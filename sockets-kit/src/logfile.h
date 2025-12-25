//
//  @(#)logfile.h
//
//  sockets kit - log file class
//  ----------------------------
//
//  copyright 2014-2025 Code Construct Systems (CCS)
//
#ifndef __LOGFILE_H
#define __LOGFILE_H

#include <string>

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

#endif // __LOGFILE_H