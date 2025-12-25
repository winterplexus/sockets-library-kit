Sockets Library Kit for C++
===========================

Sockets library kit based on C++ for implementing Windows-based TCP/IP socket application.

The kit includes the following features:

* TCP/IP client that sends messages to a server.

* TCP/IP server that receives and returns messages sent by a client.

* Thread-safe log file (which is used by the TCP/IP server to trace socket activity and error conditions).

The kit includes the following component(s):

* Sockets C++ class:

```
#define WIN32_LEAN_AND_MEAN
#include <winsock.h>

#ifdef  _SOCKETS_INTERFACE_DLL_EXPORTS
#define _SOCKETS_INTERFACE_API __declspec(dllexport)
#else
#define _SOCKETS_INTERFACE_API __declspec(dllimport)
#endif

class _SOCKETS_INTERFACE_API SocketsInterface {
public:
    SocketsInterface(void);
    SocketsInterface(int, int, int);
   ~SocketsInterface(void);
    SOCKET CreateSocket(void);
    SOCKET BindSocket(SOCKET, const int);
    SOCKET ListenConnections(SOCKET, int);
    SOCKET AcceptConnections(const SOCKET);
    SOCKET ConnectServer(SOCKET, const char *, const int);
    int SendRequest(const SOCKET, const char *, const int);
    int ReceiveResponse(const SOCKET, char *, const int);
    void CloseSocket(SOCKET);
private:
    int address_family = AF_INET;
    int socket_type = SOCK_STREAM;
    int ip_protocol = IPPROTO_TCP;
    WSADATA wsa_data;
};
```

* Client application C++ class:

```
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
```

* Console server application C++ class:

```
class ConsoleServerApplication {
public:
    ConsoleServerApplication();
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
```

* Log file C++ class:

```
class LogFile {
public:
    LogFile(const std::string &);
    LogFile(const std::string &, const std::string &);
    LogFile(LogFile const &);
   ~LogFile(void);
    void SetFileName(const std::string &);
    void SetDateTimeFormat(const std::string &);
    void WriteDebugLog(const std::string &);
    void WriteInformationLog(const std::string &);
    void WriteWarningLog(const std::string &);
    void WriteErrorLog(const std::string &);
private:
    std::string log_file_name = std::string("log-file");
    std::string log_date_time_format = std::string("%Y-%m-%d %H:%M:%S");
private:
    void WriteEntryToLogFile(const std::string &);
    void WriteRuntimeErrorToLogFile(const std::string &);
    std::string GetSystemDate();
    std::string GetSystemDateTime();
};
```

Sockets library is supported on Windows operating systems only.
