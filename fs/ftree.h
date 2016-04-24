//
// Created by zaiyangli on 4/23/16.
//

#include "path.h"
#include "fdisk.h"

#ifndef _FTREE_H
#define _FTREE_H

#define CURRENT_DIRECTORY_LABEL "."
#define PARENT_DIRECTORY_LABLE ".."
#define NOT_FOUND 0
#define FOUND 1
#define FILE_SIZE_MAX (BLOCK_FILE_MAX_BYTE_COUNT * FNODE_MAX_BLOCK_COUNT)

typedef struct ftree_t ftree;

typedef struct ftree_t* p_ftree;

struct ftree_t{
    p_fnode root;

};

int ftree_traverse_from_root(char* path, p_fnode result);
int ftree_traverse_from(p_fnode node, char* path, p_fnode result);
void ftree_insert_node_at(p_fnode node, p_fnode leaf);
void ftree_delete_node_at(p_fnode node);
void ftree_delete_recursive(p_fnode node);
void ftree_get_dir_node_parent(p_fnode node, p_fnode result);
void ftree_move_node(p_fnode node, p_fnode new_parent);
int ftree_find_node_match_name_in_dir(p_fnode node, char *name, p_fnode result);
int ftree_node_find_dir_block_with_space(p_fnode node, p_fblock block);


void ftree_create_file_at(p_fnode parent, char* name, int preallocate, int *error);
void ftree_create_dir_at(p_fnode parent, char *name, int preallocate, int* error);
void ftree_file_delete(p_fnode node);
void ftree_file_delete_data(p_fnode node, int zero_out);

int ftree_dir_get_file_count(p_fnode node);



void ftree_file_write_bytes(p_fnode node, char* bytes, uint32_t size);
#endif //_FTREE_H


