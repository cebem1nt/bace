#ifndef _BACE_MISC_H
#define _BACE_MISC_H

#include <stdlib.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

#define error_exit(...) do {                \
    fprintf(stderr, __VA_ARGS__);           \
    exit(1);                                \
} while(0)

#define perror_exit(msg) do  {              \
    perror(msg);                            \
    exit(1);                                \
} while(0)

#ifdef BACE_IMPLEMENTATION
char* readfile(const char* fp, size_t* out_size) 
{
    size_t fsize;
    char*  out;
    int    fd;
    
    if (open(fp, O_RDONLY) == -1) {
        perror("open");
        return NULL;   
    }

    fsize = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    if ((out = (char*) malloc(fsize)) == NULL)
        return NULL;

    if (read(fd, out, fsize) == -1) {
        perror("read");
        free(out);
        return NULL;
    }

    if (out_size)
        *out_size = fsize;

    return out;
}

#endif // BACE_IMPLEMENTATION
#endif // _BACE_MISC_H