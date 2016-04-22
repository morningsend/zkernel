//
// Created by zaiyangli on 4/22/16.
//

#ifndef _BITMAP_H
#define _BITMAP_H

#include <stdint-gcc.h>

#define BITMAP_BITS 65536
#define BITMAP_WORD_SIZE (BITMAP_BITS/sizeof(uint32_t))
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



#endif //_BITMAP_H
