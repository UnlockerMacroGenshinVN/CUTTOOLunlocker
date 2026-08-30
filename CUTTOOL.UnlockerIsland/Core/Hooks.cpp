/*
Copyright (c) CUTTOOL Dev Team. All rights reserved.
Licensed under the AGPL-3.0 License.
*/
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "Hooks.h"
#include "../Scanner/Scanner.h"
#include "../Config/Config.h"
#include "Utils.h"
#include "../MinHook/MinHook.h"
#include "SharedState.h"
#include "../Patterns/Patterns.h"
#include "../Visual/Visual.h"
#include "../Network/Network.h"
#include "../HideUI/HideUI.h"
#include <iostream>
#include <atomic>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>

#pragma comment(lib, "MinHook/libMinHook.x64.lib")
#pragma comment(lib, "ws2_32.lib")

#define HOOK_REL(name, pat, hookFn, storeOrig) \
    { \
        std::cout << "[SCAN] " << name << "..." << std::endl; \
        void* addr = Scanner::ScanMainMod(pat); \
        if (addr) { \
            void* target = Scanner::ResolveRelative(addr, 1, 5); \
            if (target) { \
                LogOffset(name, target, addr); \
                std::cout << "   -> Found at: 0x" << std::hex << ((long long)target - (long long)GetModuleHandle(nullptr)) << std::endl; \
                if (MH_CreateHook(target, (void*)hookFn, (void**)&storeOrig) == MH_OK) \
                    std::cout << "   -> Hook Ready." << std::endl; \
                else std::cout << "   -> [ERR] MH_CreateHook Failed." << std::endl; \
            } else std::cout << "   -> [ERR] ResolveRelative Failed." << std::endl; \
        } else std::cout << "   -> [ERR] Pattern Not Found." << std::endl; \
    }

#define HOOK_DIR(name, pat, hookFn, storeOrig) \
    { \
        std::cout << "[SCAN] " << name << "..." << std::endl; \
        void* addr = Scanner::ScanMainMod(pat); \
        if (addr) { \
            LogOffset(name, addr, addr); \
            std::cout << "   -> Found at: 0x" << std::hex << ((long long)addr - (long long)GetModuleHandle(nullptr)) << std::endl; \
            if (MH_CreateHook(addr, (void*)hookFn, (void**)&storeOrig) == MH_OK) \
                 std::cout << "   -> Hook Ready." << std::endl; \
            else std::cout << "   -> [ERR] MH_CreateHook Failed." << std::endl; \
        } else std::cout << "   -> [ERR] Pattern Not Found." << std::endl; \
    }

#define SCAN_REL(name, pat, storePtr) \
    { \
        std::cout << "[SCAN] " << name << "..." << std::endl; \
        void* addr = Scanner::ScanMainMod(pat); \
        if (addr) { \
            void* target = Scanner::ResolveRelative(addr, 1, 5); \
            LogOffset(name, target, addr); \
            if (target) { \
                storePtr.store(target); \
                std::cout << "   -> Found at: 0x" << std::hex << ((long long)target - (long long)GetModuleHandle(nullptr)) << std::endl; } \
        } else std::cout << "   -> [ERR] Not Found." << std::endl; \
    }

#define SCAN_DIR(name, pat, storePtr) \
    { \
        std::cout << "[SCAN] " << name << "..." << std::endl; \
        void* addr = Scanner::ScanMainMod(pat); \
        if (addr) { \
            storePtr.store(addr); LogOffset(name, addr, addr); \
            std::cout << "   -> Found at: 0x" << std::hex << ((long long)addr - (long long)GetModuleHandle(nullptr)) << std::endl; } \
        else std::cout << "   -> [ERR] Not Found." << std::endl; \
    }

int32_t WINAPI hk_GetFrameCount() {
    auto orig = (tGetFrameCount)o_GetFrameCount.load();
    if (!orig) return 60;
    int32_t ret = 60;
    SafeInvoke([&] { ret = orig(); });

    UpdateHideUID();

    return ret;
}

int32_t WINAPI hk_ChangeFov(void* __this, float value) {
    if (!g_GameUpdateInit.load()) g_GameUpdateInit.store(true);

    auto& cfg = Config::Get();

    if (cfg.enable_vsync_override) {
        auto setSync = (tSetSyncCount)o_SetSyncCount.load();
        if (IsValid(setSync)) SafeInvoke([&]() { setSync(false); });
    }

    if (cfg.enable_fps_override) {
        auto setFps = (tSetFrameCount)o_SetFrameCount.load();
        if (IsValid(setFps)) SafeInvoke([&]() { setFps(cfg.selected_fps); });
    }

    if (cfg.enable_fov_override) {
        value = cfg.fov_value;
    }

    auto orig = (tChangeFov)o_ChangeFov.load();
    return orig ? orig(__this, value) : 0;
}

bool Hooks::Init() {
    auto StringToAddr = [](const std::string& hexStr) -> uintptr_t {
        if (hexStr.empty()) return 0;
        uintptr_t addr = 0;
        std::stringstream ss;
        ss << std::hex << hexStr;
        ss >> addr;
        return addr;
    };

    char szFileName[MAX_PATH];
    GetModuleFileNameA(NULL, szFileName, MAX_PATH);
    std::string path(szFileName);
    std::transform(path.begin(), path.end(), path.begin(), ::tolower);
    bool isOS = (path.find("genshinimpact.exe") != std::string::npos);
    Offsets::InitOffsets(isOS);

    if (Config::Get().dump_offsets) {
        std::string filePath = GetOwnDllDir() + "\\offsets.txt";
        std::ofstream file(filePath, std::ios::trunc);
        if (file.is_open()) {
            file << "Feature Offsets Dump" << '\n';
            file << "====================" << '\n';
            file << "Generated on module init." << '\n' << '\n';
        }
    }

    if (MH_Initialize() != MH_OK) return false;

    // Feature 5: FPS & FOV
    HOOK_REL("GetFrameCount", Patterns::GetFrameCount, hk_GetFrameCount, o_GetFrameCount);
    SCAN_REL("SetFrameCount", Patterns::SetFrameCount, o_SetFrameCount);
    HOOK_DIR("ChangeFOV", Patterns::ChangeFOV, hk_ChangeFov, o_ChangeFov);
    SCAN_REL("SetSyncCount", Patterns::SetSyncCount, o_SetSyncCount);

    // Feature 2: Remove Team Load Animation
    SCAN_DIR("CheckCanEnter", Patterns::CheckCanEnter, p_CheckCanEnter);
    SCAN_DIR("OpenTeamPage", Patterns::OpenTeamPage, p_OpenTeamPage);
    HOOK_DIR("OpenTeam", Patterns::OpenTeam, hk_OpenTeam, o_OpenTeam);

    // Feature 4: Disable Fog
    HOOK_DIR("DisplayFog", Patterns::DisplayFog, hk_DisplayFog, o_DisplayFog);

    // Feature 1: Event Camera Move
    void* eventCameraAddr = nullptr;
    uintptr_t offsetEventCam = StringToAddr(Offsets::EventCameraOffset);
    if (offsetEventCam > 0) {
        eventCameraAddr = (void*)((uintptr_t)GetModuleHandle(NULL) + offsetEventCam);
        std::cout << "[SCAN] EventCamera resolved via explicit offset: 0x" << std::hex << offsetEventCam << std::dec << '\n';
    } else {
        void* scanRes = Scanner::ScanMainMod(Patterns::EventCamera);
        if (scanRes) {
            eventCameraAddr = scanRes;
            std::cout << "[SCAN] EventCamera resolved via signature fallback.\n";
        }
    }

    if (eventCameraAddr) {
        LogOffset("EventCamera", eventCameraAddr, eventCameraAddr);
        if (MH_CreateHook(eventCameraAddr, (void*)hk_EventCamera, (void**)&o_EventCamera) == MH_OK) {
            std::cout << "   -> EventCamera Hook Ready.\n";
        } else {
            std::cout << "   -> [ERR] EventCamera Hook Failed.\n";
        }
    } else {
        std::cout << "   -> [ERR] EventCamera not found.\n";
    }

    // HideUID
    SCAN_DIR("FindGameObject", Patterns::FindGameObject, p_FindGameObject);
    SCAN_DIR("FindString", Patterns::FindString, p_FindString);
    SCAN_DIR("GetActive", Patterns::GetActive, p_GetActive);
    
    uintptr_t offsetSetActive = StringToAddr(Offsets::SetActiveOffset);
    if (offsetSetActive > 0) {
        void* setActiveAddr = (void*)((uintptr_t)GetModuleHandle(NULL) + offsetSetActive);
        o_SetActive.store(setActiveAddr);
        std::cout << "[SCAN] SetActive resolved via offset: 0x" << std::hex << offsetSetActive << std::dec << '\n';
    } else {
        SCAN_REL("SetActive", Patterns::SetActive, o_SetActive);
    }

    // BlockNetwork / Network Toggle (Comprehensive: TCP, UDP, Overlapped I/O, Send & Recv)
    MH_CreateHookApi(L"ws2_32.dll", "send", (void*)hk_send, (void**)&o_send);
    MH_CreateHookApi(L"ws2_32.dll", "sendto", (void*)hk_sendto, (void**)&o_sendto);
    MH_CreateHookApi(L"ws2_32.dll", "WSASend", (void*)hk_WSASend, (void**)&o_WSASend);
    MH_CreateHookApi(L"ws2_32.dll", "WSASendTo", (void*)hk_WSASendTo, (void**)&o_WSASendTo);
    MH_CreateHookApi(L"ws2_32.dll", "recv", (void*)hk_recv, (void**)&o_recv);
    MH_CreateHookApi(L"ws2_32.dll", "recvfrom", (void*)hk_recvfrom, (void**)&o_recvfrom);
    std::cout << "   -> ws2_32 Network Hooks Ready (send, sendto, WSASend, WSASendTo, recv, recvfrom)." << std::endl;

    if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK) {
        std::cout << "[SCAN] MH_EnableHook Failed!" << '\n';
        return false;
    }

    return true;
}

bool Hooks::IsGameUpdateInit() { return o_GetFrameCount.load() != nullptr; }
void Hooks::Uninit() {}
