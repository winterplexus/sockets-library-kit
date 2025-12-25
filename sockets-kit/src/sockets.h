//
//  @(#)sockets.h
//
//  sockets kit - sockets interface
//  -------------------------------
//
//  copyright 2014-2025 Code Construct Systems (CCS)
//
#ifndef __SOCKETS_H
#define __SOCKETS_H

#define WIN32_LEAN_AND_MEAN
#include <winsock.h>

#ifdef  _SOCKETS_INTERFACE_DLL_EXPORTS
#define _SOCKETS_INTERFACE_API __declspec(dllexport)
#else
#define _SOCKETS_INTERFACE_API __declspec(dllimport)
#endif

class _SOCKETS_INTERFACE_API SocketsInterface {
public:
    SocketsInterface(void);
    SocketsInterface(int, int, int);
   ~SocketsInterface(void);
    SOCKET CreateSocket(void);
    SOCKET BindSocket(SOCKET, const int);
    SOCKET ListenConnections(SOCKET, int);
    SOCKET AcceptConnections(const SOCKET);
    SOCKET ConnectServer(SOCKET, const char *, const int);
    int SendRequest(const SOCKET, const char *, const int);
    int ReceiveResponse(const SOCKET, char *, const int);
    void CloseSocket(SOCKET);
private:
    int address_family = AF_INET;
    int socket_type = SOCK_STREAM;
    int ip_protocol = IPPROTO_TCP;
    WSADATA wsa_data;
};

#endif __SOCKETS_H