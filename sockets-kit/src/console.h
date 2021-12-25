/*
**  @(#)console.h
**
**  sockets kit - console application class
**  ---------------------------------------
**
**  copyright 2014 E. Spangler
*/
#ifndef __CONSOLE_APPLICATION_H
#define __CONSOLE_APPLICATION_H

#include <string>

/*
**  Default port, pending connections limit and thread limit.
*/
const int DefaultPort = 16000;
const int DefaultPendingConnectionsLimit = 16;
const int DefaultThreadLimit = 32767;

/*
**  Console application class.
*/
class ConsoleApplication {
    public:
        ConsoleApplication();
        bool ProcessOptions(int, char **);
        void ProcessServerRequests(void);

    private:
        int port;
        int pending_connections;
        std::string log_file_path;
        bool trace_mode;

    private:
        void WriteFatalLogMessage(const std::string&);
        void DisplayOptionsUsage(void);
        void DisplayInvalidOptionMessage(const std::string&);
        void DisplayInvalidOptionArgumentMessage(const std::string&);
        void DisplayVersion(void);
};

#endif /* __CONSOLE_APPLICATION_H */
