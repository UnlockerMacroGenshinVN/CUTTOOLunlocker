/*
Copyright (c) CUTTOOL Dev Team. All rights reserved.
Licensed under the AGPL-3.0 License.
*/
#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <winsock2.h>
#include <windows.h>
#include <atomic>
#include <vector>
#include <list>
#include <string>

struct Il2CppString;

typedef int32_t (WINAPI *tGetFrameCount)();
typedef int32_t (WINAPI *tSetFrameCount)(int32_t);
typedef int32_t (WINAPI *tChangeFov)(void*, float);
typedef void (WINAPI *tSetActive)(void*, bool);
typedef bool (WINAPI *tEventCamera)(void*, void*);
typedef bool (WINAPI *tCheckCanEnter)();
typedef void (WINAPI *tOpenTeamPage)(bool);
typedef void (WINAPI *tOpenTeam)();
typedef __int64 (*tDisplayFog)(__int64, __int64);
typedef int32_t (WINAPI *tSetSyncCount)(bool);
typedef Il2CppString* (*tGetName)(void*);
typedef void* (WINAPI *tFindGameObject)(Il2CppString*);
typedef Il2CppString* (WINAPI *tFindString)(const char*);
typedef bool (WINAPI *tGetActive)(void*);
typedef int (WSAAPI* tSend)(SOCKET s, const char* buf, int len, int flags);
typedef int (WSAAPI* tSendTo)(SOCKET s, const char* buf, int len, int flags, const struct sockaddr* to, int tolen);
typedef int (WSAAPI* tWSASend)(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, DWORD dwFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
typedef int (WSAAPI* tWSASendTo)(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, DWORD dwFlags, const struct sockaddr* lpTo, int iTolen, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
typedef int (WSAAPI* tRecv)(SOCKET s, char* buf, int len, int flags);
typedef int (WSAAPI* tRecvFrom)(SOCKET s, char* buf, int len, int flags, struct sockaddr* from, int* fromlen);

extern std::atomic<void*> o_GetFrameCount;
extern std::atomic<void*> o_SetFrameCount;
extern std::atomic<void*> o_ChangeFov;
extern std::atomic<void*> o_EventCamera;
extern std::atomic<void*> o_OpenTeam;
extern std::atomic<void*> o_DisplayFog;
extern std::atomic<void*> o_SetActive;
extern std::atomic<void*> p_CheckCanEnter;
extern std::atomic<void*> p_OpenTeamPage;
extern std::atomic<void*> o_SetSyncCount;
extern std::atomic<void*> p_GetName;

extern std::atomic<void*> p_FindGameObject;
extern std::atomic<void*> p_FindString;
extern std::atomic<void*> p_GetActive;

extern std::atomic<void*> o_send;
extern std::atomic<void*> o_sendto;
extern std::atomic<void*> o_WSASend;
extern std::atomic<void*> o_WSASendTo;
extern std::atomic<void*> o_recv;
extern std::atomic<void*> o_recvfrom;

extern std::atomic<bool> g_GameUpdateInit;

struct SafeFogBuffer {
    __declspec(align(16)) uint8_t data[404];
    uint8_t padding[16];
};
