Sockets Library Kit for C++
===========================

Sockets library kit based on C++ for implementing Windows-based TCP/IP socket application.

The kit includes the following features:

* TCP/IP client that sends messages to a server.

* TCP/IP server that receives and returns messages sent by a client.

* Thread-safe log file (which is used by the TCP/IP server to trace socket activity and error conditions).

The kit includes the following component(s):

* Sockets C++ class:

```
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
```

Sockets library is supported on Windows operating systems only.
