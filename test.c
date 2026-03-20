#define BACE_IMPLEMENTATION
#include "bace.h"

#include <stdio.h>
#include <stddef.h>

struct da_ints {
    float* arr;
    size_t cap;
    size_t len;
};

int main() 
{
    span_t s = SPAN("foo_bar_baz");
    span_t choped = span_chop_by(&s, ' ');

    printf("%s\n", s.ptr);
    printf("Span: "SPAN_FMT"\n", SPAN_ARG(choped));

    struct da_ints ints;
    DA_INIT(&ints);

    DA_APPEND(&ints, 2);
    DA_APPEND(&ints, 3);
    DA_APPEND(&ints, 4);
    DA_APPEND(&ints, 5);
    DA_APPEND(&ints, 6);
    DA_APPEND(&ints, 7);

    for (int i = 0; i < ints.len; i++) {
        printf("%f, ", ints.arr[i]);
    }
}