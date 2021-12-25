/*
**  @(#)client.cpp
**
**  sockets kit - client application class
**  --------------------------------------
**
**  copyright 2014 E. Spangler
*/
#include <iostream>
#include <string>
#include "client.h"
#include "sockets.h"
#include "version.h"

/*
**  Console application.
*/
int main(int argc, char **argv)
{
    ClientApplication application;
    if (application.ProcessOptions(argc, argv)) {
        application.ProcessClientRequests();
    }
    return (0);
}

/*
**  Class constructor for client application.
*/
ClientApplication::ClientApplication()
{
    host_address = std::string("");
    port = 0;
    data = std::string("");
}

/*
**  Process options.
*/
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

/*
**  Process client requests.
*/
void ClientApplication::ProcessClientRequests(void)
{
    SocketsInterface sockets;
    char buffer[DefaultBufferSize];

    memset(buffer, 0, DefaultBufferSize);
    memcpy(buffer, data.c_str(), data.size());

    try {
        SOCKET client_socket = sockets.CreateSocket();

        sockets.ConnectServer(client_socket, host_address, port);
        std::cout << "connecting to " << host_address << " at port " << port << std::endl;

        sockets.SendRequest(client_socket, buffer, DefaultBufferSize);
        std::cout << "data sent     : " << buffer << std::endl;

        sockets.ReceiveRequest(client_socket, buffer, DefaultBufferSize);
        std::cout << "data received : " << buffer << std::endl;

        sockets.CloseSocket(client_socket);
    }
    catch (std::string& s) {
        std::cout << "error-> " << s << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "error-> " << std::string(e.what()) << std::endl;
    }
}

/*
**  Display options usage.
*/
void ClientApplication::DisplayOptionsUsage(void)
{
    std::cout << "usage: client -d [data] -h [host address] -p [port] -v" << std::endl << std::endl;
}

/*
**  Display missing option.
*/
void ClientApplication::DisplayMissingOption(const std::string& message)
{
    std::cout << std::endl << "error-> " << message << " option is missing" << std::endl;
}

/*
**  Display invalid option.
*/
void ClientApplication::DisplayInvalidOptionMessage(const std::string& option)
{
    std::cout << std::endl << "error-> invalid option: " << option << std::endl;
}

/*
**  Display invalid options argument.
*/
void ClientApplication::DisplayInvalidOptionArgumentMessage(const std::string& argument)
{
    std::cout << std::endl << "error-> missing option value or invalid option argument: " << argument << std::endl;
}

/*
**  Display version.
*/
void ClientApplication::DisplayVersion(void)
{
    std::cout << VersionString << std::endl << std::endl;
}
