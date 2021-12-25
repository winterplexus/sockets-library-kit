//
//  @(#)client.cpp
//
//  sockets kit - client application class
//  --------------------------------------
//
//  copyright 2014-2020 Code Construct Systems (CCS)
//
#include <iostream>
#include <string>
#include "client.h"
#include "sockets.h"
#include "version.h"

int main(int argc, char **argv) {
    ClientApplication application;
    if (application.ProcessOptions(argc, argv)) {
        application.ProcessClientRequest();
    }
    return (0);
}

ClientApplication::ClientApplication(void) {
    host_address = std::string("");
    port = 0;
    data = std::string("");
}

bool ClientApplication::ProcessOptions(int argc, char **argv) {
    if (argc == 1) {
        DisplayOptionsUsage();
        return (false);
    }

    for (int i = 1; i < argc; i++) {
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

void ClientApplication::ProcessClientRequest(void) {
    char *buffer;
    int buffer_size = data.size();

    if ((buffer = (char *)malloc(buffer_size + 1)) == NULL) {
        DisplayErrorMessage(std::string("insufficient memory to allocating client request buffer"));
        return;
    }

    memset(buffer, 0, buffer_size + 1);

    try {
        SocketsInterface sockets;
        SOCKET client_socket = sockets.CreateSocket();

        sockets.ConnectServer(client_socket, host_address, port);
        std::cout << "connecting to " << host_address << " at port " << port << std::endl;

        int bytes_sent = sockets.SendRequest(client_socket, data.c_str(), data.size());
        std::cout << data << std::endl;

        int total_bytes_received = 0;
        while (total_bytes_received < bytes_sent) {
            int bytes_received = sockets.ReceiveResponse(client_socket, buffer, buffer_size);
            if (bytes_received < 1) {
                break;
            }

            total_bytes_received += bytes_received;

            std::cout << std::string(buffer);
            memset(buffer, 0, buffer_size + 1);
        }

        sockets.CloseSocket(client_socket);

        std::cout << std::endl << std::endl;
        std::cout << "bytes sent: " << bytes_sent << std::endl;
        std::cout << "bytes received: " << total_bytes_received << std::endl;
    }
    catch (std::exception &e) {
        DisplayErrorMessage(std::string(e.what()));
    }

    free(buffer);
}

void ClientApplication::DisplayOptionsUsage(void) {
    std::cout << "usage: client.exe (options)" << std::endl << std::endl;
    std::cout << "where (options) include:" << std::endl;
    std::cout << "  -d  [data]" << std::endl;
    std::cout << "  -h  [host address]" << std::endl;
    std::cout << "  -p  [port number]" << std::endl;
    std::cout << "  -v  display version" << std::endl;
}

void ClientApplication::DisplayMissingOption(const std::string &message) {
    std::cout << std::endl << "error-> " << message << " option is missing" << std::endl;
}

void ClientApplication::DisplayInvalidOptionMessage(const std::string &option) {
    std::cout << std::endl << "error-> invalid option: " << option << std::endl;
}

void ClientApplication::DisplayInvalidOptionArgumentMessage(const std::string &argument) {
    std::cout << std::endl << "error-> missing option value or invalid option argument: " << argument << std::endl;
}

void ClientApplication::DisplayErrorMessage(const std::string &message) {
    std::cout << "error-> " << message << std::endl;
}

void ClientApplication::DisplayVersion(void) {
    std::cout << VersionRelease << std::endl;
    std::cout << "client" << std::endl << std::endl;
}