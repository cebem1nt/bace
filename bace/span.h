/*
 * Spans or string view implementation in c
 */

#ifndef _BACE_SPAN_H
#define _BACE_SPAN_H

#include <ctype.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
# include <strings.h>  /* strncasecmp (-std=c11) */
#endif

#define SPAN_EMPTY (span_t){NULL, 0}

#define SPAN_FMT "%.*s"
#define SPAN_ARG(span) (int)(span).length, (span).ptr

#define SPAN(cstr) (span_t){cstr, sizeof(cstr) - 1} // Compile time, at runtime use span_from_cstr

#define SPAN_IS_EMPTY(span) \
    (((span)->ptr == NULL) && ((span)->length == 0))

#define span_trim(span) \
    do { span_ltrim(span); span_rtrim(span); } while (0)

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

// Takes s, returns n whitespaces trimmed
size_t span_ltrim(span_t* s);

// Takes s, returns n whitespaces trimmed
size_t span_rtrim(span_t* s);

// Takes s1, s2, returns n times s2 was trimmed from s1
size_t span_ltrims(span_t* s1, span_t s2);

// Takes s1, s2, returns n times s2 was trimmed from s1 
size_t span_rtrims(span_t* s1, span_t s2);

// Find needle in haystack, returns -1 if not found
ssize_t span_finds(span_t haystack, span_t needle);

// Advance n chars from s.ptr, doesn't check bounds
size_t span_advance(span_t* s, size_t n);

#ifdef BACE_IMPLEMENTATION

size_t span_advance(span_t *s, size_t n) 
{
    s->ptr += n;
    s->length -= n;
}

char* span_to_cstr(span_t s)
{
    char* out = (char*) malloc(s.length + 1);
    if (!out) 
        return NULL;

    memcpy(out, s.ptr, s.length);
    out[s.length] = '\0';

    return out;
}

span_t span_from_cstr(char* cstr) 
{
    span_t span = {
        cstr,
        cstr ? strlen(cstr) : 0 
    };
    return span;
}

bool span_iseq(span_t a, span_t b) 
{
    if (a.length != b.length)
        return false;

    return strncmp(a.ptr, b.ptr, a.length) == 0;
}

bool span_case_iseq(span_t a, span_t b) 
{
    if (a.length != b.length)
        return false;

    return strncasecmp(a.ptr, b.ptr, a.length) == 0;
}

bool span_starts_with(span_t s, span_t expected) 
{
    if (expected.length > s.length)
        return false;

    return strncmp(s.ptr, expected.ptr, expected.length) == 0;
}

bool span_ends_with(span_t s, span_t expected) 
{
    if (expected.length > s.length)
        return false;

    s.ptr += (s.length - expected.length);
    return strncmp(s.ptr, expected.ptr, expected.length) == 0;
}

span_t span_chop_by(span_t* from, char delim) 
{
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

size_t span_ltrim(span_t* s)
{
    size_t n = 0;
 
    while(s->length > 0) {
        if (!isspace(*s->ptr))
            break;
        s->ptr++;
        s->length--;
        n++;
    }

    return n;
}

size_t span_rtrim(span_t* s) 
{
    size_t n = 0;

    while(s->length > 0) {
        if (!isspace(s->ptr[s->length - 1])) 
            break;
        s->length--;
        n++;
    }

    return n;
}

size_t span_ltrims(span_t* s1, span_t s2) 
{
    size_t n = 0;

    while (span_starts_with(*s1, s2)) {
        s1->ptr += s2.length;
        s1->length -= s2.length;
        n++;
    }

    return n;
}

size_t span_rtrims(span_t* s1, span_t s2)
{
    size_t n = 0;

    while(span_ends_with(*s1, s2)) {
        s1->length -= s2.length;
        n++;
    }

    return n;
}

ssize_t span_finds(span_t haystack, span_t needle) 
{
    ssize_t pos = 0;

    while (pos + needle.length <= haystack.length) {
        span_t remaining = {
            haystack.ptr + pos,
            haystack.length - pos
        };
        
        if (span_starts_with(remaining, needle))
            return pos;
        
        pos += needle.length;
    }

    return -1;
}

#endif // BACE_IMPLEMENTATION
#endif // _BACE_SPAN_H