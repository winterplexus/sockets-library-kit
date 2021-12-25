//
//  @(#)sockets.cpp
//
//  sockets kit - sockets interface
//  -------------------------------
//
//  copyright 2014-2020 Code Construct Systems (CCS)
//
#include <string>
#include <stdexcept>
#include <winsock.h>
#include "sockets.h"

SocketsInterface::SocketsInterface(void) {
    if (WSAStartup(MAKEWORD(2, 0), &wsa_data) != 0) {
        throw (std::runtime_error(std::string("WSAStartup() failed")));
    }
}

SocketsInterface::~SocketsInterface(void) {
    WSACleanup();
}

SOCKET SocketsInterface::CreateSocket(void) {
    SOCKET client_socket;

    if ((client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        throw (std::runtime_error(std::string("socket() failed")));
    }
    return (client_socket);
}

SOCKET SocketsInterface::ConnectServer(SOCKET client_socket, const std::string &host_address, const int port) {
    if (!port) {
        throw (std::runtime_error(std::string("invalid port number")));
    }

    struct sockaddr_in socket_address;
    memset(&socket_address, 0, sizeof(socket_address));

    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = inet_addr(host_address.c_str());
    socket_address.sin_port = htons(port);

    if (connect(client_socket, (struct sockaddr *) & socket_address, sizeof(socket_address)) < 0) {
        throw (std::runtime_error(std::string("connect() failed")));
    }
    return (client_socket);
}

SOCKET SocketsInterface::BindSocket(SOCKET server_socket, const int port) {
    if (!port) {
        throw (std::runtime_error(std::string("invalid port number")));
    }

    struct sockaddr_in socket_address;
    memset(&socket_address, 0, sizeof(socket_address));

    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = htonl(INADDR_ANY);
    socket_address.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr *) & socket_address, sizeof(socket_address)) < 0) {
        throw (std::runtime_error(std::string("bind() failed")));
    }
    return (server_socket);
}

SOCKET SocketsInterface::ListenConnections(SOCKET server_socket, int pending_connections) {
    if (pending_connections < 1) {
        pending_connections = SOMAXCONN;
    }
    if (listen(server_socket, pending_connections) < 0) {
        throw (std::runtime_error(std::string("listen() failed")));
    }
    return (server_socket);
}

SOCKET SocketsInterface::AcceptConnections(const SOCKET server_socket) {
    SOCKET client_socket;

    struct sockaddr_in client_address;
    int client_address_length = sizeof(client_address);

    if ((client_socket = accept(server_socket, (struct sockaddr *) & client_address, &client_address_length)) < 0) {
        throw (std::runtime_error(std::string("accept() failed")));
    }
    return client_socket;
}

int SocketsInterface::SendRequest(const SOCKET client_socket, const char *buffer, const int buffer_size) {
    int send_size = 0;

    if (client_socket) {
        send_size = send(client_socket, buffer, buffer_size, 0);
    }
    return (send_size);
}

int SocketsInterface::ReceiveResponse(const SOCKET client_socket, char *buffer, const int buffer_size) {
    int receive_size = 0;

    if (client_socket) {
        memset(buffer, 0, buffer_size);
        receive_size = recv(client_socket, buffer, buffer_size, 0);
    }
    return (receive_size);
}

void SocketsInterface::CloseSocket(SOCKET socket) {
    if (socket) {
        closesocket(socket);
    }
}