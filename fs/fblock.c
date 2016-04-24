//
// Created by zaiyangli on 4/22/16.
//

#include "fblock.h"
#include "../libc/string.h"
#include "fnode.h"

void block_create_type_data(p_fblock block, uint32_t owner, uint32_t id){
    block->header.type = BLOCK_TYPE_DATA;
    block->header.owner = owner;
    block->header.id = id;
}
void block_create_type_dir(p_fblock block, uint32_t owner, uint32_t parent, uint32_t id){
    memset(block, (int) sizeof(fblock), 0);
    block->header.id = id;
    block->header.type = BLOCK_TYPE_DIRECTORY_ENTRY;
    block->header.owner = owner;
    block->payload.dir_block.count = 0;
}

int block_is_dir_block_empty(p_fblock block){
    return block->header.type == BLOCK_TYPE_DIRECTORY_ENTRY && block->payload.dir_block.count > 0;
}
int block_dir_has_space(p_fblock block){
    return block->header.type == BLOCK_TYPE_DIRECTORY_ENTRY && block->payload.dir_block.count < BLOCK_DIRECTORY_ENTRY_MAX_COUNT;
}
void block_dir_add_entry(p_fblock block, p_fnode entry){
    if(block_dir_has_space(block)){
        block->payload.dir_block.nodes[block->payload.dir_block.count++] = entry->fid;
    }
}