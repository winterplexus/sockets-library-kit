/*
**  @(#)sockets.cpp
**
**  sockets kit - sockets interface class
**  -------------------------------------
**
**  copyright 2014 E. Spangler
*/
#ifndef __SOCKETS_H
#define __SOCKETS_H

#include <winsock.h>

/*
**  Sockets interface class.
*/
class SocketsInterface {
    public:
        SocketsInterface();
       ~SocketsInterface();
        SOCKET CreateSocket(void);
        SOCKET BindSocket(SOCKET, const int);
        SOCKET ListenConnections(SOCKET, int);
        SOCKET AcceptConnections(const SOCKET);
        SOCKET ConnectServer(SOCKET, const std::string&, const int);
        int SendRequest(const SOCKET, const char *, const int);
        int ReceiveRequest(const SOCKET, char *, const int);
        void CloseSocket(SOCKET);

    private:
        WSADATA wsa_data;
};

#endif /* __SOCKETS_H */