#ifndef __COMMON
#define __COMMON

#include <stdio.h>

// Macro to print debug messages
#ifdef NDEBUG
#define debug(M, ...)
#else 
#define debug(M, ...) fprintf(stderr, "[DEBUG] %s:%s:%d: " M "\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__) 
#endif

// Macro to print errors
#define LogError(M, ...) fprintf(stderr,"[ERROR] %s:%s:%d: " M "\n", __FILE__,__func__,__LINE__, ##__VA_ARGS__) 

// Macro to print info messages
#define LogInfo(M, ...) fprintf(stderr,"[Info] %s:%s:%d: " M "\n", __FILE__,__func__,__LINE__, ##__VA_ARGS__) 

#endif // __COMMON
