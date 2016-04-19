//
// Created by zaiyangli on 4/11/16.
//

#include "allocator.h"

#define OVERHEAD (sizeof(alloc_entry))

#define MIN_BLOCK_SIZE (sizeof(alloc_entry) < sizeof(free_list_node)? sizeof(free_list_node):sizeof(alloc_entry))

void* mem_alloc(p_allocator allocator, uint32_t size){
    int new_size = 0;
    size += OVERHEAD;
    if(size < MIN_BLOCK_SIZE) size = MIN_BLOCK_SIZE;
    p_free_list_node node = free_list_find_block_of_size(&allocator->list, size);
    if(node != NULL){
        new_size = (int) (node->block_size - size);
        void* mem = free_list_node_shrink(&allocator->list, node, new_size);
        mark_alloc_entry(mem, size);
        return mem + OVERHEAD;
    }
    return NULL;
}
void mem_free(p_allocator allocator, void *address){
    p_alloc_entry entry = get_mem_alloc_entry(address);
    if(entry->block_size >= MIN_BLOCK_SIZE && entry->block_size <= allocator->list.memory_size) {
        p_free_list_node node = create_free_list_node(entry, entry->block_size);
        free_list_insert_node(&allocator->list, node);
    }
}
void init_alloc_with_pool(p_allocator alloc, void* memory, uint32_t size){
    init_free_list(&alloc->list, memory, size);
}
p_alloc_entry mark_alloc_entry(void* mem, uint32_t size){
    p_alloc_entry entry = (p_alloc_entry) mem;
    entry->block_size = size;
    return entry;
}
p_alloc_entry get_mem_alloc_entry(void*mem){
    return (p_alloc_entry) (mem - OVERHEAD);
}