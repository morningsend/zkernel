//
// Created by zaiyangli on 4/22/16.
//

#include "fnode.h"
#include "../libc/string.h"

void fnode_create_dir(p_fnode node, uint32_t fid, uint32_t parent_id, char* name){
    memset(node, (int) sizeof(fnode), 0);
    node->type = FNODE_TYPE_DIRECTORY;
    node->parent_id = parent_id;
    node->fid = fid;
    node->files_in_dir = 0;
    node->block_count = 0;
    strncpy(node->name, name, FNODE_MAX_FILE_NAME_LENGTH);
}
void fnode_create_file(p_fnode node, uint32_t fid, uint32_t parent_id, char* name){
    memset(node, (int) sizeof(fnode), 0);
    node->type = FNODE_TYPE_FILE;
    node->parent_id = parent_id;
    node->fid = fid;
    node->filesize = 0;
    node->block_count = 0;
    strncpy(node->name, name, FNODE_MAX_FILE_NAME_LENGTH);
}

void fnode_add_block(p_fnode node, p_fblock block){
    if(node->block_count >= FNODE_MAX_BLOCK_COUNT){
        return;
    }
    if(node->type == FNODE_TYPE_DIRECTORY)
        node->blocks[node->block_count++] = block->header.id;
}
void fnode_remove_block(p_fnode node, p_fblock block){
    if(node->block_count <= 0)
        return;
    int index=-1;
    for(int i = 0; i < node->block_count; i++){
        if(node->blocks[i] == block->header.id){
            index = i;
        }
    }
    if(index > -1){
        node->block_count--;
        node->blocks[index ] = node->blocks[node->block_count];
        node->blocks[node->block_count] = 0;
    }
}

int fnode_name_matches(p_fnode node, const char* name){
    return strcmp(node->name, name) == 0? 1: 0;
}
