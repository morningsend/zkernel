//
// Created by zaiyangli on 4/22/16.
//

#ifndef _FDISK_H
#define _FDISK_H

#include "bitmap.h"
#include "fblock.h"
#include "fnode.h"
#include "../device/device.h"
#define BITMAP_ALLOC_TABLE_FNODE 0
#define BITMAP_ALLOC_TABLE_DATA 1
#define FNODE_LIMIT 1024
#define DATA_BLOCK_LIMIT 4096
#define FNODE_BLOCK_BEGIN (2)
#define DATA_BLOCK_BEGIN (2+FNODE_LIMIT/FNODE_PER_BLOCK)
extern bitmap node_alloc_table;
extern bitmap block_alloc_table;

void disk_mount();
void disk_format();
int disk_allocate_block();
void read_fnode(p_fnode node, int id);
void write_node(p_fnode node);
#endif //_FDISK_H
