//
//  @(#)client.h
//
//  sockets kit - client application class
//  --------------------------------------
//
//  copyright 2014-2015 Software Constructions (SC)
//
#ifndef __CLIENT_APPLICATION_H
#define __CLIENT_APPLICATION_H

#include <string>

//
//  Client application class.
//
class ClientApplication {
    public:
        ClientApplication(void);
        bool ProcessOptions(int, char **);
        void ProcessClientRequest(void);

    private:
        void DisplayOptionsUsage(void);
        void DisplayMissingOption(const std::string&);
        void DisplayInvalidOptionMessage(const std::string&);
        void DisplayInvalidOptionArgumentMessage(const std::string&);
        void DisplayErrorMessage(const std::string&);
        void DisplayVersion(void);

    private:
        std::string host_address;
        int port;
        std::string data;
};

#endif // __CLIENT_APPLICATION_H
