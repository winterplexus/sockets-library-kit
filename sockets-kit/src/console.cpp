//
//  @(#)console.cpp
//
//  sockets kit - console application
//  ---------------------------------
//
//  copyright 2014-2020 Code Construct Systems (CCS)
//
#include <iostream>
#include <string>
#include "console.h"
#include "log.h"
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
    port = DefaultPort;
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
                DisplayInvalidOptionArgumentMessage("port");
                return (false);
            }
            port = atoi(argv[i]);
        }
        else if (strcmp(argv[i], "-x") == 0) {
            trace_mode = true;
        }
        else if (strcmp(argv[i], "-v") == 0) {
            DisplayVersion();
        }
        else {
            DisplayInvalidOptionMessage(std::string(argv[i]));
        }
    }

    return (true);
}

void ConsoleApplication::ProcessServerRequests(void) {
    try {
        Server server = Server(port, pending_connections, log_file_path, trace_mode);
        server.ServerRequests();
    }
    catch (std::exception &e) {
        std::string exception_message = std::string("error-> " + std::string(e.what()));
        WriteFatalLogMessage(exception_message);
    }
}

void ConsoleApplication::WriteFatalLogMessage(const std::string &message) {
    LogFile log = LogFile(log_file_path);
    log.WriteFatalLog(message);
}

void ConsoleApplication::DisplayOptionsUsage(void) {
    std::cout << "usage: server-console.exe (options)" << std::endl << std::endl;
    std::cout << "where (options) include:" << std::endl;
    std::cout << "  -b  [pending connections backlog length]" << std::endl;
    std::cout << "  -l  [log file path]" << std::endl;
    std::cout << "  -p  [port number]" << std::endl;
    std::cout << "  -v  display version" << std::endl;
    std::cout << "  -x  enable trace mode" << std::endl;
}

void ConsoleApplication::DisplayInvalidOptionMessage(const std::string &option) {
    std::cout << std::endl << "error-> invalid option: " << option << std::endl;
}

void ConsoleApplication::DisplayInvalidOptionArgumentMessage(const std::string &argument) {
    std::cout << std::endl << "error-> missing option value or invalid option argument: " << argument << std::endl;
}

void ConsoleApplication::DisplayVersion(void) {
    std::cout << VersionRelease << std::endl;
    std::cout << "server-console" << std::endl << std::endl;
}