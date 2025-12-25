//
//  @(#)client.h
//
//  sockets kit - client application class
//  --------------------------------------
//
//  copyright 2014-2025 Code Construct Systems (CCS)
//
#ifndef __CLIENT_H
#define __CLIENT_H

#define WIN32_LEAN_AND_MEAN

#include <string>

class ClientApplication {
public:
    ClientApplication(void);
    bool ProcessOptions(int, char **);
    void ProcessClientRequest(void);
private:
    std::string host_address;
    int port_number;
    std::string data;
private:
    void DisplayOptionsUsage(void);
    void DisplayInvalidOptionMessage(const std::string &);
    void DisplayInvalidOptionArgumentMessage(const std::string &);
    void DisplayMissingOptionMessage(const std::string &);
    void DisplayErrorMessage(const std::string &);
    void DisplayVersion(void);
};

#endif // __CLIENT_H