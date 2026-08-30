/*
Copyright (c) CUTTOOL Dev Team. All rights reserved.
Licensed under the AGPL-3.0 License.
*/
#include "Gui.h"
#include "../Config/Config.h"
#include "../MinHook/MinHook.h"
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_win32.h"
#include "../ImGui/imgui_impl_dx11.h"
#include <d3d11.h>
#include <dxgi.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <thread>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Gui {
    typedef HRESULT(__stdcall* Present_t)(IDXGISwapChain*, UINT, UINT);
    typedef HRESULT(__stdcall* ResizeBuffers_t)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);

    Present_t oPresent = nullptr;
    ResizeBuffers_t oResizeBuffers = nullptr;

    HWND g_hWnd = nullptr;
    ID3D11Device* g_pd3dDevice = nullptr;
    ID3D11DeviceContext* g_pd3dContext = nullptr;
    ID3D11RenderTargetView* g_mainRTV = nullptr;
    bool g_ImGuiInitialized = false;

    void CleanupRenderTarget() {
        if (g_mainRTV) {
            g_mainRTV->Release();
            g_mainRTV = nullptr;
        }
    }

    void CreateRenderTarget(IDXGISwapChain* pSwapChain) {
        ID3D11Texture2D* pBackBuffer = nullptr;
        if (SUCCEEDED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer))) {
            g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRTV);
            pBackBuffer->Release();
        }
    }

    void InitImGui(IDXGISwapChain* pSwapChain) {
        if (g_ImGuiInitialized) return;

        if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&g_pd3dDevice))) {
            g_pd3dDevice->GetImmediateContext(&g_pd3dContext);

            DXGI_SWAP_CHAIN_DESC sd;
            pSwapChain->GetDesc(&sd);
            g_hWnd = sd.OutputWindow;

            CreateRenderTarget(pSwapChain);

            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();
            io.IniFilename = nullptr;
            io.ConfigFlags &= ~ImGuiConfigFlags_NavEnableKeyboard;

            ImVector<ImWchar> ranges;
            ImFontGlyphRangesBuilder builder;

            builder.AddRanges(io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
            builder.AddRanges(io.Fonts->GetGlyphRangesChineseFull());
            builder.BuildRanges(&ranges);

            io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\msyhbd.ttc", 20.0f, NULL, ranges.Data);
            io.Fonts->Build();

            ImGui::StyleColorsDark();

            ImGui_ImplWin32_Init(g_hWnd);
            ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dContext);

            g_ImGuiInitialized = true;
        }
    }

    HRESULT __stdcall HookedPresent(IDXGISwapChain* pSwapChain, UINT sync, UINT flags) {
        if (!g_ImGuiInitialized)
            InitImGui(pSwapChain);

        if (Config::Get().show_fps) {
            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

            char buffer[64];
            sprintf_s(buffer, "FPS: %.0f", ImGui::GetIO().Framerate);

            ImDrawList* draw_list = ImGui::GetForegroundDrawList();
            ImVec2 text_size = ImGui::CalcTextSize(buffer);
            ImVec2 pos = ImVec2(5.f, 5.f); // TopLeft
            
            draw_list->AddText(pos, IM_COL32_WHITE, buffer);

            ImGui::Render();
            g_pd3dContext->OMSetRenderTargets(1, &g_mainRTV, NULL);
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        }

        return oPresent(pSwapChain, sync, flags);
    }

    HRESULT __stdcall HookedResizeBuffers(IDXGISwapChain* pSwapChain,
        UINT BufferCount, UINT Width, UINT Height,
        DXGI_FORMAT NewFormat, UINT SwapChainFlags) {
        
        if (g_ImGuiInitialized) {
            ImGui_ImplDX11_InvalidateDeviceObjects();
            CleanupRenderTarget();
        }

        HRESULT hr = oResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);

        if (g_ImGuiInitialized) {
            CreateRenderTarget(pSwapChain);
            ImGui_ImplDX11_CreateDeviceObjects();
        }

        return hr;
    }

    DWORD WINAPI DX11InitThread(LPVOID lpParam) {
        WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, DefWindowProc, 0L, 0L,
            GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("DummyWindowForDX11"), NULL };
        RegisterClassEx(&wc);
        HWND hwnd = CreateWindow(wc.lpszClassName, _T("DummyWindowForDX11"), WS_OVERLAPPEDWINDOW,
            0, 0, 100, 100, NULL, NULL, wc.hInstance, NULL);

        DXGI_SWAP_CHAIN_DESC sd = {};
        sd.BufferCount = 1;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = hwnd;
        sd.SampleDesc.Count = 1;
        sd.Windowed = TRUE;
        sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        D3D_FEATURE_LEVEL level;
        const D3D_FEATURE_LEVEL levels[] = { D3D_FEATURE_LEVEL_11_0 };
        IDXGISwapChain* pSwapChain = nullptr;
        ID3D11Device* pDevice = nullptr;
        ID3D11DeviceContext* pContext = nullptr;

        if (SUCCEEDED(D3D11CreateDeviceAndSwapChain(
            nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, levels, 1,
            D3D11_SDK_VERSION, &sd, &pSwapChain, &pDevice, &level, &pContext)))
        {
            void** vTable = *reinterpret_cast<void***>(pSwapChain);

            if (MH_CreateHook(vTable[8], (void*)HookedPresent, (void**)&oPresent) == MH_OK) {
                MH_EnableHook(vTable[8]);
                std::cout << "[+] DX11 Present Hook Ready.\n";
            } else {
                std::cout << "[!] DX11 Present Hook Failed.\n";
            }

            if (MH_CreateHook(vTable[13], (void*)HookedResizeBuffers, (void**)&oResizeBuffers) == MH_OK) {
                MH_EnableHook(vTable[13]);
                std::cout << "[+] DX11 ResizeBuffers Hook Ready.\n";
            } else {
                std::cout << "[!] DX11 ResizeBuffers Hook Failed.\n";
            }

            pSwapChain->Release();
            pDevice->Release();
            pContext->Release();
        }

        DestroyWindow(hwnd);
        UnregisterClass(wc.lpszClassName, wc.hInstance);

        return 0;
    }

    void InitDX11Hook() {
        std::thread(DX11InitThread, nullptr).detach();
    }
}
