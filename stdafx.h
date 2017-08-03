#ifndef STDAFX_H_INCLUDED
#define STDAFX_H_INCLUDED

#define UNICODE
#define WINVER   0x0500
#define _WIN32_WINNT 0x0500

#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <vector>
#include <list>
#define ERROR_TEST printf("error=%ld\n",GetLastError());

uint64_t rdtsc();

#endif // STDAFX_H_INCLUDED
