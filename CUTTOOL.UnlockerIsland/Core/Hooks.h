/*
Copyright (c) CUTTOOL Dev Team. All rights reserved.
Licensed under the AGPL-3.0 License.
*/
#pragma once
#include <atomic>

namespace Hooks {
    bool Init();
    void Uninit();
    
    bool IsGameUpdateInit();
}
