/*
Copyright (c) CUTTOOL Dev Team. All rights reserved.
Licensed under the AGPL-3.0 License.
*/
#include <Windows.h>
#include <thread>
#include <iostream>
#include <cstdio>
#include <string>
#include <filesystem>
#include <fstream>

#include "../Config/Config.h"
#include "Hooks.h"
#include "../Visual/Gui.h"
#include "../HideUI/HideUI.h"

static std::string g_LogPath;

static void LogToFile(const std::string& msg) {
    std::error_code ec;
    if (std::filesystem::exists(g_LogPath, ec)) {
        if (std::filesystem::file_size(g_LogPath, ec) > 1048576) {
            std::ofstream truncFile(g_LogPath, std::ios::trunc);
            truncFile.close();
        }
    }

    std::ofstream ofs(g_LogPath, std::ios::app);
    if (ofs.is_open()) {
        SYSTEMTIME st;
        GetLocalTime(&st);
        char timeBuf[64];
        sprintf_s(timeBuf, "[%02d:%02d:%02d] ", st.wHour, st.wMinute, st.wSecond);
        ofs << timeBuf << msg << std::endl;
    }
}

inline FILETIME GetFileLastWriteTime(const std::string& path) {
    FILETIME lastWriteTime = { 0, 0 };
    WIN32_FILE_ATTRIBUTE_DATA fileInfo;
    if (GetFileAttributesExA(path.c_str(), GetFileExInfoStandard, &fileInfo)) {
        lastWriteTime = fileInfo.ftLastWriteTime;
    }
    return lastWriteTime;
}

void OpenConsole(const char* title) {
    if (AllocConsole()) {
        FILE* f;
        freopen_s(&f, "CONOUT$", "w", stdout);
        freopen_s(&f, "CONOUT$", "w", stderr);
        freopen_s(&f, "CONIN$", "r", stdin);
        SetConsoleTitleA(title);
        std::cout << "[+] Console Allocated - CUTTOOL UnlockerIsland (Lite)\n";
    }
}

void MainWorker(HMODULE hMod) {
    char dllPath[MAX_PATH];
    GetModuleFileNameA(hMod, dllPath, MAX_PATH);
    g_LogPath = dllPath;
    size_t lastSlash = g_LogPath.find_last_of("\\/");
    if (lastSlash != std::string::npos)
        g_LogPath = g_LogPath.substr(0, lastSlash + 1);
    g_LogPath += "heartbeat.log";
    LogToFile("=== DLL Loaded ===");

    Config::Load();

    if (Config::Get().debug_console) {
        OpenConsole("Unlocker System (Lite)");
    }

    std::cout << "[*] Initializing Hooks..." << '\n';
    if (!Hooks::Init()) {
        std::cout << "[!] Hooks::Init Failed!" << '\n';
        return;
    }

    std::cout << "[*] Initializing DX11 Hook for FPS..." << '\n';
    Gui::InitDX11Hook();
    
    std::cout << "[*] Waiting for GameUpdate..." << '\n';
    while (!Hooks::IsGameUpdateInit()) {
        Sleep(1000);
    }

    std::string configPath = Config::GetConfigPath();
    FILETIME lastConfigWriteTime = GetFileLastWriteTime(configPath);

    int fileCheckCounter = 0;

    while (true) {
        auto& cfg = Config::Get();
        
        HWND hForeground = GetForegroundWindow();
        DWORD foregroundProcessId = 0;
        if (hForeground) {
            GetWindowThreadProcessId(hForeground, &foregroundProcessId);
        }
        bool isFocused = (foregroundProcessId == GetCurrentProcessId());

        // Toggle Network Key
        static bool net_was_pressed = false;
        bool net_is_pressed = (isFocused && cfg.network_toggle_key != 0 && (GetAsyncKeyState(cfg.network_toggle_key) & 0x8000));

        if (cfg.enable_network_toggle && net_is_pressed && !net_was_pressed) {
            cfg.is_currently_blocking = !cfg.is_currently_blocking;
            
            if (cfg.is_currently_blocking) {
                std::thread([] { Beep(300, 300); }).detach(); 
                std::cout << "[Network] >>> STATUS: DISCONNECTED (Blocking / Network OFF)" << '\n';
            } else {
                std::thread([] { Beep(1000, 150); }).detach(); 
                std::cout << "[Network] >>> STATUS: CONNECTED (Normal / Network ON)" << '\n';
            }
        }
        net_was_pressed = net_is_pressed;
        
        // Manual Reload Key (default VK_HOME = 36)
        if (isFocused && cfg.toggle_key != 0 && (GetAsyncKeyState(cfg.toggle_key) & 0x8000)) {
            Config::Load();
            ApplyProfilePrivacyState();
            std::cout << "[*] Config reloaded manually." << '\n';
            Sleep(400);
        }

        // Automatic config reload check every ~500ms (35 * 15ms)
        if (++fileCheckCounter >= 35) {
            fileCheckCounter = 0;
            FILETIME currentWriteTime = GetFileLastWriteTime(configPath);
            if (CompareFileTime(&lastConfigWriteTime, &currentWriteTime) != 0) {
                Config::Load();
                ApplyProfilePrivacyState();
                if (Config::Get().debug_console) {
                    std::cout << "[*] Automatic config reload detected." << '\n';
                }
                lastConfigWriteTime = currentWriteTime;
            }
        }
        
        Sleep(15);
    }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        std::thread(MainWorker, hModule).detach();
    }
    return TRUE;
}
