#include "./bace/span.h"
#include "./bace/da.h"

#define error_abort(fmt, ...) do {          \
    fprintf(stderr, fmt, __VA_ARGS__);      \
    exit(1);                                \
} while(0)

#define perror_abort(msg) do {              \
    perror(msg);                            \
    exit(1);                                \
} while(0)
