//
//  @(#)console.cpp
//
//  sockets kit - console application class
//  ---------------------------------------
//
//  copyright 2014-2015 Software Constructions (SC)
//
#include <iostream>
#include <string>
#include "console.h"
#include "log.h"
#include "server.h"
#include "version.h"

//
//  Console application.
//
int main(int argc, char **argv)
{
    ConsoleApplication application;
    if (application.ProcessOptions(argc, argv)) {
        application.ProcessServerRequests();
    }
    return (0);
}

//
//  Class constructor for console application.
//
ConsoleApplication::ConsoleApplication()
{
    port = DefaultPort;
    pending_connections = DefaultPendingConnectionsLimit;
    trace_mode = false;
}

//
//  Process options.
//
bool ConsoleApplication::ProcessOptions(int argc, char **argv)
{
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

//
//  Process server requests.
//
void ConsoleApplication::ProcessServerRequests(void)
{
    try {
        Server server = Server(port, pending_connections, log_file_path, trace_mode);
        server.ServerRequests();
    }
    catch (std::exception& e) {
        std::string exception_message = std::string("error-> " + std::string(e.what()));
        WriteFatalLogMessage(exception_message);
    }
}

//
//  Write fatal log message to log file.
//
void ConsoleApplication::WriteFatalLogMessage(const std::string& message)
{
    Log log = Log(log_file_path);
    log.WriteFatalLog(message);
}

//
//  Display options usage.
//
void ConsoleApplication::DisplayOptionsUsage(void)
{
    std::cout << "usage : server-console -b [pending connections] -l [log file path] -p [port] -v - x" << std::endl << std::endl;
}

//
//  Display invalid option.
//
void ConsoleApplication::DisplayInvalidOptionMessage(const std::string& option)
{
    std::cout << std::endl << "error-> invalid option: " << option << std::endl;
}

//
//  Display invalid options argument.
//
void ConsoleApplication::DisplayInvalidOptionArgumentMessage(const std::string& argument)
{
    std::cout << std::endl << "error-> missing option value or invalid option argument: " << argument << std::endl;
}

//
//  Display version.
//
void ConsoleApplication::DisplayVersion(void)
{
    std::cout << VersionString << std::endl;
    std::cout << "server-console" << std::endl << std::endl;
}
