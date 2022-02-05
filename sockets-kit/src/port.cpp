//
//  @(#)port.cpp
//
//  sockets kit - portable functions
//  --------------------------------
//
//  copyright 2014-2022 Code Construct Systems (CCS)
//
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "port.h"

namespace Portable {
    size_t Portable::Time(time_t *timer) {
        time(timer);

        return (EXIT_SUCCESS);
    }

    size_t Portable::LocalTime(time_t *timer, struct tm *time) {
#ifdef _SCL // secure C library
        return (localtime_s(time, timer));
#else
        struct tm *local_time = localtime(timer);

        time->tm_sec   = local_time->tm_sec;
        time->tm_min   = local_time->tm_min;
        time->tm_hour  = local_time->tm_hour;
        time->tm_mday  = local_time->tm_mday;
        time->tm_mon   = local_time->tm_mon;
        time->tm_year  = local_time->tm_year;
        time->tm_wday  = local_time->tm_wday;
        time->tm_yday  = local_time->tm_yday;
        time->tm_isdst = local_time->tm_isdst;

        return (EXIT_SUCCESS);
#endif
    }

    size_t Portable::FormatTime(char *destination, size_t destination_size, const char *format, struct tm *time) {
        return (strftime(destination, destination_size, format, time));
    }

    size_t Portable::StringCopy(char *destination, size_t destination_size, const char *source, size_t count) {
#ifdef _SCL // secure C library
        return (strncpy_s(destination, destination_size, source, count));
#else
        return ((strncpy(destination, source, count) != NULL) ? EXIT_SUCCESS : EXIT_FAILURE);
#endif
    }

    size_t Portable::StringConcatenate(char *destination, size_t destination_size, const char *source, size_t count) {
#ifdef _SCL // secure C library
        return (strncat_s(destination, destination_size, source, count));
#else
        return ((strncat(destination, source, count) != NULL) ? EXIT_SUCCESS : EXIT_FAILURE);
#endif
    }

    size_t Portable::StringFormat(char *destination, size_t destination_size, const char *format, ...) {
        va_list varg;
        int rc;

        va_start(varg, format);
#ifdef _SCL // secure C library
        rc = vsprintf_s(destination, destination_size, format, varg);
#else
        rc = vsprintf(destination, format, varg);
#endif
        va_end(varg);

        return (rc);
    }
}