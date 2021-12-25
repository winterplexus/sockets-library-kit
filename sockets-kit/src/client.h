//
//  @(#)client.h
//
//  sockets kit - client application class
//  --------------------------------------
//
//  copyright 2014-2020 Code Construct Systems (CCS)
//
#ifndef __CLIENT_H
#define __CLIENT_H

#include <string>

class ClientApplication {
public:
        ClientApplication(void);
        bool ProcessOptions(int, char **);
        void ProcessClientRequest(void);

private:
        void DisplayOptionsUsage(void);
        void DisplayMissingOption(const std::string &);
        void DisplayInvalidOptionMessage(const std::string &);
        void DisplayInvalidOptionArgumentMessage(const std::string &);
        void DisplayErrorMessage(const std::string &);
        void DisplayVersion(void);

private:
        std::string host_address;
        int port;
        std::string data;
};

#endif // __CLIENT_H