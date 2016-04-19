//
// Created by zaiyangli on 4/11/16.
//

#ifndef _ALLOCATOR_H
#define _ALLOCATOR_H

#include <stdint.h>
#include "free_list.h"

#ifndef NULL
#define NULL ((void *) 0)
#endif

typedef struct allocator_struct allocator;
typedef struct allocator_struct* p_allocator;
typedef struct alloc_entry_struct alloc_entry;
typedef struct alloc_entry_struct* p_alloc_entry;

struct allocator_struct {
    free_list list;
};
struct alloc_entry_struct {
    uint32_t block_size;
};
void* mem_alloc(p_allocator allocator, uint32_t size);
void mem_free(p_allocator allocator, void* address);
void init_alloc_with_pool(p_allocator alloc, void* memory, uint32_t size);
p_alloc_entry mark_alloc_entry(void* memory, uint32_t size);
p_alloc_entry get_mem_alloc_entry(void*mem);
#endif //_ALLOCATOR_H
