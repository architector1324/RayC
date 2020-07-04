#ifndef CHN
#define CHN

#include "vec.h"

// settings
// #define CHAIN_DEF_STD

// extra
#define __cat(X, Y) X##Y
#define _cat(X, Y) __cat(X, Y)

// base
#define chn(type) _cat(_chn_, type)
#define chn_init(type) _cat(chn(type), _init)

#define chn_chain(c, e) c.chain(&c, e)
#define chn_at(c, e) c.at(&c, e)

#define CHAIN(type)\
SLICE(slc(type))\
MICRO_VECTOR(slc(type))\
typedef struct _cat(_, chn(type)) {\
    vec_micro(slc(type)) _data;\
    size_t size;\
    void (*chain)(struct _cat(_, chn(type))*, slc(type));\
    type (*at)(const struct _cat(_, chn(type))*, size_t);\
} chn(type);\
void _cat(chn(type), _chain)(chn(type)* c, slc(type) e) {\
    c->size += e.size;\
    vec_push(c->_data, e);\
}\
type _cat(chn(type), _at)(const chn(type)* c, size_t i) {\
    for(size_t j = 0; j < c->size; j++) {\
        if(i < vec_at(c->_data, j).size) return vec_at(c->_data, j).data[i];\
        i -= vec_at(c->_data, j).size;\
    }\
    fprintf(stderr, "chn:at: index out of bounds!\n");\
    abort();\
}\
chn(type) chn_init(type)() {\
    return (chn(type)) {\
        ._data = vec_micro_init(slc(type))(),\
        .chain = _cat(chn(type), _chain),\
        .at = _cat(chn(type), _at)\
    };\
}

// defined chaines for std
#ifdef CHAIN_DEF_STD

#include <stdint.h>

CHAIN(char)
CHAIN(int)
CHAIN(float)
CHAIN(double)
CHAIN(size_t)

CHAIN(int8_t)
CHAIN(int16_t)
CHAIN(int32_t)
CHAIN(int64_t)
CHAIN(uint8_t)
CHAIN(uint16_t)
CHAIN(uint32_t)
CHAIN(uint64_t)

#endif

#endif