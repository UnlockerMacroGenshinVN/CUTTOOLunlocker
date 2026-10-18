/*
Copyright (c) CUTTOOL Dev Team. All rights reserved.
Licensed under the AGPL-3.0 License.
*/
#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

void UpdateHideUID();
void ApplyProfilePrivacyState();
void WINAPI hk_SetupPlayerProfilePage(void* pThis);
