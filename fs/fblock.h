//
// Created by zaiyangli on 4/22/16.
//

#ifndef _FBLOCK_H

#define _FBLOCK_H

#include <stdint-gcc.h>


#define BLOCK_TYPE_DIRECTORY_ENTRY 0
#define BLOCK_TYPE_DATA 1
#define BLOCK_TYPE_LINK_ENTRY 2

#define BLOCK_SIZE_BYTES 128
#define BLOCK_SIZE_WORDS (BLOCK_SIZE_BYTES / sizeof(uint32_t))

typedef struct block_header block_header;
typedef struct block_header* p_block_header;
struct block_header{
    uint32_t type;
    uint32_t parent_node;
};

typedef struct block_directory_entry_t block_directory_entry;
typedef struct block_directory_entry_t* p_block_directory_entry;

struct block_directory_entry_t{
    uint32_t count;
    uint32_t current;
    uint32_t parent;
    uint32_t nodes[BLOCK_SIZE_WORDS - sizeof(block_header)];
};
typedef struct block_data_t block_data;
typedef struct block_data_t* p_block_data;

struct block_data_t {
    uint32_t size;
    char data[BLOCK_SIZE_BYTES];
};


typedef struct fblock_t fblock;
typedef struct fblock_t* p_fblock;
typedef union block_payload block_payload;
union block_payload{
    block_data data_block;
    block_directory_entry dir_block;
};
struct fblock_t {
    block_header header;
    block_payload payload;
};

#endif //_FBLOCK_H
