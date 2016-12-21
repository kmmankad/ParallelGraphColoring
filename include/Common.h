#ifndef __COMMON
#define __COMMON

#include <stdio.h>
#include <cstdlib>

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

#ifdef __NVCC__
// If we're compiling with NVCC
// Use CUDA_CALL to do any host side CUDA related calls
#define CUDA_CALL(F)  if( (F) != cudaSuccess ) \
{fprintf(stderr, "[CUDAError] %s at %s:%d\n", cudaGetErrorString(cudaGetLastError()), \
		__FILE__,__LINE__); exit(-1);} 

// Use this to check the status of the kernel
#define CUDA_CHECK()  if( (cudaPeekAtLastError()) != cudaSuccess ) \
{fprintf(stderr, "[CUDAKernelError] %s at %s:%d\n", cudaGetErrorString(cudaGetLastError()), \
		__FILE__,__LINE__-1); exit(-1);} 
#endif // __NVCC__

// Program parameters
#define NO_COLOR 0
#define MAX_DEGREE 200

#endif // __COMMON
