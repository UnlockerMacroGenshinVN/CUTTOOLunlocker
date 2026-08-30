/*
Copyright (c) CUTTOOL Dev Team. All rights reserved.
Licensed under the AGPL-3.0 License.
*/
#pragma once
#include "../Core/SharedState.h"
#include <string>

bool WINAPI hk_EventCamera(void* a, void* b);
void WINAPI hk_OpenTeam();
auto hk_DisplayFog(__int64 a1, __int64 a2) -> __int64;

bool CheckWindowFocused(HWND window);
std::string GetOwnDllDir();
std::string GetInstructionInfo(uint8_t* addr);
void LogOffset(const std::string& name, void* resultAddress, void* instructionAddress = nullptr);
