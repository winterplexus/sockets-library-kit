/*
**  @(#)server.h
**
**  sockets kit - server class
**  --------------------------
**
**  copyright 2014 E. Spangler
*/
#ifndef __SERVER_H
#define __SERVER_H

#include <string>
#include "sockets.h"

/*
**  Server class.
*/
class Server {
    public:
        Server(const int, const int, const std::string&, const bool);
       ~Server();
        void ServerRequests(void);

    private:
        SocketsInterface *sockets;
        int port;
        int pending_connections;
        std::string log_file_path;
        bool trace_mode;

    private:
        void WriteFatalLogMessage(const std::string&);
        void WriteTraceLogMessage(const std::string&);
};

#endif /* __SERVER_H */