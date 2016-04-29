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
    node->block_used_count = 0;
    strncpy(node->name, name, FNODE_MAX_FILE_NAME_LENGTH);
}
void fnode_create_file(p_fnode node, uint32_t fid, uint32_t parent_id, char* name){
    memset(node, (int) sizeof(fnode), 0);
    node->type = FNODE_TYPE_FILE;
    node->parent_id = parent_id;
    node->fid = fid;
    node->filesize = 0;
    node->block_used_count = 0;
    node->block_capacity = 0;
    strncpy(node->name, name, FNODE_MAX_FILE_NAME_LENGTH);
}

void fnode_add_block(p_fnode node, p_fblock block){
    if(node->block_used_count >= FNODE_MAX_BLOCK_CAPACITY || node->block_capacity >= FNODE_MAX_BLOCK_CAPACITY) return;

    node->block_capacity;
    node->blocks[node->block_capacity] = node->blocks[node->block_used_count];

    if(node->type == FNODE_TYPE_DIRECTORY && block->header.type == BLOCK_TYPE_DIRECTORY_ENTRY){
        node->blocks[node->block_used_count++] = block->header.id;
    }
    else if(node->type == FNODE_TYPE_FILE && block->header.type == BLOCK_TYPE_DATA) {
        node->blocks[node->block_used_count++] = block->header.id;
    }
    node->block_capacity++;
}
void fnode_remove_block(p_fnode node, p_fblock block){
    if(node->block_used_count <= 0 || node->block_capacity <= 0)
        return;
    int index=-1;
    for(int i = 0; i < node->block_used_count; i++){
        if(node->blocks[i] == block->header.id){
            index = i;
        }
    }
    if(index > -1){
        node->block_used_count--;
        node->block_capacity--;
        node->blocks[index ] = node->blocks[node->block_used_count];
        node->blocks[node->block_used_count] = node->blocks[node->block_capacity];
    }

}

int fnode_name_matches(p_fnode node, const char* name){
    return strcmp(node->name, name) == 0? 1: 0;
}
int fnode_is_dir(p_fnode node){
    return node->type == FNODE_TYPE_DIRECTORY;
}
int fnode_is_file(p_fnode node){
    return node->type == FNODE_TYPE_FILE;
}