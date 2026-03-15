#define BACE_IMPLEMENTATION
#include "bace.h"
#include <stdio.h>

int main() 
{
    span_t s = SPAN("foo_bar_baz");
    span_t choped = span_chop_by(&s, ' ');

    printf("%s\n", s.ptr);
    printf("Span: "SPAN_FMT"\n", SPAN_ARG(choped));
}