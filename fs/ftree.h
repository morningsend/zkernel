//
// Created by zaiyangli on 4/23/16.
//

#include "path.h"
#include "fdisk.h"

#ifndef _FTREE_H
#define _FTREE_H

#define CURRENT_DIRECTORY_LABEL "."
#define PARENT_DIRECTORY_LABLE ".."

#define OK 1
#define NOT_FOUND 0
#define DIRECTORY_IS_NOT_EMPTY 0x80
#define FILE_NOT_FOUND 0x81
#define FOUND 1
#define FILE_SIZE_MAX (BLOCK_FILE_MAX_BYTE_COUNT * FNODE_MAX_BLOCK_COUNT)

typedef struct ftree_t ftree;

typedef struct ftree_t* p_ftree;

struct ftree_t{
    p_fnode root;

};
p_fnode ftree_get_root_node();
int ftree_traverse_from_root(char* path, p_fnode result);
int ftree_traverse_from(p_fnode node, char* path, p_fnode result);
int ftree_traverse_path_from(p_fnode node, char** parts, int count, p_fnode result);
int ftree_traverse_path_from_root(p_fnode node, char** parts, int count, p_fnode result);

void ftree_insert_node_at(p_fnode node, p_fnode leaf);
void ftree_delete_node_at(p_fnode node);
void ftree_delete_recursive(p_fnode node);
void ftree_get_node_parent(p_fnode node, p_fnode result);
void ftree_move_node(p_fnode node, p_fnode new_parent);
int ftree_find_node_match_name_in_dir(p_fnode node, char *name, p_fnode result);
int ftree_node_find_dir_block_with_space(p_fnode node, p_fblock block);

int ftree_create_file_at(p_fnode parent, char* name, int preallocate, p_fnode out);
int ftree_create_dir_at(p_fnode parent, char *name, int preallocate, p_fnode out);
void ftree_file_delete(p_fnode node);
void ftree_file_delete_data(p_fnode node, int zero_out);
void ftree_dir_delete(p_fnode node);
int ftree_dir_get_file_count(p_fnode node);
void ftree_node_detach_child(p_fnode parent, p_fnode child);
int ftree_file_get_file_size(p_fnode node);

void ftree_node_commit(p_fnode node);
void ftree_block_commit(p_fblock block);
void ftree_file_write_bytes(p_fnode node, char* bytes, uint32_t size);
void ftree_block_read(uint32_t block_id, p_fblock block);

int ftree_file_get_block_capacity(p_fnode node);
#endif //_FTREE_H


