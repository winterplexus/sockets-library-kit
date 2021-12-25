//
//  @(#)port.h
//
//  sockets kit - portable functions namespace
//  ------------------------------------------
//
//  copyright 2014-2017 Code Construct Systems (CCS)
//
#ifndef __PORTABLE_H
#define __PORTABLE_H

#include <time.h>

//
//  Portable functions namespace.
//
namespace Portable 
{
    int StringFormat(char *, size_t, const char *, ...);
    int Time(time_t *);
    int LocalTime(time_t *, struct tm *);
    int StringTime(char *, size_t, struct tm *);
    int FormatTime(char *, size_t, const char *, struct tm *);
};

#endif // __PORTABLE_H
