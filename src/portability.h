// Portability defines for building z88dk
#pragma once

// strcasecmp()
#if defined(_WIN32) || defined(WIN32)
#define strcasecmp(a,b) stricmp(a,b)
#endif

// glob()
#if defined(_WIN32) || defined(WIN32)
#include <unixem/glob.h>
#endif
#include <glob.h>
