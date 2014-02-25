#ifndef SAFEMALLOC_H
#define SAFEMALLOC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

int posix_memalign(void **memptr, size_t alignment, size_t size);

#define ALIGNMENT 128

void * safemalloc(size_t n);

#endif // SAFEMALLOC_H
