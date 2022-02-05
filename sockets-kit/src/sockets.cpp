//
//  @(#)sockets.cpp
//
//  sockets kit - sockets interface
//  -------------------------------
//
//  copyright 2014-2022 Code Construct Systems (CCS)
//
#define WIN32_LEAN_AND_MEAN

#include <string>
#include <stdexcept>
#include <winsock.h>
#include "sockets.h"

SocketsInterface::SocketsInterface(void) {
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
        WSACleanup();
        throw (std::runtime_error(std::string("WSAStartup() failed")));
    }
}

SocketsInterface::SocketsInterface(int addres_family, int socket_type, int ip_protocol) {
    this->address_family = address_family;
    this->socket_type = socket_type;
    this->ip_protocol = ip_protocol;

    if (WSAStartup(MAKEWORD(2, 0), &wsa_data) != 0) {
        WSACleanup();
        throw (std::runtime_error(std::string("WSAStartup() failed")));
    }
}

SocketsInterface::~SocketsInterface(void) {
    WSACleanup();
}

SOCKET SocketsInterface::CreateSocket(void) {
    SOCKET client_socket;

    if ((client_socket = socket(address_family, socket_type, ip_protocol)) < 0) {
        throw (std::runtime_error(std::string("socket() failed")));
    }
    return (client_socket);
}

SOCKET SocketsInterface::BindSocket(SOCKET server_socket, const int port_number) {
    if (server_socket == NULL) {
        throw (std::runtime_error(std::string("server_socket parameter is null")));
    }
    if (port_number < 1) {
        throw (std::runtime_error(std::string("port_number parameter is less than 1")));
    }

    struct sockaddr_in socket_address;
    memset(&socket_address, 0, sizeof(socket_address));

    socket_address.sin_family = address_family;
    socket_address.sin_addr.s_addr = htonl(INADDR_ANY);
    socket_address.sin_port = htons(port_number);

    if (bind(server_socket, (struct sockaddr *)&socket_address, sizeof(socket_address)) < 0) {
        throw (std::runtime_error(std::string("bind() failed")));
    }
    return (server_socket);
}

SOCKET SocketsInterface::ListenConnections(SOCKET server_socket, int pending_connections) {
    if (server_socket == NULL) {
        throw (std::runtime_error(std::string("server_socket parameter is null")));
    }
    if (pending_connections < 1) {
        pending_connections = SOMAXCONN;
    }

    if (listen(server_socket, pending_connections) < 0) {
        throw (std::runtime_error(std::string("listen() failed")));
    }
    return (server_socket);
}

SOCKET SocketsInterface::AcceptConnections(const SOCKET server_socket) {
    if (server_socket == NULL) {
        throw (std::runtime_error(std::string("server_socket parameter is null")));
    }

    SOCKET client_socket;
    struct sockaddr_in client_address {};
    int client_address_length = sizeof(client_address);

    if ((client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_length)) < 0) {
        throw (std::runtime_error(std::string("accept() failed")));
    }
    return client_socket;
}

SOCKET SocketsInterface::ConnectServer(SOCKET client_socket, const char *host_address, const int port_number) {
    if (client_socket == NULL) {
        throw (std::runtime_error(std::string("client_socket parameter is null")));
    }
    if (!host_address) {
        throw (std::runtime_error(std::string("host_address parameter is null")));
    }
    if (port_number < 1) {
        throw (std::runtime_error(std::string("port_number parameter is less than 1")));
    }

    struct sockaddr_in socket_address;
    memset(&socket_address, 0, sizeof(socket_address));

    socket_address.sin_family = address_family;
    socket_address.sin_addr.s_addr = inet_addr(host_address);
    socket_address.sin_port = htons(port_number);

    if (connect(client_socket, (struct sockaddr *)&socket_address, sizeof(socket_address)) < 0) {
        throw (std::runtime_error(std::string("connect() failed")));
    }
    return (client_socket);
}

int SocketsInterface::SendRequest(const SOCKET client_socket, const char *buffer, const int buffer_size) {
    if (client_socket == NULL) {
        throw (std::runtime_error(std::string("client_socket parameter is null")));
    }
    if (!buffer) {
        throw (std::runtime_error(std::string("buffer parameter is null")));
    }
    if (buffer_size < 1) {
        throw (std::runtime_error(std::string("buffer_size parameter is less than 1")));
    }

    int send_size = 0;

    if (client_socket) {
        send_size = send(client_socket, buffer, buffer_size, 0);
    }
    return (send_size);
}

int SocketsInterface::ReceiveResponse(const SOCKET client_socket, char *buffer, const int buffer_size) {
    if (client_socket == NULL) {
        throw (std::runtime_error(std::string("client_socket is null")));
    }
    if (buffer_size < 1) {
        throw (std::runtime_error(std::string("buffer_size parameter is less than 1")));
    }

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