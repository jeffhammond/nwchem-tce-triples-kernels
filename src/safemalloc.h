#ifndef SAFEMALLOC_H
#define SAFEMALLOC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int posix_memalign(void **memptr, size_t alignment, size_t size);

#define ALIGNMENT 64

static void * safemalloc(size_t n)
{
    int rc = -1;
    void * ptr = NULL;
    rc = posix_memalign( &ptr, ALIGNMENT, n);
    if ( ptr==NULL || rc!=0 ) {
        fprintf( stdout , "%zu bytes could not be allocated \n" , n );
	return NULL;
    }
    return ptr;
}

#endif // SAFEMALLOC_H
