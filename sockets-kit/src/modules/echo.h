//
//  @(#)echo.h
//
//  sockets kit - echo service namespace
//  ------------------------------------
//
//  copyright 2014-2017 Code Construct Systems (CCS)
//
#ifndef __ECHO_SERVICE_H
#define __ECHO_SERVICE_H

#include "../server.h"

//
//  Echo service namespace.
//
namespace EchoService 
{
    void HandleRequest(THREAD_ARGUMENTS *);

    const int EchoBufferSize = 10;
};

#endif // __ECHO_SERVICE_H