/*
**  @(#)module.h
**
**  sockets kit - server module namespace
**  -------------------------------------
**
**  copyright 2014 E. Spangler
*/
#ifndef __SERVER_MODULE_H
#define __SERVER_MODULE_H

#include <winsock.h>
#include "sockets.h"

/*
**  Server module namespace.
*/
namespace  ServerModule
{
    const int DefaultBufferSize = 512;

    void HandleClientRequest(SocketsInterface *, SOCKET);
};

#endif /* __SERVER_MODULE_H */