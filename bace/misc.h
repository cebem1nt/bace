#ifndef _BACE_MISC_H
#define _BACE_MISC_H

#define error_exit(fmt, ...) do {           \
    fprintf(stderr, fmt, __VA_ARGS__);      \
    exit(1);                                \
} while(0)

#define perror_exit(msg) do  {              \
    perror(msg);                            \
    exit(1);                                \
} while(0)

#endif