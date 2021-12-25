/*
**  @(#)server.cpp
**
**  sockets kit - server class
**  --------------------------
**
**  copyright 2014 E. Spangler
*/
#include <string>
#include "log.h"
#include "module.h"
#include "server.h"
#include "sockets.h"

/*
**  Thread arguments structure.
*/
struct ThreadArguments {
    SocketsInterface *sockets;
    SOCKET            client_socket;
};

/*
**  Sockets interface.
*/
SocketsInterface Server::*sockets;

/*
**  Local function prototypes.
*/
void *ThreadRoutine(void *);

/*
**  Class constructor for server.
*/
Server::Server(const int port, const int pending_connections, const std::string& log_file_path, const bool trace_mode)
{
    sockets = new SocketsInterface();

    this->port = port;
    this->pending_connections = pending_connections;
    this->log_file_path = log_file_path;
    this->trace_mode = trace_mode;
}

/*
**  Class destructor for server.
*/
Server::~Server()
{
    sockets->~SocketsInterface();
}

/*
**  Serve requests with a maximum number of threads.
*/
void Server::ServerRequests(void)
{
    SOCKET server_socket = sockets->CreateSocket();
    if (trace_mode) {
        std::string trace_message = "server socket created " + std::to_string(server_socket);
        WriteTraceLogMessage(trace_message);
    }

    server_socket = sockets->BindSocket(server_socket, port);
    if (trace_mode) {
        std::string trace_message = "server socket bound to local address using server socket " + std::to_string(server_socket) + " and port number " + std::to_string(port);
        WriteTraceLogMessage(trace_message);
    }

    server_socket = sockets->ListenConnections(server_socket, pending_connections);
    if (trace_mode) {
        std::string trace_message = "server socket listening to connections using server socket " + std::to_string(server_socket) + " and pending connections (backlog) " + std::to_string(pending_connections);
        WriteTraceLogMessage(trace_message);
    }

    for (;;) {
        SOCKET client_socket = sockets->AcceptConnections(server_socket);
        if (trace_mode) {
            std::string trace_message = "accepted connection from client " + std::to_string(client_socket);
            WriteTraceLogMessage(trace_message);
        }

        struct ThreadArguments *thread_arguments = (struct ThreadArguments *)malloc(sizeof(struct ThreadArguments));
        if (!thread_arguments) {
            throw "insufficient memory for allocating thread argument structure";
        }

        thread_arguments->sockets = sockets;
        thread_arguments->client_socket = client_socket;

        if (trace_mode) {
            std::string trace_message = "thread arguments structure created for server socket " + std::to_string(server_socket);
            WriteTraceLogMessage(trace_message);
        }

        DWORD thread_id;
        if (CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadRoutine, thread_arguments, 0, (LPDWORD)&thread_id) == NULL) {
            throw "CreateThread() failed with thread argument client address " + std::to_string(thread_arguments->client_socket);
        }
        if (trace_mode) {
            std::string trace_message = "thread created (TID) " + std::to_string(thread_id);
            WriteTraceLogMessage(trace_message);
        }
    }
}

/*
**  Thread routine.
*/
void *ThreadRoutine(void *thread_arguments)
{
    if (thread_arguments) {
        ServerModule::HandleClientRequest(((struct ThreadArguments *)thread_arguments)->sockets, ((struct ThreadArguments *)thread_arguments)->client_socket);
    }
    free(thread_arguments);
    return (NULL);
}

/*
**  Write fatal log message to log file.
*/
void Server::WriteFatalLogMessage(const std::string& message)
{
    Log log = Log(log_file_path);
    log.WriteFatalLog(message);
}

/*
**  Write trace log message to log file.
*/
void Server::WriteTraceLogMessage(const std::string& message)
{
    Log log = Log(log_file_path);
    log.WriteTraceLog(message);
}
