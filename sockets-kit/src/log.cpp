//
//  @(#)log.cpp
//
//  sockets kit - log file
//  ----------------------
//
//  copyright 2014-2020 Code Construct Systems (CCS)
//
#define WIN32_LEAN_AND_MEAN

#include <fstream>
#include <iostream>
#include <sstream>
#include <errno.h>
#include <time.h>
#include <windows.h>
#include "log.h"
#include "port.h"

static std::string log_file_name;
static std::string log_date_time_format;

CRITICAL_SECTION log_critical_section;

LogFile::LogFile(void) {
    InitializeCriticalSection(&log_critical_section);

    log_file_name = std::string("log");
}

LogFile::LogFile(const std::string &file_name) {
    InitializeCriticalSection(&log_critical_section);

    log_file_name = file_name;
    log_date_time_format = std::string("%Y-%m-%d %H:%M:%S");
}

LogFile::LogFile(LogFile const &log) {
    InitializeCriticalSection(&log_critical_section);

    log_file_name = std::string(log_file_name);
    log_date_time_format = std::string(log_date_time_format);
}

LogFile::~LogFile(void) {
    DeleteCriticalSection(&log_critical_section);
}

void LogFile::SetFileName(const std::string &file_name) {
    log_file_name = file_name;
}

void LogFile::SetDateTimeFormat(const std::string &date_time_format) {
    log_date_time_format = std::string(date_time_format);
}

void LogFile::WriteTraceLog(const std::string &trace_message) {
    std::string entry = std::string(GetSystemDateTime() + " *TRACE: " + trace_message + "\n");

    WriteEntryToLogFile(entry);
}

void LogFile::WriteDebugLog(const std::string &debug_message) {
    std::string entry = std::string(GetSystemDateTime() + " *DEBUG: " + debug_message + "\n");

    WriteEntryToLogFile(entry);
}

void LogFile::WriteInformationLog(const std::string &information_message) {
    std::string entry = std::string(GetSystemDateTime() + " *INFORMATION: " + information_message + "\n");

    WriteEntryToLogFile(entry);
}

void LogFile::WriteWarningLog(const std::string &warning_message) {
    std::string entry = std::string(GetSystemDateTime() + " *WARNING: " + warning_message + "\n");

    WriteEntryToLogFile(entry);
}

void LogFile::WriteErrorLog(const std::string &error_message) {
    std::string entry = std::string(GetSystemDateTime() + " *ERROR: " + error_message + "\n");

    WriteEntryToLogFile(entry);
}

void LogFile::WriteFatalLog(const std::string &fatal_message) {
    std::string entry = std::string(GetSystemDateTime() + " *FATAL: " + fatal_message + "\n");

    WriteEntryToLogFile(entry);
}

void LogFile::WriteEntryToLogFile(const std::string &entry) {
    EnterCriticalSection(&log_critical_section);

    std::string log_fname = std::string(std::string(log_file_name) + "." + GetSystemDate() + ".log");
    std::ofstream log_file(log_fname.c_str(), std::ios::app);

    if (!log_file.is_open()) {
        LeaveCriticalSection(&log_critical_section);
        return;
    }

    log_file << entry;
    log_file.flush();
    log_file.close();

    LeaveCriticalSection(&log_critical_section);
}

std::string LogFile::GetSystemDate() {
    time_t rawtime;
    struct tm tms;
    char buffer[32];

    Portable::Time(&rawtime);
    Portable::LocalTime(&rawtime, &tms);

    memset(buffer, 0, sizeof(buffer));
    if (Portable::FormatTime(buffer, sizeof(buffer), "%Y-%m-%d", &tms) == EXIT_FAILURE) {
        std::string runtime_error = std::string("error-> Portable::FormatTime() failed: error number (" + std::to_string(errno) + "\n");
        WriteRuntimeErrorToLogFile(runtime_error);
    }

    std::string system_date(buffer);
    return (system_date);
}

std::string LogFile::GetSystemDateTime() {
    time_t rawtime;
    struct tm tms;
    char buffer[32];

    Portable::Time(&rawtime);
    Portable::LocalTime(&rawtime, &tms);

    memset(buffer, 0, sizeof(buffer));
    if (Portable::FormatTime(buffer, sizeof(buffer), log_date_time_format.c_str(), &tms) == EXIT_FAILURE) {
        std::string runtime_error = std::string("error-> Portable::FormatTime() failed: error number (" + std::to_string(errno) + ")\n");
        WriteRuntimeErrorToLogFile(runtime_error);
    }

    std::string system_date(buffer);
    return (system_date);
}

void LogFile::WriteRuntimeErrorToLogFile(const std::string &runtime_error) {
    EnterCriticalSection(&log_critical_section);

    std::string log_fname = std::string(std::string(log_file_name) + std::string(".") + GetSystemDate() + ".log");
    std::ofstream log_file(log_fname.c_str(), std::ios::app);

    if (!log_file.is_open()) {
        LeaveCriticalSection(&log_critical_section);
        return;
    }

    log_file << std::string("0000-00-00 00:00:00 *FATAL: " + runtime_error + "\n");
    log_file.flush();
    log_file.close();

    LeaveCriticalSection(&log_critical_section);
}