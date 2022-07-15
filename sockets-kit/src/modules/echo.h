//
//  @(#)echo.h
//
//  sockets kit - echo service
//  --------------------------
//
//  copyright 2014-2022 Code Construct Systems (CCS)
//
#ifndef __ECHO_H
#define __ECHO_H

#include <cstdio>
#include "../server.h"

namespace EchoService {
        void HandleRequest(THREAD_ARGUMENTS *);
        const int EchoBufferSize = BUFSIZ;
};

#endif // __ECHO_H