/*
**  @(#)module.cpp
**
**  sockets kit - server module namespace
**  -------------------------------------
**
**  copyright 2014 E. Spangler
*/
#include <string>
#include <winsock.h>
#include "module.h"

/*
**  Server module namespace.
*/
namespace  ServerModule
{
    /*
    **  Handle client request.
    */
    void ServerModule::HandleClientRequest(SocketsInterface *sockets, SOCKET client_socket)
    {
        char *buffer = NULL;
        int message_size;

        if ((buffer = (char *)malloc(DefaultBufferSize)) == NULL) {
            return;
        }

        message_size = sockets->ReceiveRequest(client_socket, buffer, DefaultBufferSize);
        sockets->SendRequest(client_socket, buffer, DefaultBufferSize);
        sockets->CloseSocket(client_socket);

        free(buffer);
    }
}
