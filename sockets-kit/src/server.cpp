//
//  @(#)server.cpp
//
//  sockets kit - server
//  ---------------------
//
//  copyright 2014-2020 Code Construct Systems (CCS)
//
#include <stdexcept>
#include <string>
#include "log.h"
#include "server.h"
#include "sockets.h"
#include "modules/echo.h"

SocketsInterface Server:: *sockets;
LogFile Server:: *server_log;

void *ThreadRoutine(void *);

Server::Server(const int port, const int pending_connections, const std::string &log_file_path, const bool trace_mode) {
    this->port = port;
    this->pending_connections = pending_connections;
    this->log_file_path = log_file_path;
    this->trace_mode = trace_mode;

    sockets = new SocketsInterface();
    server_log = new LogFile(log_file_path);
}

Server::~Server(void) {
    sockets->~SocketsInterface();
    server_log->~LogFile();
}

void Server::ServerRequests(void) {
    SOCKET server_socket = sockets->CreateSocket();

    if (trace_mode) {
        std::string trace_message = std::string("server socket created " + std::to_string(server_socket));
        server_log->WriteTraceLog(trace_message);
    }

    server_socket = sockets->BindSocket(server_socket, port);

    if (trace_mode) {
        std::string trace_message = std::string("server socket bound to local address using server socket " + std::to_string(server_socket) + " and port number " + std::to_string(port));
        server_log->WriteTraceLog(trace_message);
    }

    server_socket = sockets->ListenConnections(server_socket, pending_connections);

    if (trace_mode) {
        std::string trace_message = std::string("server socket listening to connections using server socket " + std::to_string(server_socket) + " and pending connections backlog length " + std::to_string(pending_connections));
        server_log->WriteTraceLog(trace_message);
    }

    for (;;) {
        SOCKET client_socket = sockets->AcceptConnections(server_socket);

        if (trace_mode) {
            std::string trace_message = std::string("accepted connection from client " + std::to_string(client_socket));
            server_log->WriteTraceLog(trace_message);
        }

        struct ThreadArguments *thread_arguments = (struct ThreadArguments *)malloc(sizeof(struct ThreadArguments));
        if (!thread_arguments) {
            throw (std::runtime_error(std::string("insufficient memory for allocating thread arguments structure")));
        }

        thread_arguments->ta_sockets = sockets;
        thread_arguments->ta_client_socket = client_socket;
        thread_arguments->ta_server_log = server_log;
        thread_arguments->ta_server_log_trace_mode = trace_mode;

        if (trace_mode) {
            std::string trace_message = std::string("thread arguments structure created for server socket " + std::to_string(server_socket));
            server_log->WriteTraceLog(trace_message);
        }

        DWORD thread_id;
        if (CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadRoutine, thread_arguments, 0, (LPDWORD)&thread_id) == NULL) {
            throw (std::runtime_error(std::string("CreateThread() failed")));
        }

        if (trace_mode) {
            std::string trace_message = std::string("thread created (TID) " + std::to_string(thread_id));
            server_log->WriteTraceLog(trace_message);
        }
    }
}

void *ThreadRoutine(void *thread_arguments) {
    if (thread_arguments) {
        EchoService::HandleRequest(((THREAD_ARGUMENTS *)thread_arguments));
    }
    free(thread_arguments);
    return (NULL);
}