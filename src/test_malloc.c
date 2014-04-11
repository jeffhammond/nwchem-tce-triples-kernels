#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[])
{
    size_t max = (argc>1) ? (size_t)atol(argv[1]) : ((size_t)256*1024)*((size_t)1024*1024);
    for (size_t n=1; n<=max; n*=2) {
        printf("attempting malloc of %zu bytes \n", n);
        fflush(0);
        void * ptr = malloc(n);
        if (ptr==NULL) {
            printf("malloc of %zu bytes failed \n", n);
            fflush(0);
            return 1;
        } else {
            printf("malloc of %zu bytes succeeded \n", n);
            fflush(0);
            memset(ptr,0,n);
            printf("memset of %zu bytes succeeded \n", n);
            fflush(0);
            free(ptr);
        }
    }
    return 0;
}
