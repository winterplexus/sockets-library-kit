/*
**  @(#)client.h
**
**  sockets kit - client application class
**  --------------------------------------
**
**  copyright 2014 E. Spangler
*/
#ifndef __CLIENT_APPLICATION_H
#define __CLIENT_APPLICATION_H

#include <string>

/*
**  Default buffer size for receiving and sending data.
*/
const int DefaultBufferSize = 512;

/*
**  Client application class.
*/
class ClientApplication {
    public:
        ClientApplication();
        bool ProcessOptions(int, char **);
        void ProcessClientRequests(void);

    private:
        std::string host_address;
        int port;
        std::string data;

    private:
        void DisplayOptionsUsage(void);
        void DisplayMissingOption(const std::string&);
        void DisplayInvalidOptionMessage(const std::string&);
        void DisplayInvalidOptionArgumentMessage(const std::string&);
        void DisplayVersion(void);
};

#endif /* __CLIENT_APPLICATION_H */
