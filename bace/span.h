/*
 * Spans or string view implementation in c
 */

#ifndef _BACE_SPAN_H
#define _BACE_SPAN_H

#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
# include <strings.h>  /* strncasecmp (-std=c11) */
#endif

#define SPAN_FMT "%.*s"
#define SPAN_ARG(span) (int)(span).length, (span).ptr
#define SPAN_EMPTY (span_t){NULL, 0}

#define SPAN(cstr) (span_t){cstr, sizeof(cstr) - 1} // Compile time, at runtime use span_from_cstr
#define SPAN_IS_EMPTY(span) (((span)->ptr == NULL) && ((span)->length == 0))
#define SPAN_TRIM(span) do { SPAN_LTRIM(span); SPAN_RTRIM(span); } while (0)

#define SPAN_LTRIM(span) do {                                       \
    while((span)->length > 0) {                                     \
        if (!isspace(*(span)->ptr))                                 \
            break;                                                  \
        (span)->ptr++;                                              \
        (span)->length--;                                           \
    }                                                               \
} while (0)

#define SPAN_RTRIM(span) do {                                       \
    while((span)->length > 0) {                                     \
        if (!isspace((span)->ptr[(span)->length - 1]))              \
            break;                                                  \
        (span)->length--;                                           \
    }                                                               \
} while (0)

typedef struct span {
    char* ptr;
    size_t length;
} span_t;

span_t span_from_cstr(char* cstr);
span_t span_chop_by(span_t* from, char delim); 

bool span_iseq(span_t a, span_t b);
bool span_case_iseq(span_t a, span_t b);
bool span_starts_with(span_t s, span_t expected);
bool span_ends_with(span_t s, span_t expected);

char* span_to_cstr(span_t s);

#ifdef BACE_IMPLEMENTATION

char* span_to_cstr(span_t s) {
    char* out = (char*) malloc(s.length + 1);
    if (!out) 
        return NULL;

    memcpy(out, s.ptr, s.length);
    out[s.length] = '\0';

    return out;
}

span_t span_from_cstr(char* cstr) {
    span_t span = {
        cstr,
        cstr ? strlen(cstr) : 0 
    };
    return span;
}

bool span_iseq(span_t a, span_t b) {
    if (a.length != b.length)
        return false;

    return strncmp(a.ptr, b.ptr, a.length) == 0;
}

bool span_case_iseq(span_t a, span_t b) {
    if (a.length != b.length)
        return false;

    return strncasecmp(a.ptr, b.ptr, a.length) == 0;
}

bool span_starts_with(span_t s, span_t expected) {
    if (expected.length > s.length)
        return false;

    return strncmp(s.ptr, expected.ptr, expected.length) == 0;
}

bool span_ends_with(span_t s, span_t expected) {
    if (expected.length > s.length)
        return false;

    s.ptr += (s.length - expected.length);
    return strncmp(s.ptr, expected.ptr, expected.length) == 0;
}

span_t span_chop_by(span_t* from, char delim) {
    span_t out = {
        .ptr = from->ptr,
        .length = 0
    };

    if (from->length == 0)
        return out; 

    char* found = (char*) memchr(from->ptr, delim, from->length);
    
    if (!found) {
        out.length = from->length;
        from->ptr += from->length;
        from->length = 0;
    } else {
        size_t pos = found - from->ptr;
        out.length = pos;
        from->ptr += pos + 1;
        from->length -= pos + 1;
    }

    return out;
}

#endif // BACE_IMPLEMENTATION
#endif // _BACE_SPAN_H