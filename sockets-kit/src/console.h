//
//  @(#)console.h
//
//  sockets kit - console application
//  ---------------------------------
//
//  copyright 2014-2022 Code Construct Systems (CCS)
//
#ifndef __CONSOLE_H
#define __CONSOLE_H

#define WIN32_LEAN_AND_MEAN
#include <string>

class ConsoleApplication {
public:
        ConsoleApplication();
        bool ProcessOptions(int, char **);
        void ProcessServerRequests(void);
private:
        const int DefaultPendingConnectionsLimit = 16;
        const int DefaultThreadLimit = 32767;
        int port_number;
        int pending_connections;
        std::string log_file_path;
        bool trace_mode;
private:
        void DisplayOptionsUsage(void);
        void DisplayInvalidOptionMessage(const std::string &);
        void DisplayInvalidOptionArgumentMessage(const std::string &);
        void DisplayMissingOptionMessage(const std::string &);
        void DisplayErrorMessage(const std::string &);
        void DisplayVersion(void);
};

#endif // __CONSOLE_H