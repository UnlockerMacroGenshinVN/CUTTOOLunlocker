/*
Copyright (c) CUTTOOL Dev Team. All rights reserved.
Licensed under the AGPL-3.0 License.
*/
#include "Network.h"
#include "../Config/Config.h"

int WSAAPI hk_send(SOCKET s, const char* buf, int len, int flags) {
    if (Config::Get().block_network || (Config::Get().enable_network_toggle && Config::Get().is_currently_blocking)) {
        return len;
    }
    auto orig = (tSend)o_send.load();
    return orig ? orig(s, buf, len, flags) : len;
}

int WSAAPI hk_sendto(SOCKET s, const char* buf, int len, int flags, const struct sockaddr* to, int tolen) {
    if (Config::Get().block_network || (Config::Get().enable_network_toggle && Config::Get().is_currently_blocking)) {
        return len;
    }
    auto orig = (tSendTo)o_sendto.load();
    return orig ? orig(s, buf, len, flags, to, tolen) : len;
}

int WSAAPI hk_WSASend(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, DWORD dwFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine) {
    if (Config::Get().block_network || (Config::Get().enable_network_toggle && Config::Get().is_currently_blocking)) {
        if (lpNumberOfBytesSent && lpBuffers && dwBufferCount > 0) {
            DWORD total = 0;
            for (DWORD i = 0; i < dwBufferCount; ++i) total += lpBuffers[i].len;
            *lpNumberOfBytesSent = total;
        }
        return 0;
    }
    auto orig = (tWSASend)o_WSASend.load();
    return orig ? orig(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags, lpOverlapped, lpCompletionRoutine) : 0;
}

int WSAAPI hk_WSASendTo(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, DWORD dwFlags, const struct sockaddr* lpTo, int iTolen, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine) {
    if (Config::Get().block_network || (Config::Get().enable_network_toggle && Config::Get().is_currently_blocking)) {
        if (lpNumberOfBytesSent && lpBuffers && dwBufferCount > 0) {
            DWORD total = 0;
            for (DWORD i = 0; i < dwBufferCount; ++i) total += lpBuffers[i].len;
            *lpNumberOfBytesSent = total;
        }
        return 0;
    }
    auto orig = (tWSASendTo)o_WSASendTo.load();
    return orig ? orig(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags, lpTo, iTolen, lpOverlapped, lpCompletionRoutine) : 0;
}

int WSAAPI hk_recv(SOCKET s, char* buf, int len, int flags) {
    if (Config::Get().block_network || (Config::Get().enable_network_toggle && Config::Get().is_currently_blocking)) {
        WSASetLastError(WSAEWOULDBLOCK);
        return SOCKET_ERROR;
    }
    auto orig = (tRecv)o_recv.load();
    return orig ? orig(s, buf, len, flags) : SOCKET_ERROR;
}

int WSAAPI hk_recvfrom(SOCKET s, char* buf, int len, int flags, struct sockaddr* from, int* fromlen) {
    if (Config::Get().block_network || (Config::Get().enable_network_toggle && Config::Get().is_currently_blocking)) {
        WSASetLastError(WSAEWOULDBLOCK);
        return SOCKET_ERROR;
    }
    auto orig = (tRecvFrom)o_recvfrom.load();
    return orig ? orig(s, buf, len, flags, from, fromlen) : SOCKET_ERROR;
}
