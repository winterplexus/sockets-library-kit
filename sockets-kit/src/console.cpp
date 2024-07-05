//
//  @(#)console.cpp
//
//  sockets kit - console application              `
//  ---------------------------------
//
//  copyright 2014-2024 Code Construct Systems (CCS)
//
#include <iostream>
#include <string>
#include "console.h"
#include "server.h"
#include "version.h"

int main(int argc, char **argv) {
    ConsoleApplication application;

    if (application.ProcessOptions(argc, argv)) {
        application.ProcessServerRequests();
    }
    return (0);
}

ConsoleApplication::ConsoleApplication() {
    port_number = 0;
    pending_connections = DefaultPendingConnectionsLimit;
    trace_mode = false;
}

bool ConsoleApplication::ProcessOptions(int argc, char **argv) {
    int i;

    if (argc == 1) {
        DisplayOptionsUsage();
        return (false);
    }

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-b") == 0) {
            if (!argv[++i]) {
                DisplayInvalidOptionArgumentMessage("pending connections");
                return (false);
            }
            pending_connections = atoi(argv[i]);
        }
        else if (strcmp(argv[i], "-l") == 0) {
            if (!argv[++i]) {
                DisplayInvalidOptionArgumentMessage("log file path");
                return (false);
            }
            log_file_path = std::string(argv[i]);
        }
        else if (strcmp(argv[i], "-p") == 0) {
            if (!argv[++i]) {
                DisplayInvalidOptionArgumentMessage("port number");
                return (false);
            }
            port_number = atoi(argv[i]);
        }
        else if (strcmp(argv[i], "-x") == 0) {
            trace_mode = true;
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

    if (port_number < 1) {
        DisplayMissingOptionMessage("port number");
        return (false);
    }

    return (true);
}

void ConsoleApplication::ProcessServerRequests(void) {
    Server *server = new Server(port_number, pending_connections, log_file_path, trace_mode);

    try {
        server->ServerRequests();
    }
    catch (std::exception &e) {
        DisplayErrorMessage(std::string(e.what()));
    }

    delete server;
}

void ConsoleApplication::DisplayOptionsUsage(void) {
    std::cout << "usage: console-server.exe (options)" << std::endl << std::endl;
    std::cout << "where (options) include:" << std::endl << std::endl;
    std::cout << "-b  [pending connections backlog length]" << std::endl;
    std::cout << "-l  [log file path name (excluding file extension)]" << std::endl;
    std::cout << "-p  [port IP number]" << std::endl;
    std::cout << "-v  display version" << std::endl;
    std::cout << "-x  enable trace mode" << std::endl;
}

void ConsoleApplication::DisplayInvalidOptionMessage(const std::string &option) {
    std::cout << std::endl << "error-> invalid option: " << option << std::endl;
}

void ConsoleApplication::DisplayInvalidOptionArgumentMessage(const std::string &argument) {
    std::cout << std::endl << "error-> missing option value or invalid option argument: " << argument << std::endl;
}

void ConsoleApplication::DisplayMissingOptionMessage(const std::string &message) {
    std::cout << std::endl << "error-> " << message << " option is missing" << std::endl;
}

void ConsoleApplication::DisplayErrorMessage(const std::string &message) {
    std::cout << "error-> " << message << std::endl;
}

void ConsoleApplication::DisplayVersion(void) {
    std::cout << VersionRelease << std::endl;
}