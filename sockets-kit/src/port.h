//
//  @(#)port.h
//
//  sockets kit - portable functions
//  --------------------------------
//
//  copyright 2014-2024 Code Construct Systems (CCS)
//
#ifndef __PORT_H
#define __PORT_H

#include <time.h>

namespace Portable {
        size_t Time(time_t *);
        size_t LocalTime(time_t *, struct tm *);
        size_t FormatTime(char *, size_t, const char *, struct tm *);
        size_t StringCopy(char *, size_t, const char *, size_t);
        size_t StringConcatenate(char *, size_t, const char *, size_t);
        size_t StringFormat(char *, size_t, const char *, ...);
};

#endif // __PORT_H