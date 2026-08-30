/*
Copyright (c) CUTTOOL Dev Team. All rights reserved.
Licensed under the AGPL-3.0 License.
*/
#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <string>

struct ModConfig {
    bool debug_console = false;
    
    // FPS & FOV Unlock
    bool show_fps = true;
    bool enable_vsync_override = true;
    bool enable_fps_override = false;
    int selected_fps = 60;
    bool enable_fov_override = false;
    float fov_value = 45.0f;

    // Feature 1: Disable Event Camera Move
    bool disable_event_camera_move = false;

    // Feature 2: Remove Team Load Animation
    bool enable_remove_team_anim = false;

    // Feature 3: Disable Fog
    bool disable_fog = false;

    // Feature 4: HideUID
    bool hide_uid = false;

    // Feature 5: BlockNetwork & Network Toggle
    bool block_network = false;
    bool enable_network_toggle = false;
    int network_toggle_key = VK_F11; // default VK_F11 (122)
    bool is_currently_blocking = false;
    int toggle_key = VK_HOME; // reload config (36)
    
    // Offsets dump
    bool dump_offsets = false;
};

namespace Config {
    ModConfig& Get();
    void Load();
    std::string GetConfigPath();
}
