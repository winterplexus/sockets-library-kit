//
//  @(#)logmutex.h
//
//  sockets kit - log file mutex operations
//  ---------------------------------------
//
//  copyright 2014-2022 Code Construct Systems (CCS)
//
#ifndef __LOGMUTEX_H
#define __LOGMUTEX_H

#ifdef _POSIX_ENVIRONMENT
#include <pthread.h>
#endif

#ifdef _WINDOWS_ENVIRONMENT
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#ifdef  MUTEX_CRITICAL_SECTION
#error  MUTEX_CRITICAL_SECTION is defined in another include file
#endif
#ifdef  MUTEX_CRITICAL_SECTION_INIT
#error  MUTEX_CRITICAL_SECTION_INIT is defined in another include file
#endif
#ifdef  MUTEX_CRITICAL_SECTION_LOCK
#error  MUTEX_CRITICAL_SECTION_LOCK is defined in another include file
#endif
#ifdef  MUTEX_CRITICAL_SECTION_UNLOCK
#error  MUTEX_CRITICAL_SECTION_UNLOCK is defined in another include file
#endif
#ifdef  MUTEX_CRITICAL_SECTION_DESTROY
#error  MUTEX_CRITICAL_SECTION_DESTROY is defined in another include file
#endif

#ifdef _POSIX_ENVIRONMENT
#define MUTEX_CRITICAL_SECTION         pthread_mutex_t critical_section_lock
#define MUTEX_CRITICAL_SECTION_INIT    pthread_mutex_init(&critical_section_lock, NULL)
#define MUTEX_CRITICAL_SECTION_LOCK    pthread_mutex_lock(&critical_section_lock)
#define MUTEX_CRITICAL_SECTION_UNLOCK  pthread_mutex_unlock(&critical_section_lock)
#define MUTEX_CRITICAL_SECTION_DESTROY pthread_mutex_destroy(&critical_section_lock)
#endif

#ifdef _WINDOWS_ENVIRONMENT
#define MUTEX_CRITICAL_SECTION         CRITICAL_SECTION critical_section_lock
#define MUTEX_CRITICAL_SECTION_INIT    InitializeCriticalSection(&critical_section_lock)
#define MUTEX_CRITICAL_SECTION_LOCK    EnterCriticalSection(&critical_section_lock)
#define MUTEX_CRITICAL_SECTION_UNLOCK  LeaveCriticalSection(&critical_section_lock)
#define MUTEX_CRITICAL_SECTION_DESTROY DeleteCriticalSection(&critical_section_lock)
#endif

#endif // __LOGMUTEX_H