//
//  @(#)logfile.cpp
//
//  sockets kit - log file
//  ----------------------
//
//  copyright 2014-2022 Code Construct Systems (CCS)
//
#include <fstream>
#include <iostream>
#include <sstream>
#include <errno.h>
#include <time.h>
#include <windows.h>
#include "logfile.h"
#include "logmutex.h"
#include "port.h"

MUTEX_CRITICAL_SECTION;

LogFile::LogFile(const std::string &file_name) {
    MUTEX_CRITICAL_SECTION_INIT;

    if (!file_name.empty()) {
        log_file_name = file_name;
    }
    else {
        log_file_name = std::string("log-file");
    }
}

LogFile::LogFile(const std::string &file_name, const std::string &date_time_format) {
    MUTEX_CRITICAL_SECTION_INIT;

    if (!file_name.empty()) {
        log_file_name = file_name;
    }
    else {
        log_file_name = std::string("log-file");
    }
    if (!date_time_format.empty()) {
        log_date_time_format = date_time_format;
    }
    else {
        log_date_time_format = std::string(date_time_format);
    }
}

LogFile::LogFile(LogFile const &log) {
    MUTEX_CRITICAL_SECTION_INIT;

    log_file_name = std::string(log_file_name);
    log_date_time_format = std::string(log_date_time_format);
}

LogFile::~LogFile(void) {
    MUTEX_CRITICAL_SECTION_DESTROY;
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
    MUTEX_CRITICAL_SECTION_LOCK;

    std::string log_fname = std::string(std::string(log_file_name) + "." + GetSystemDate() + ".log");
    std::ofstream log_file(log_fname.c_str(), std::ios::app);

    if (!log_file.is_open()) {
        MUTEX_CRITICAL_SECTION_UNLOCK;
        return;
    }

    log_file << entry;
    log_file.flush();
    log_file.close();

    MUTEX_CRITICAL_SECTION_UNLOCK;
}

void LogFile::WriteRuntimeErrorToLogFile(const std::string &runtime_error) {
    MUTEX_CRITICAL_SECTION_LOCK;

    std::string log_fname = std::string(std::string(log_file_name) + std::string(".") + GetSystemDate() + ".log");
    std::ofstream log_file(log_fname.c_str(), std::ios::app);

    if (!log_file.is_open()) {
        MUTEX_CRITICAL_SECTION_UNLOCK;
        return;
    }

    log_file << std::string("0000-00-00 00:00:00 *FATAL: " + runtime_error + "\n");
    log_file.flush();
    log_file.close();

    MUTEX_CRITICAL_SECTION_UNLOCK;
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