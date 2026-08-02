#ifndef _BACE_MISC_H
#define _BACE_MISC_H

#include <stdlib.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

#define error_exit(...) do {                \
    fprintf(stderr, __VA_ARGS__);           \
    exit(EXIT_FAILURE);                     \
} while(0)

#define perror_exit(msg) do  {              \
    perror(msg);                            \
    exit(EXIT_FAILURE);                     \
} while(0)

#define help_exit(program) do  {            \
    printf(HELP, program);                  \
    exit(EXIT_FAILURE);                     \
} while(0)

#ifdef BACE_IMPLEMENTATION

char* readfile(const char* filename, size_t* out_size) 
{
    char*  out = NULL;
    size_t fsize;
    int    fd;
    
    if ((fd = open(filename, O_RDONLY)) == -1) {
        perror("open");
        goto _exit;
    }

    if ((fsize = lseek(fd, 0, SEEK_END)) == -1) {
        perror("lseek");
        goto _exit;
    }

    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("lseek");
        goto _exit;
    }

    if ((out = (char*) malloc(fsize + 1)) == NULL) {
        goto _exit;
    }

    if (read(fd, out, fsize) == -1) {
        perror("read");
        free(out);
        goto _exit;
    }

    if (out_size)
        *out_size = fsize;

    out[fsize] = '\0';
_exit:
    close(fd);
    return out;
}


#endif // BACE_IMPLEMENTATION
#endif // _BACE_MISC_H
