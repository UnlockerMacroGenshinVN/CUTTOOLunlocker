/*
Copyright (c) CUTTOOL Dev Team. All rights reserved.
Licensed under the AGPL-3.0 License.
*/
#pragma once
#include <string>

namespace Patterns {
    // FPS & FOV
    inline constexpr const char* GetFrameCount = "E8 ? ? ? ? 85 C0 7E 0E E8 ? ? ? ? 0F 57 C0 F3 0F 2A C0 EB 08";
    inline constexpr const char* SetFrameCount = "E8 ? ? ? ? E8 ? ? ? ? 83 F8 1F 0F 9C 05 ? ? ? ? 48 8B 05";
    inline constexpr const char* ChangeFOV = "40 53 48 83 EC 60 0F 29 74 24 ? 48 8B D9 0F 28 F1 E8 ? ? ? ? 48 85 C0 0F 84 ? ? ? ? E8 ? ? ? ? 48 8B C8";
    inline constexpr const char* SetSyncCount = "E8 ? ? ? ? E8 ? ? ? ? 89 C6 E8 ? ? ? ? 31 C9 89 F2 49 89 C0 E8 ? ? ? ? 48 89 C6 48 8B 0D ? ? ? ? 80 B9 ? ? ? ? ? 74 47 48 8B 3D ? ? ? ? 48 85 DF 74 4C";

    // Feature 1: Disable Event Camera Move
    inline constexpr const char* EventCamera = "41 57 41 56 56 57 55 53 48 83 EC 48 48 89 D7 49 89 CE 80 3D ?? ?? ?? ?? 00 0F 85 ?? ?? ?? ?? 80";

    // Feature 2: Remove Team Load Animation
    inline constexpr const char* CheckCanEnter = "56 48 81 ec 80 00 00 00 80 3d ? ? ? ? 00 0f 84 ? ? ? ? 80 3d ? ? ? ? 00";
    inline constexpr const char* OpenTeamPage = "56 57 53 48 83 ec 20 89 cb 80 3d ? ? ? ? 00 74 7a 80 3d ? ? ? ? 00 48 8b 05";
    inline constexpr const char* OpenTeam = "48 83 EC 28 80 3D ? ? ? ? 00 75 ? 48 8B 0D ? ? ? ? 80 B9 C7 00 00 00 00 74 ? B9 0C 00 00 00 E8 ? ? ? ? 84 C0 74"; 

    // Feature 3: Hide Grass & Burst Blackscreen
    inline constexpr const char* SetActive = "";
    inline constexpr const char* GetName = "40 53 48 81 EC ?? ?? ?? ?? 48 8B D9 48 85 C9 0F 84 ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 85 C0 0F 84 ?? ?? ?? ?? 48 8B 10 48 8B C8 FF 52 ?? 48 85 C0 0F 85 ?? ?? ?? ?? 48 8B CB E8 ?? ?? ?? ??";

    inline constexpr const char* FindGameObject = "40 53 48 83 EC ? 48 89 4C 24 ? 48 8D 54 24 ? 48 8D 4C 24 ? E8 ? ? ? ? 48 8B 08 48 85 C9 75 ? 48 8D 48 ? E8 ? ? ? ? 48 8B 4C 24 ? 48 8B D8 48 85 C9 74 ? 48 83 7C 24 ? 00 76";
    inline constexpr const char* FindString = "56 48 83 ec 20 48 89 ce e8 ? ? ? ? 48 89 f1 89 c2 48 83 c4 20 5e e9 ? ? ? ? cc cc cc cc";
    inline constexpr const char* GetActive = "E8 ?? ?? ?? ?? 84 C0 74 ?? 48 89 F1 E8 ?? ?? ?? ?? 48 8B 4E ?? 48 85 C9 0F 84 ?? ?? ?? ?? 80 79 ?? ?? 0F 94 C1 08 C1";

    // Feature 4: Disable Fog
    inline constexpr const char* DisplayFog = "0F B6 02 88 01 8B 42 04 89 41 04 F3 0F 10 52 ? F3 0F 10 4A ? F3 0F 10 42 ? 8B 42 08";

    // Feature: SetupPlayerProfilePage (Event-driven profile privacy)
    inline constexpr const char* SetupPlayerProfilePage = "55 41 57 41 56 41 55 41 54 56 57 53 48 81 EC ?? ?? ?? ?? 48 8D AC 24 ?? ?? ?? ?? 0F 29 75 ?? 48 C7 45 ?? ?? ?? ?? ?? 49 89 CC 80 3D ?? ?? ?? ?? ?? 0F 84 ?? ?? ?? ?? 80 3D ?? ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 0F 85 ?? ?? ?? ??";

    namespace CN {
        inline constexpr const char* EventCameraOffset = "";
        inline constexpr const char* SetActiveOffset = "1452EE0";
    }

    namespace OS {
        inline constexpr const char* EventCameraOffset = "73AC8E0"; // 7.1 OS offset
        inline constexpr const char* SetActiveOffset = "1452EE0";   // 7.1 OS offset
    }
}

namespace GameStrings {
    inline constexpr const char* ProfileUIDPath = "/Canvas/Pages/PlayerProfilePage/GrpProfile/Right/GrpPlayerCard/UID";
    inline constexpr const char* UIDPathWatermark = "/BetaWatermarkCanvas(Clone)/Panel/TxtUID";
}

namespace Offsets {
    extern std::string EventCameraOffset;
    extern std::string SetActiveOffset;
    void InitOffsets(bool isOS);
}
