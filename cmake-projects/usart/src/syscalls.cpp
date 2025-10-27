/**
 * @file    syscalls.cpp
 * @author  Rohit Nimkar (nehalnimkar@gmail.com) <https://csrohit.github.io>
 * @brief   Minimal implementation for system calls
 * @version 1.0
 *
 * @copyright Copyright (c) 2025
 * @attention
 *
 * This software component is licensed by Rohit Nimkar under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at: opensource.org/licenses/BSD-3-Clause
 */

#include <errno.h>
#include <sys/stat.h>

#include "usart.h"

/*
 * Minimal environment variable support.
 * Required by Newlib, but not actually used in most embedded applications.
 */
char*  __env[] = {nullptr};
char** environ = __env;

extern "C"
{
    /*
     * _write: Called by printf, puts, etc.
     * Redirects all output to serial/UART via __io_putchar.
     */
    int _write(int, char* ptr, int len)
    {
        static USART& usart1 = *new (USART::Usart1) USART;
        for (int i = 0; i < len; ++i)
        {
            usart1.tx_char(ptr[i]);
        }
        return len;
    }

    /*
     * _read: Used for reading from stdin (e.g. getchar()).
     * Reads from serial/UART via __io_getchar.
     */
    int _read(int, char* ptr, int len)
    {
        return -1;
    }

    /*
     * _close: File close stub.
     * No file system, so always returns error.
     */
    int _close(int)
    {
        return -1;
    }

    /*
     * _fstat: Returns information about a file.
     * Always returns character device (for UART/stdio compatibility).
     */
    int _fstat(int, struct stat* st)
    {
        st->st_mode = S_IFCHR;
        return 0;
    }

    /*
     * _isatty: Check if file descriptor is a terminal.
     * Always true for embedded/serial console.
     */
    int _isatty(int)
    {
        return 1;
    }

    /*
     * _lseek: Move file pointer (unused; required stub).
     * No files, so returns 0.
     */
    int _lseek(int, int, int)
    {
        return 0;
    }

    /*
     * _getpid: Returns a dummy PID.
     * Single-process embedded, so always 1.
     */
    int _getpid(void)
    {
        return 1;
    }

    /*
     * _kill: Send signal to process (stub).
     * Not supported on bare metal; sets errno and returns error.
     */
    int _kill(int, int)
    {
        errno = EINVAL;
        return -1;
    }

    /*
     * _exit: Called on program exit.
     * In embedded, just hang forever.
     */
    void _exit(int)
    {
        while (1)
        {
        }
    }

    /*
     * _sbrk: Provides/expands heap for malloc/new.
     * If not using dynamic allocation, this can be removed.
     * Adjust '_end' according to your linker script.
     */
    caddr_t _sbrk(int incr)
    {
        extern char  _ebss; // Defined by linker
        static char* heap_end;
        char*        prev_heap_end;
        if (heap_end == nullptr)
        {
            heap_end = &_ebss;
        }
        prev_heap_end = heap_end;
        heap_end += incr;
        return (caddr_t)prev_heap_end;
    }

} // extern "C"

