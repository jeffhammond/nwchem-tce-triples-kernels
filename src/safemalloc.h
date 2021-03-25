#ifndef SAFEMALLOC_H
#define SAFEMALLOC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#if defined(USE_CUDA_UM)
#include <cuda.h>
#include <cuda_runtime.h>
#include <cuda_runtime_api.h>
#endif

int posix_memalign(void **memptr, size_t alignment, size_t size);

#define ALIGNMENT 64

static void * safemalloc(size_t n)
{
    int rc = -1;
    void * ptr = NULL;
#if defined(USE_CUDA_UM)
    rc = cudaMallocManaged((void**)&ptr, n, cudaMemAttachGlobal);
    if ( ptr==NULL || rc!=0 ) {
        fprintf( stdout , "%zu bytes could not be allocated \n" , n );
	return NULL;
    }
#elif defined(__INTEL_COMPILER)
    ptr = _mm_malloc(n,64); /* breaks if free used */
    if ( ptr==NULL ) {
        fprintf( stdout , "%zu bytes could not be allocated \n" , n );
    }
#elif 1
    rc = posix_memalign( &ptr, ALIGNMENT, n);
    if ( ptr==NULL || rc!=0 ) {
        fprintf( stdout , "%zu bytes could not be allocated \n" , n );
	return NULL;
    }
#else
    ptr = malloc(n);
    if ( ptr==NULL ) {
        fprintf( stdout , "%zu bytes could not be allocated \n" , n );
    }
#endif
    return ptr;
}

static void safefree(void * ptr)
{
#if defined(USE_CUDA_UM)
    int rc = cudaFree((void*)ptr);
#elif defined(__INTEL_COMPILER)
    _mm_free(ptr);
#else
    free(ptr);
#endif
    return;
}

#endif // SAFEMALLOC_H
