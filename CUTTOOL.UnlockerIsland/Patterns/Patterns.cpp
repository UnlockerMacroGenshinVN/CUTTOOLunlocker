/*
Copyright (c) CUTTOOL Dev Team. All rights reserved.
Licensed under the AGPL-3.0 License.
*/
#include "Patterns.h"
#include <iostream>

namespace Offsets {
    std::string EventCameraOffset;
    std::string SetActiveOffset;

    void InitOffsets(bool isOS) {
        if (isOS) {
            EventCameraOffset = Patterns::OS::EventCameraOffset;
            SetActiveOffset = Patterns::OS::SetActiveOffset;
            std::cout << "[INFO] Pre-initialized Global (OS) Offsets" << std::endl;
        } else {
            EventCameraOffset = Patterns::CN::EventCameraOffset;
            SetActiveOffset = Patterns::CN::SetActiveOffset;
            std::cout << "[INFO] Pre-initialized China (CN) Offsets" << std::endl;
        }
    }
}
