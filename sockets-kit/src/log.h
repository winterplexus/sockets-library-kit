//
//  @(#)log.h
//
//  sockets kit - log file
//  ----------------------
//
//  copyright 2014-2020 Code Construct Systems (CCS)
//
#ifndef __LOG_H
#define __LOG_H

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <string>

#ifdef  LOG_FILE_DLL_EXPORTS
#define LOG_FILE_API __declspec(dllexport)
#else
#define LOG_FILE_API __declspec(dllimport)
#endif

class LOG_FILE_API LogFile {
public:
        LogFile(void);
        LogFile(const std::string &file_name);
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
        void WriteEntryToLogFile(const std::string &);
        std::string GetSystemDate();
        std::string GetSystemDateTime();
        void WriteRuntimeErrorToLogFile(const std::string &);
};

#endif // __LOG_H