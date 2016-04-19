//
// Created by zaiyangli on 4/18/16.
//

#ifndef _FREE_LIST_H
#define _FREE_LIST_H

#ifndef NULL
#define NULL ((void*)(0))
#endif

#include <stdint.h>

typedef struct free_list_node_struct free_list_node;
typedef struct free_list_node_struct* p_free_list_node;
typedef struct free_list_struct free_list;
typedef struct free_list_struct* p_free_list;
struct free_list_node_struct {
    p_free_list_node next;
    p_free_list_node previous;
    uint32_t block_size;

};

struct free_list_struct {
    p_free_list_node head;
    p_free_list_node tail;
    void* base_address;
    uint32_t memory_size;
};

void init_free_list(free_list* list, void* memory, uint32_t size);
p_free_list_node create_free_list_node(void* memory, uint32_t size);
p_free_list free_list_insert_node_head(p_free_list list, p_free_list_node node);
p_free_list free_list_insert_node_tail(p_free_list list, p_free_list_node node);
p_free_list free_list_init_with_node(p_free_list list, p_free_list_node node);

void free_list_insert_before(p_free_list_node target, p_free_list_node new_node);
void free_list_insert_after(p_free_list_node target, p_free_list_node new_node);
void* free_list_node_shrink(p_free_list list, p_free_list_node node, uint32_t new_size);
void free_list_node_combine(p_free_list list, p_free_list_node node1, p_free_list_node node2);
void free_list_node_unlink(p_free_list_node first , p_free_list_node second);
void free_list_insert_node(p_free_list list, p_free_list_node node);
p_free_list_node free_list_find_block_of_size(p_free_list list, uint32_t size);
#endif //_FREE_LIST_H
