/*
Copyright (c) CUTTOOL Dev Team. All rights reserved.
Licensed under the AGPL-3.0 License.
*/
#include "Config.h"
#include <string>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <Windows.h>

ModConfig g_Config;

namespace Config {
    ModConfig& Get() { return g_Config; }
    
    int ReadInt(LPCSTR section, int defaultVal, LPCSTR file) {
        return GetPrivateProfileIntA(section, "Value", defaultVal, file);
    }

    float ReadFloat(LPCSTR section, float defaultVal, LPCSTR file) {
        char buf[32];
        char defStr[32];
        snprintf(defStr, sizeof(defStr), "%f", defaultVal);
        GetPrivateProfileStringA(section, "Value", defStr, buf, 32, file);
        return (float)atof(buf);
    }

    std::string GetConfigPath() {
        char path[MAX_PATH];
        HMODULE hm = NULL;
        GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR)&g_Config, &hm);
        GetModuleFileNameA(hm, path, sizeof(path));
        
        std::string fullPath = path;
        std::string dirPath;
        size_t lastSlash = fullPath.find_last_of("\\/");
        if (lastSlash != std::string::npos) {
            dirPath = fullPath.substr(0, lastSlash);
        } else {
            dirPath = ".";
        }
        return dirPath + "\\config.ini";
    }
    
    void Load() {
        std::string cfgPath = GetConfigPath();
        LPCSTR file = cfgPath.c_str();
        
        g_Config.debug_console = ReadInt("DebugConsole", 0, file);
        
        // FPS & FOV
        g_Config.show_fps = ReadInt("ShowFps", 1, file);
        g_Config.enable_fps_override = ReadInt("FpsUnlock", 0, file);
        g_Config.selected_fps = ReadInt("TargetFps", 60, file);
        if (g_Config.selected_fps > 100000) {
            g_Config.selected_fps = 100000;
        } else if (g_Config.selected_fps < 1) {
            g_Config.selected_fps = 60;
        }
        g_Config.enable_vsync_override = ReadInt("VSync", 1, file);
        g_Config.enable_fov_override = ReadInt("FovUnlock", 0, file);
        g_Config.fov_value = ReadFloat("FovValue", 45.0f, file);
        
        // Feature 1: Event Camera
        g_Config.disable_event_camera_move = ReadInt("DisableCameraMove", 0, file);
        
        // Feature 2: Remove Team Animation
        g_Config.enable_remove_team_anim = ReadInt("RemoveTeamAnim", 0, file);
        
        // Feature 3: Disable Fog
        g_Config.disable_fog = ReadInt("DisableFog", 0, file);

        // Feature 4: HideUID
        g_Config.hide_uid = ReadInt("HideUID", 0, file);

        // Feature 5: BlockNetwork & Network Toggle
        g_Config.block_network = ReadInt("BlockNetwork", 0, file);
        g_Config.enable_network_toggle = ReadInt("EnableNetworkToggle", 0, file);
        g_Config.network_toggle_key = ReadInt("NetworkToggleKey", VK_F11, file);
        g_Config.toggle_key = ReadInt("ToggleKey", VK_HOME, file);

        g_Config.dump_offsets = ReadInt("DumpOffsets", 0, file);
    }
}
