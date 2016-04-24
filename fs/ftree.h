//
// Created by zaiyangli on 4/23/16.
//

#include "path.h"
#include "fdisk.h"

#ifndef _FTREE_H
#define _FTREE_H


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
void ftree_move_node(p_fnode previous_parent, p_fnode next_parent, p_fnode node);
int ftree_find_node_match_name_in_dir(p_fnode node, char *name, p_fnode result);
int ftree_node_find_dir_block_with_space(p_fnode node, p_fblock block);
#endif //_FTREE_H


