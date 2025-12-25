//
//  @(#)client.cpp
//
//  sockets kit - client application class
//  --------------------------------------
//
//  copyright 2014-2025 Code Construct Systems (CCS)
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
    port_number = 0;
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
                DisplayInvalidOptionArgumentMessage("port number");
                return (false);
            }
            port_number = atoi(argv[i]);
        }
        else if (strcmp(argv[i], "-v") == 0) {
            DisplayVersion();
        }
        else if (strcmp(argv[i], "-?") == 0) {
            DisplayOptionsUsage();
            return (false);
        }
        else {
            DisplayInvalidOptionMessage(std::string(argv[i]));
        }
    }

    if (host_address.size() < 1) {
        DisplayMissingOptionMessage("host address");
        return (false);
    }
    if (!port_number) {
        DisplayMissingOptionMessage("port number");
        return (false);
    }

    return (true);
}

void ClientApplication::ProcessClientRequest(void) {
    char *buffer;
    int buffer_size = (int)data.size() + 1;

    if ((buffer = new char[buffer_size]) == NULL) {
        DisplayErrorMessage(std::string("insufficient memory to allocating client request buffer"));
        return;
    }

    memset(buffer, 0, buffer_size);

    SocketsInterface *sockets = new SocketsInterface();

    try {
        SOCKET client_socket = sockets->CreateSocket();

        sockets->ConnectServer(client_socket, host_address.c_str(), port_number);
        std::cout << "connecting to: " << host_address << " at port number: " << port_number << std::endl;

        size_t bytes_sent = sockets->SendRequest(client_socket, data.c_str(), (int)data.size());
        std::cout << data << std::endl;

        size_t total_bytes_received = 0;
        while (total_bytes_received < bytes_sent) {
            size_t bytes_received = sockets->ReceiveResponse(client_socket, buffer, buffer_size);
            if (bytes_received < 1) {
                break;
            }

            total_bytes_received += bytes_received;

            std::cout << std::string(buffer);
            memset(buffer, 0, buffer_size);
        }

        sockets->CloseSocket(client_socket);

        std::cout << std::endl << std::endl;
        std::cout << "bytes sent: " << bytes_sent << std::endl;
        std::cout << "bytes received: " << total_bytes_received << std::endl;
    }
    catch (std::exception &e) {
        DisplayErrorMessage(std::string(e.what()));
    }

    delete sockets;
    delete[] buffer;
}

void ClientApplication::DisplayOptionsUsage(void) {
    std::cout << "usage: client.exe (options)" << std::endl << std::endl;
    std::cout << "options: -d <data>" << std::endl;
    std::cout << "         -h <host IP address>" << std::endl;
    std::cout << "         -p <port IP number>" << std::endl;
    std::cout << "         -v print version" << std::endl;
    std::cout << "         -? print this usage" << std::endl;
}

void ClientApplication::DisplayInvalidOptionMessage(const std::string &option) {
    std::cerr << std::endl << "error-> invalid option: " << option << std::endl;
}

void ClientApplication::DisplayInvalidOptionArgumentMessage(const std::string &argument) {
    std::cerr << std::endl << "error-> missing option value or invalid option argument: " << argument << std::endl;
}

void ClientApplication::DisplayMissingOptionMessage(const std::string &message) {
    std::cerr << std::endl << "error-> " << message << " option is missing" << std::endl;
}

void ClientApplication::DisplayErrorMessage(const std::string &message) {
    std::cerr << "error-> " << message << std::endl;
}

void ClientApplication::DisplayVersion(void) {
    std::cout << VersionRelease << std::endl;
}