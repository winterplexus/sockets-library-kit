//
//  @(#)server.h
//
//  sockets kit - server class
//  --------------------------
//
//  copyright 2014-2015 Software Constructions (SC)
//
#ifndef __SERVER_H
#define __SERVER_H

#include <string>
#include "log.h"
#include "sockets.h"

//
//  Thread arguments structure and type.
//
typedef struct ThreadArguments {
    SocketsInterface *ta_sockets;
    SOCKET            ta_client_socket;
    Log              *ta_server_log;
    bool              ta_server_log_trace_mode;
} THREAD_ARGUMENTS;

//
//  Server class.
//
class Server {
    public:
        Server(const int, const int, const std::string&, const bool);
       ~Server(void);
        void ServerRequests(void);

    private:
        int port;
        int pending_connections;
        std::string log_file_path;
        bool trace_mode;
        SocketsInterface *sockets;
        Log *server_log;
};

#endif // __SERVER_H