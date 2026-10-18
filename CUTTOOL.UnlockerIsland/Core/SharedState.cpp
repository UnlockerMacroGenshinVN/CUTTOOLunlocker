/*
Copyright (c) CUTTOOL Dev Team. All rights reserved.
Licensed under the AGPL-3.0 License.
*/
#include "SharedState.h"

std::atomic<void*> o_GetFrameCount{ nullptr };
std::atomic<void*> o_SetFrameCount{ nullptr };
std::atomic<void*> o_ChangeFov{ nullptr };
std::atomic<void*> o_EventCamera{ nullptr };
std::atomic<void*> o_OpenTeam{ nullptr };
std::atomic<void*> o_SetupPlayerProfilePage{ nullptr };
std::atomic<void*> o_DisplayFog{ nullptr };
std::atomic<void*> o_SetActive{ nullptr };
std::atomic<void*> p_CheckCanEnter{ nullptr };
std::atomic<void*> p_OpenTeamPage{ nullptr };
std::atomic<void*> o_SetSyncCount{ nullptr };
std::atomic<void*> p_GetName{ nullptr };

std::atomic<void*> p_FindGameObject{ nullptr };
std::atomic<void*> p_FindString{ nullptr };
std::atomic<void*> p_GetActive{ nullptr };

std::atomic<void*> o_send{ nullptr };
std::atomic<void*> o_sendto{ nullptr };
std::atomic<void*> o_WSASend{ nullptr };
std::atomic<void*> o_WSASendTo{ nullptr };
std::atomic<void*> o_recv{ nullptr };
std::atomic<void*> o_recvfrom{ nullptr };

std::atomic<bool> g_GameUpdateInit{ false };
