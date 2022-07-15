//
//  @(#)logfile.h
//
//  sockets kit - log file
//  ----------------------
//
//  copyright 2014-2022 Code Construct Systems (CCS)
//
#ifndef __LOG_H
#define __LOG_H

#include <string>

class LogFile {
public:
        LogFile(const std::string &);
        LogFile(const std::string &, const std::string &);
        LogFile(LogFile const &);
       ~LogFile(void);
        void SetFileName(const std::string &);
        void SetDateTimeFormat(const std::string &);
        void WriteTraceLog(const std::string &);
        void WriteDebugLog(const std::string &);
        void WriteInformationLog(const std::string &);
        void WriteWarningLog(const std::string &);
        void WriteErrorLog(const std::string &);
        void WriteFatalLog(const std::string &);
private:
        std::string log_file_name = std::string("log-file");
        std::string log_date_time_format = std::string("%Y-%m-%d %H:%M:%S");
private:
        void WriteEntryToLogFile(const std::string &);
        void WriteRuntimeErrorToLogFile(const std::string &);
        std::string GetSystemDate();
        std::string GetSystemDateTime();
};

#endif // __LOG_H