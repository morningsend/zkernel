//
// Created by zaiyangli on 4/22/16.
//

#ifndef _FDISK_H
#define _FDISK_H

#include <stdint-gcc.h>

/**super block**/

struct fdisk_header {
    char magic_iden[8];
    char partition_name[8];
    uint32_t alloc_bitmap_begin;
    uint32_t alloc_bitmap_count;
    uint32_t fnode_block_begin;
    uint32_t fnode_block_count;
    uint32_t fnode_size;
    uint32_t data_block_begin;
    uint32_t data_block_count;
    uint32_t data_block_header_size;
};

#endif //_FDISK_H
