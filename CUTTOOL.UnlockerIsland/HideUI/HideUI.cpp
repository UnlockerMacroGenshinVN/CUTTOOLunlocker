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
            auto str_obj_watermark = FindString("/BetaWatermarkCanvas(Clone)/Panel/TxtUID");
            if (str_obj_watermark) {
                void* foundObj = FindGameObject(str_obj_watermark);
                if (foundObj) {
                    SafeInvoke([&] { SetActive(foundObj, false); });
                }
            }
            
            auto str_obj_main = FindString("/Canvas/Pages/PlayerProfilePage/GrpProfile/Right/GrpPlayerCard/UID");
            if (str_obj_main) {
                void* foundObjMain = FindGameObject(str_obj_main);
                if (foundObjMain) {
                    SafeInvoke([&] { SetActive(foundObjMain, false); });
                }
            }
        }
    }
}
