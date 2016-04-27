//
// Created by zaiyangli on 4/22/16.
//

#ifndef _BITMAP_H
#define _BITMAP_H

#include <stdint-gcc.h>
#include "fblock.h"
#define BITMAP_BITS (BITMAP_WORD_SIZE * 32)

#define BITMAP_WORD_SIZE (BLOCK_SIZE_BYTES/sizeof(uint32_t) + ( BLOCK_SIZE_BYTES % sizeof(uint32_t)==0 ? 0 : 1))
#define BITS_IN_WORD (8 * sizeof(uint32_t))

typedef struct bitmap_struct bitmap;
typedef struct bitmap_struct* p_bitmap;
struct bitmap_struct{
    uint32_t bits[BITMAP_WORD_SIZE];
};
void bitmap_init(p_bitmap bmap, uint32_t val);

void bitmap_set_on(p_bitmap bmap, uint32_t pos);
void bitmap_set_off(p_bitmap bmap, uint32_t pos);

int bitmap_scan_first_zero(p_bitmap bmap);

uint32_t bitmap_get(p_bitmap bmap, uint32_t pos);

void _bitmap_set_on(void* bmap, uint32_t pos, uint32_t bmap_word_size);
void _bitmap_set_off(void* bmap, uint32_t pos, uint32_t bmap_word_size);
uint32_t _bitmap_get(void* bmap, uint32_t pos, uint32_t bmap_word_size);
int _bitmap_scan_first_zero(void* bmap, uint32_t bmap_word_size);

#define BITMAP_GEN(size) BITMAP_GEN_STRUCT(size)\
                        BITMAP_GEN_INIT_FUNC(size)\
                        BITMAP_GEN_SET_ON(size)\
                        BITMAP_GEN_SET_OFF(size)\
                        BITMAP_GEN_GET(size)\
                        BITMAP_GEN_SCAN_FIRST_ZERO(size)

#define BITMAP_GEN_STRUCT(size) \
    struct bitmap_struct_##size {\
            uint32_t bits[size>> 5];\
    };\
    typedef struct bitmap_struct_##size bitmap_##size;\
    typedef struct bitmap_struct_##size * p_bitmap_##size;

#define BITMAP_GEN_INIT_FUNC(size) void bitmap_init_##size(void* bmap) {\
        memset(bmap, size >> 3 , 0);\
    }

#define BITMAP_GEN_SET_ON(size) void bitmap_set_on_##size ( void* bitmap, uint32_t pos) { \
        _bitmap_set_on(bitmap, pos, size >> 5);\
    }

#define BITMAP_GEN_SET_OFF(size) void bitmap_set_off_##size (void* bitmap, uint32_t pos) {\
    _bitmap_set_off(bitmap, pos, size >> 5);\
}

#define BITMAP_GEN_GET(size) uint32_t bitmap_get_##size ( void* bitmap, uint32_t pos) {\
    return _bitmap_get(bitmap, pos, size >> 5);\
}

#define BITMAP_GEN_SCAN_FIRST_ZERO(size) void bitmap_scan_first_zero_##size(void* bitmap){\
    _bitmap_scan_first_zero(bitmap, size >> 5);\
}
#endif //_BITMAP_H
