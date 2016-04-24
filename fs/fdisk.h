//
// Created by zaiyangli on 4/22/16.
//

#ifndef _FDISK_H
#define _FDISK_H

#include "../device/device.h"
#include "bitmap.h"
#include "fblock.h"
#include "fnode.h"

#define DISK_HEADER_BLOCK_ID 0
#define BITMAP_ALLOC_TABLE_FNODE (DISK_HEADER_BLOCK_ID + 1)
#define BITMAP_ALLOC_TABLE_DATA (BITMAP_ALLOC_TABLE_FNODE + 1)
#define FNODE_LIMIT 1024
#define DATA_BLOCK_LIMIT 1024
#define FNODE_BLOCK_BEGIN (BITMAP_ALLOC_TABLE_DATA+1)
#define DATA_BLOCK_BEGIN (FNODE_BLOCK_BEGIN+FNODE_LIMIT/FNODE_PER_BLOCK)

#define ROOT_DIR_NAME "/"

#define DISK_UNFORMATTED_ERROR 0x01
#define DISK_NO_ROOT_FOUND 0x02
#define DISK_MOUNT_OK 0x00

#define FILESYSTEM_MAGIC "zfs"

#define ERROR_CANNOT_ALLOCATE_FNODE 0x01
#define ERROR_CANNOT_ALLOCATE_BLOCK 0x02
/**
 * File system layout:
 *
 * ---------------------------
 *  Disk Header:
 *      <magic string>
 *      <format information>
 * ---------------------------
 *  fnode allocation bitmap
 * ---------------------------
 *  data region allocation bitmap
 * ---------------------------
 *  blocks containing fnodes
 *
 *
 *
 *
 * ---------------------------
 *  blocks containing file data
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * ---------------------------
 */
typedef struct fdisk_header fdisk_header;
typedef struct fdisk_header* p_fdisk_header;

struct fdisk_header{
    char magic[8];
    char padding[BLOCK_SIZE_BYTES - 8];
};

extern bitmap node_alloc_table;
extern bitmap block_alloc_table;

void read_root_dir();

void disk_mount(int* error);

void disk_format();

int disk_allocate_block();
int disk_allocate_fnode();
void disk_free_block(uint32_t index);
void disk_free_fnode(uint32_t index);

void write_alloc_tables();

void read_fnode(uint32_t id, p_fnode node);
void write_fnode(p_fnode node);
void write_data_block(p_fblock block);
void read_data_block (uint32_t id, p_fblock block );
int get_dir_entries_count(p_fnode node);
void read_disk_header(p_fdisk_header header);
void write_disk_header(p_fdisk_header header);
void verify_partition(p_fdisk_header header, int* error);
p_fnode disk_get_root_node();;
void disk_data_block_zero_out(int block_id);

void ftree_file_read(p_fnode node, char* buffer, uint32_t size);

#endif //_FDISK_H
