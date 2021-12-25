/*
**  @(#)sockets.cpp
**
**  sockets kit - sockets interface class
**  -------------------------------------
**
**  copyright 2014 E. Spangler
*/
#include <string>
#include <winsock.h>
#include "log.h"
#include "sockets.h"

/*
**  Class constructor for sockets interface.
*/
SocketsInterface::SocketsInterface()
{
    if (WSAStartup(MAKEWORD(2, 0), &wsa_data) != 0) {
        throw "WSAStartup() failed";
    }
}

/*
**  Class destructor for sockets interface.
*/
SocketsInterface::~SocketsInterface()
{
    WSACleanup();
}

/*
**  Create a socket.
*/
SOCKET SocketsInterface::CreateSocket(void)
{
    SOCKET client_socket;
    if ((client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        std::string exception_message = "socket() failed using address family PF_INET, socket type SOCK_STREAM and protocol IPPROTO_TCP";
        throw exception_message;
    }
    return (client_socket);
}

/*
**  Connect to server using client socket, IP address and port number.
*/
SOCKET SocketsInterface::ConnectServer(SOCKET client_socket, const std::string& host_address, const int port)
{
    if (!port) {
        std::string exception_message = "connect() failed (port number is out of range) using client socket " + std::to_string(client_socket) + ", host address " + host_address + " and port " + std::to_string(port);
        throw exception_message;
    }

    struct sockaddr_in socket_address;
    memset(&socket_address, 0, sizeof(socket_address));
    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = inet_addr(host_address.c_str());
    socket_address.sin_port = htons(port);

    if (connect(client_socket, (struct sockaddr *)&socket_address, sizeof(socket_address)) < 0) {
        std::string exception_message = "connect() failed using client socket " + std::to_string(client_socket) + ", host address " + host_address + " and port " + std::to_string(port);
        throw exception_message;
    }
    return (client_socket);
}

/*
**  Bind socket to local address using server socket and port number.
*/
SOCKET SocketsInterface::BindSocket(SOCKET server_socket, const int port)
{
    if (!port) {
        std::string exception_message = "connect() failed (port number is out of range) using server socket " + std::to_string(server_socket) + std::to_string(port);
        throw exception_message;
    }

    struct sockaddr_in socket_address;
    memset(&socket_address, 0, sizeof(socket_address));
    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = htonl(INADDR_ANY);
    socket_address.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr *)&socket_address, sizeof(socket_address)) < 0) {
        std::string exception_message = "bind() failed using server socket " + std::to_string(server_socket) + "and port " + std::to_string(port);
        throw exception_message;
    }
    return (server_socket);
}

/*
**  Listen for connections using server socket and pending connections (limit).
*/
SOCKET SocketsInterface::ListenConnections(SOCKET server_socket, int pending_connections)
{
    if (pending_connections < 1) {
        pending_connections = SOMAXCONN;
    }
    if (listen(server_socket, pending_connections) < 0) {
        std::string exception_message = "listen() failed using server socket " + std::to_string(server_socket) + " and pending connections limit (backlog) " + std::to_string(pending_connections);
        throw exception_message;
    }
    return (server_socket);
}

/*
**  Accept a connection using server socket returning a client socket.
*/
SOCKET SocketsInterface::AcceptConnections(const SOCKET server_socket)
{
    SOCKET client_socket;
    struct sockaddr_in client_address;
    int client_address_length = sizeof(client_address);

    if ((client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_length)) < 0) {
        std::string exception_message = "accept() failed using server socket " + std::to_string(server_socket);
        throw exception_message;
    }
    return client_socket;
}

/*
**  Send request using client socket, buffer and buffer size.
*/
int SocketsInterface::SendRequest(const SOCKET client_socket, const char *buffer, const int buffer_size)
{
    int send_size;

    if ((send_size = send(client_socket, buffer, buffer_size, 0)) != buffer_size) {
        throw "send() failed with buffer size " + std::to_string(buffer_size);
    }
    return (send_size);
}

/*
**  Receive request using client socket, buffer and buffer size.
*/
int SocketsInterface::ReceiveRequest(const SOCKET client_socket, char *buffer, const int buffer_size)
{
    int receive_size;

    memset(buffer, 0, buffer_size);
    if ((receive_size = recv(client_socket, buffer, buffer_size, 0)) < 0) {
        throw "recv() failed with buffer size " + std::to_string(buffer_size);
    }
    return (receive_size);
}

/*
**  Close socket.
*/
void SocketsInterface::CloseSocket(SOCKET socket)
{
    if (socket) {
        closesocket(socket);
    }
}
