//
//  @(#)port.cpp
//
//  sockets kit - portable functions
//  --------------------------------
//
//  copyright 2014-2020 Code Construct Systems (CCS)
//
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "port.h"

namespace Portable {
    static int strcpy_p(char *, size_t, const char *, size_t);

    int Portable::StringFormat(char *destination, size_t destination_size, const char *format, ...) {
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

    int Portable::Time(time_t *timer) {
        time(timer);

        return (EXIT_SUCCESS);
    }

    int Portable::LocalTime(time_t *timer, struct tm *time) {
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

    int Portable::StringTime(char *destination, size_t destination_size, struct tm *time) {
#ifdef _SCL // secure C library
        return (asctime_s(destination, destination_size, time));
#else
        char *ascii_time = asctime(time);

        return (strcpy_p(destination, destination_size, ascii_time, strlen(ascii_time)));
#endif
    }

    int Portable::FormatTime(char *destination, size_t destination_size, const char *format, struct tm *time) {
        return (strftime(destination, destination_size, format, time));
    }

    static int strcpy_p(char *destination, size_t destination_size, const char *source, size_t count) {
#ifdef _SCL // secure C library
        return (strncpy_s(destination, destination_size, source, count));
#else
        return ((strncpy(destination, source, count) != NULL) ? EXIT_SUCCESS : EXIT_FAILURE);
#endif
    }
}