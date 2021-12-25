//
//  @(#)client.cpp
//
//  sockets kit - client application class
//  --------------------------------------
//
//  copyright 2014-2017 Code Construct Systems (CCS)
//
#include <iostream>
#include <string>
#include "client.h"
#include "sockets.h"
#include "version.h"

//
//  Client application.
//
int main(int argc, char **argv)
{
    ClientApplication application;
    if (application.ProcessOptions(argc, argv)) {
        application.ProcessClientRequest();
    }
    return (0);
}

//
//  Class constructor for client application.
//
ClientApplication::ClientApplication(void)
{
    host_address = std::string("");
    port = 0;
    data = std::string("");
}

//
//  Process options.
//
bool ClientApplication::ProcessOptions(int argc, char **argv)
{
    int i;

    if (argc == 1) {
        DisplayOptionsUsage();
        return (false);
    }

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0) {
            if (!argv[++i]) {
                DisplayInvalidOptionArgumentMessage("data");
                return (false);
            }
            data = std::string(argv[i]);
        }
        else if (strcmp(argv[i], "-h") == 0) {
            if (!argv[++i]) {
                DisplayInvalidOptionArgumentMessage("host address");
                return (false);
            }
            host_address = std::string(argv[i]);
        }
        else if (strcmp(argv[i], "-p") == 0) {
            if (!argv[++i]) {
                DisplayInvalidOptionArgumentMessage("port");
                return (false);
            }
            port = atoi(argv[i]);
        }
        else if (strcmp(argv[i], "-v") == 0) {
            DisplayVersion();
        }
        else {
            DisplayInvalidOptionMessage(std::string(argv[i]));
        }
    }

    if (host_address.size() < 1) {
        DisplayMissingOption("host address");
        return (false);
    }
    if (!port) {
        DisplayMissingOption("port");
        return (false);
    }

    return (true);
}

//
//  Process client request.
//
void ClientApplication::ProcessClientRequest(void)
{
    SocketsInterface sockets;
    char *buffer;
    int buffer_size = data.size();

    if ((buffer = (char *)malloc(buffer_size + 1)) == NULL) {
        DisplayErrorMessage(std::string("insufficient memory to allocating client request buffer"));
        return;
    }

    memset(buffer, 0, buffer_size + 1);

    try {
        SOCKET client_socket = sockets.CreateSocket();

        sockets.ConnectServer(client_socket, host_address, port);
        std::cout << "connecting to " << host_address << " at port " << port << std::endl;

        int bytes_sent = sockets.SendRequest(client_socket, data.c_str(), data.size());
        std::cout << data << std::endl;

        int total_bytes_received = 0;
        while (total_bytes_received < bytes_sent) {
            int bytes_received = sockets.ReceiveRequest(client_socket, buffer, buffer_size);
            if (bytes_received < 0) {
                break;
            }
            std::cout << std::string(buffer);
            total_bytes_received += bytes_received;
            memset(buffer, 0, buffer_size + 1);
        }

        std::cout << std::endl;

        sockets.CloseSocket(client_socket);
    }
    catch (std::exception& e) {
        DisplayErrorMessage(std::string(e.what()));
    }

    free(buffer);
}

//
//  Display options usage.
//
void ClientApplication::DisplayOptionsUsage(void)
{
    std::cout << "usage: client -d [data] -h [host address] -p [port] -v" << std::endl << std::endl;
}

//
//  Display missing option.
//
void ClientApplication::DisplayMissingOption(const std::string& message)
{
    std::cout << std::endl << "error-> " << message << " option is missing" << std::endl;
}

//
//  Display invalid option.
//
void ClientApplication::DisplayInvalidOptionMessage(const std::string& option)
{
    std::cout << std::endl << "error-> invalid option: " << option << std::endl;
}

//
//  Display invalid options argument.
//
void ClientApplication::DisplayInvalidOptionArgumentMessage(const std::string& argument)
{
    std::cout << std::endl << "error-> missing option value or invalid option argument: " << argument << std::endl;
}

//
//  Display error message.
//
void ClientApplication::DisplayErrorMessage(const std::string& message)
{
    std::cout << "error-> " << message << std::endl;
}

//
//  Display version.
//
void ClientApplication::DisplayVersion(void)
{
    std::cout << VersionString << std::endl;
    std::cout << "client" << std::endl << std::endl;
}
