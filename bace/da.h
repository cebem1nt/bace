/*
 * dynamic array
 * I'll use tsoding's approach for it, macros.
 * This is the most flexible way of doing this.
 */

#include <assert.h>
#include <stdlib.h>

#define DA_DEFAULT_CAP 10

#define DA_INIT(da, type, capacity) do {                        \
    size_t cap = (capacity) ? (capacity)                        \
                            : DA_DEFAULT_CAP;                   \
                                                                \
    (da)->len = 0;                                              \
    (da)->cap = cap;                                            \
    (da)->arr = malloc(cap * sizeof(type));                     \
    assert((da)->arr && "Could not alloc array, no memory");    \
} while(0)

#define DA_APPEND(da, ...) do {                                         \
    if ((da)->len >= (da)->cap) {                                       \
        (da)->cap = (da)->cap ? (da)->cap * 2                           \
                              : DA_DEFAULT_CAP;                         \
        (da)->arr = realloc((da)->arr, (da)->cap * sizeof(*(da)->arr)); \
        assert((da)->arr && "Could not realloc array, no memory");      \
    }                                                                   \
    (da)->arr[(da)->len++] = __VA_ARGS__;                               \
} while(0) 

#define DA_POP(da) (da)->arr[--(da)->len]