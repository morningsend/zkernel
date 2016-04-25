//
// Created by zaiyangli on 4/22/16.
//

#include "fblock.h"
#include "../libc/string.h"
#include "fnode.h"

#ifndef NULL
#define NULL ((void*)0)
#endif

void block_create_type_data(p_fblock block,uint32_t id, char* data, uint32_t n){
    block->header.type = BLOCK_TYPE_DATA;
    block->header.id = id;
    if(n > BLOCK_FILE_MAX_BYTE_COUNT) n = BLOCK_FILE_MAX_BYTE_COUNT;
    block->payload.data_block.size = n;
    if(data != NULL){
        memcpy(block->payload.data_block.data, data, n);
    }
}
void block_create_type_dir(p_fblock block, uint32_t id){
    memset(block, (int) sizeof(fblock), 0);
    block->header.id = id;
    block->header.type = BLOCK_TYPE_DIRECTORY_ENTRY;
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
void block_dir_remove_entry(p_fblock block, p_fnode entry){
    uint32_t temp;
    if(block->header.type==BLOCK_TYPE_DIRECTORY_ENTRY && block->payload.dir_block.count > 0){
        for(int i = 0; i < block->payload.dir_block.count; i++){
            if(block->payload.dir_block.nodes[i] == entry->fid){
                temp = block->payload.dir_block.nodes[block->payload.dir_block.count-1];
                block->payload.dir_block.nodes[i] = temp;
                block->payload.dir_block.nodes[block->payload.dir_block.count-1] = 0;
                block->payload.dir_block.count--;
                break;
            }
        }
    }


}