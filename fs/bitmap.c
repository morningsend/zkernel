//
// Created by zaiyangli on 4/22/16.
//

#include "bitmap.h"
#include "../libc/string.h"


void bitmap_init(p_bitmap bmap, uint32_t val){
    if(val == 0)
        memset(bmap->bits, BITMAP_WORD_SIZE, 0);
    else if(val == 1)
        memset(bmap->bits, BITMAP_WORD_SIZE, 0xffffffff);
}

void bitmap_set_on(p_bitmap bmap, uint32_t pos){
    uint32_t bitpos = pos & 0x1f;
    uint32_t wordpos = pos >> 5;
    bmap->bits[wordpos] |= 0x01 << bitpos;
}
void bitmap_set_off(p_bitmap bmap, uint32_t pos){
    uint32_t bitpos = pos & 0x1f;
    uint32_t wordpos = pos >> 5;
    bmap->bits[wordpos] &= ~(0x01 << bitpos);
}
uint32_t bitmap_get(p_bitmap bmap, uint32_t pos){
    uint32_t bitpos = pos & 0x1f;
    uint32_t wordpos = pos >> 5;
    return (bmap->bits[wordpos] >> bitpos) & 0x01;
}
int bitmap_scan_first_one(p_bitmap bmap){

}
int bitmap_scan_first_zero(p_bitmap bmap){
    uint32_t word = 0;
    int count = 0;
    int i = 0;
    for(i = 0; i < BITMAP_WORD_SIZE;i++){
        word = ~ bmap->bits[i];
        asm(
            "rbit %[word], %[word]\n"
            "clz %[count], %[word]\n"
        :[count] "=r" (count)
        :[word] "r" (word)
        );
        if(count != 32){
            count += i*BITS_IN_WORD;
            break;
        }
    }
    if(i == BITMAP_WORD_SIZE)
        return -1;
    return count;
}

void _bitmap_set_on(void* bmap, uint32_t pos, uint32_t bmap_word_size){
    uint32_t bitpos = pos & 0x1f;
    uint32_t wordpos = pos >> 5;
    uint32_t* bbmap = (uint32_t*) bmap;
    bbmap[wordpos] |= 0x01 << bitpos;
}
void _bitmap_set_off(void* bmap, uint32_t pos, uint32_t bmap_word_size){
    uint32_t bitpos = pos & 0x1f;
    uint32_t wordpos = pos >> 5;
    uint32_t* bbmap = (uint32_t*) bmap;
    bbmap[wordpos] &= ~(0x01 << bitpos);
}
uint32_t _bitmap_get(void* bmap, uint32_t pos, uint32_t bmap_word_size){
    uint32_t bitpos = pos & 0x1f;
    uint32_t wordpos = pos >> 5;
    uint32_t* bbmap = (uint32_t*) bmap;
    return (bbmap[wordpos] >> bitpos) & 0x01;
}
int _bitmap_scan_first_zero(void* bmap, uint32_t bmap_word_size){
    uint32_t word = 0;
    int count = 0;
    int i = 0;
    uint32_t* bbmap = (uint32_t*) bmap;
    for(i = 0; i < bmap_word_size;i++){
        word = ~ bbmap[i];
        asm(
        "rbit %[word], %[word]\n"
                "clz %[count], %[word]\n"
        :[count] "=r" (count)
        :[word] "r" (word)
        );
        if(count != 32){
            count += i*BITS_IN_WORD;
            break;
        }
    }
    if(i == bmap_word_size)
        return -1;
    else
        return count;
}