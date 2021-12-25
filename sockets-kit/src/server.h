//
//  @(#)server.h
//
//  sockets kit - server
//  --------------------
//
//  copyright 2014-2020 Code Construct Systems (CCS)
//
#ifndef __SERVER_H
#define __SERVER_H

#include <string>
#include "log.h"
#include "sockets.h"

typedef struct ThreadArguments {
        SocketsInterface *ta_sockets;
        SOCKET ta_client_socket;
        LogFile *ta_server_log;
        bool ta_server_log_trace_mode;
} THREAD_ARGUMENTS;

class Server {
public:
        Server(const int, const int, const std::string &, const bool);
       ~Server(void);
        void ServerRequests(void);

private:
        int port;
        int pending_connections;
        std::string log_file_path;
        bool trace_mode;
        SocketsInterface *sockets;
        LogFile *server_log;
};

#endif // __SERVER_H