/*
 * dynamic array
 * I'll use tsoding's approach for it, macros.
 * This is the most flexible way of doing this.
 */

#ifndef _BACE_DA_H
#define _BACE_DA_H

#include <assert.h>
#include <stdlib.h>

#define DA_DEFAULT_CAP 10

typedef struct {
    size_t len, cap;
    int* arr;
} int_da_t;

typedef struct {
    size_t len, cap;
    float* arr;
} float_da_t;

typedef struct {
    size_t len, cap;
    double* arr;
} double_da_t;

#define DA_INIT_CAP(da, capacity) do {                          \
    size_t cap = (capacity) ? (capacity)                        \
                            : DA_DEFAULT_CAP;                   \
                                                                \
    (da)->len = 0;                                              \
    (da)->cap = cap;                                            \
    (da)->arr = malloc(cap * sizeof(*(da)->arr));               \
    assert((da)->arr && "Could not alloc array, no memory");    \
} while(0)

#define DA_INIT_NOCAP(da) DA_INIT_CAP(da, DA_DEFAULT_CAP)
#define __DA_PARAMS_MATCH_MACRO(_1, _2, MACRO, ...) MACRO
#define DA_INIT(...) __DA_PARAMS_MATCH_MACRO(__VA_ARGS__, DA_INIT_CAP, DA_INIT_NOCAP)(__VA_ARGS__)

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

#endif // _BACE_DA_H