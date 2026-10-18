/*
Copyright (c) CUTTOOL Dev Team. All rights reserved.
Licensed under the AGPL-3.0 License.
*/
#include "HideUI.h"
#include "../Config/Config.h"
#include "../Core/SharedState.h"
#include "../Core/Utils.h"
#include "../Patterns/Patterns.h"
#include <iostream>
#include <ctime>

static void* g_profile_uid_cached = nullptr;
static bool g_profile_uid_hidden_by_plugin = false;

static bool SetProfileUIDActive(bool active) {
    auto SetActive = (tSetActive)o_SetActive.load();
    if (!SetActive) return false;

    auto FindString = (tFindString)p_FindString.load();
    auto FindGameObject = (tFindGameObject)p_FindGameObject.load();
    if (!FindString || !FindGameObject) return false;

    bool updated = false;
    SafeInvoke([&] {
        void* go = nullptr;
        auto str_obj = FindString(GameStrings::ProfileUIDPath);
        if (str_obj) go = FindGameObject(str_obj);
        if (!go) go = g_profile_uid_cached; // inactive objects are invisible to Find
        if (go) {
            SetActive(go, active);
            g_profile_uid_cached = go;
            updated = true;
        }
    });
    return updated;
}

void ApplyProfilePrivacyState() {
    const auto& config = Config::Get();
    const bool hideUid = config.hide_uid;

    if (hideUid) {
        if (SetProfileUIDActive(false)) g_profile_uid_hidden_by_plugin = true;
    } else if (g_profile_uid_hidden_by_plugin) {
        if (SetProfileUIDActive(true)) g_profile_uid_hidden_by_plugin = false;
    }
}

void WINAPI hk_SetupPlayerProfilePage(void* pThis) {
    auto orig = (tSetupPlayerProfilePage)o_SetupPlayerProfilePage.load();
    if (orig) orig(pThis);
    ApplyProfilePrivacyState();
}

void UpdateHideUID() {
    auto& config = Config::Get();
    if (!config.hide_uid) return;

    static float last_check_time = 0.0f;
    float current_time = (float)clock() / CLOCKS_PER_SEC;

    auto SetActive = (tSetActive)o_SetActive.load();
    if (!SetActive) return;

    if (current_time - last_check_time > 2.0f) {
        last_check_time = current_time;

        auto FindString = (tFindString)p_FindString.load();
        auto FindGameObject = (tFindGameObject)p_FindGameObject.load();

        if (FindString && FindGameObject) {
            auto str_obj_watermark = FindString(GameStrings::UIDPathWatermark);
            if (str_obj_watermark) {
                void* foundObj = FindGameObject(str_obj_watermark);
                if (foundObj) {
                    SafeInvoke([&] { SetActive(foundObj, false); });
                }
            }
        }
    }
}
