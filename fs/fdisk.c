//
// Created by zaiyangli on 4/22/16.
//

#include "fdisk.h"
#include "../libc/string.h"


bitmap node_alloc_table;
bitmap block_alloc_table;
static fnode root_node;

static uint8_t block_buffer[BLOCK_SIZE_BYTES];

void disk_mount(){
    disk_rd(BITMAP_ALLOC_TABLE_FNODE, (uint8_t *) node_alloc_table.bits, BLOCK_SIZE_BYTES);
    disk_rd(BITMAP_ALLOC_TABLE_DATA, (uint8_t *) block_alloc_table.bits, BLOCK_SIZE_BYTES);
}
void read_root_dir(){
    read_fnode(&root_node, ROOT_NODE_ID);
}
void disk_format(){
    memset(&root_node, sizeof(fnode), 0);
    memset(&node_alloc_table, sizeof(node_alloc_table),0);
    memset(&block_alloc_table, sizeof(node_alloc_table),0);
    root_node.fid = ROOT_NODE_ID;
    bitmap_set_on(&node_alloc_table, ROOT_NODE_ID);
    int block_id = disk_allocate_block();

}

int disk_allocate_block(){
    int bid = bitmap_scan_first_zero(&block_alloc_table);

    if(bid < DATA_BLOCK_LIMIT)
    {
        bitmap_set_on(&block_alloc_table, (uint32_t)bid);
        return bid;
    }
    return -1;
}
int disk_allocate_fnode(){
    int fid = bitmap_scan_first_zero(&node_alloc_table);

    if(fid < FNODE_LIMIT)
    {
        bitmap_set_on(&node_alloc_table, (uint32_t)fid);
        return fid;
    }
    return -1;
}
void read_fnode(p_fnode node, int id){
    uint32_t block_addr = 2 + id/FNODE_PER_BLOCK;
    int offset = FNODE_ALIGN_SIZE * (id % FNODE_PER_BLOCK) ;
    disk_rd(block_addr,block_buffer,BLOCK_SIZE_BYTES);
    *node = *(p_fnode)(block_buffer + offset);
}
void write_node(p_fnode node){
    uint32_t block_addr = 2 + node->fid/FNODE_PER_BLOCK;
    int offset = FNODE_ALIGN_SIZE * (node->fid % FNODE_PER_BLOCK) ;
    disk_rd(block_addr,block_buffer,BLOCK_SIZE_BYTES);
    *(p_fnode)(block_buffer + offset) = *node;
    disk_wr(block_addr, block_buffer, BLOCK_SIZE_BYTES);
}