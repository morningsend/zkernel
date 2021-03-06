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
#define BLOCK_DIRECTORY_ENTRY_MAX_COUNT (BLOCK_SIZE_WORDS - sizeof(block_header)/4 - 1)
#define BLOCK_FILE_MAX_BYTE_COUNT (BLOCK_SIZE_BYTES - sizeof(block_header)*4 - 4)
struct fnode_t;
typedef struct fnode_t* p_fnode;

typedef struct block_header block_header;
typedef struct block_header* p_block_header;
struct block_header{
    uint32_t id;
    uint32_t type;
};

typedef struct block_directory_entry_t block_directory_entry;
typedef struct block_directory_entry_t* p_block_directory_entry;



struct block_directory_entry_t{
    uint32_t count;
    uint32_t nodes[BLOCK_DIRECTORY_ENTRY_MAX_COUNT];
};


typedef struct fblock_t fblock;
typedef struct fblock_t* p_fblock;
typedef union block_payload block_payload;
typedef struct block_data_t block_data;
typedef struct block_data_t* p_block_data;

struct block_data_t {
    uint32_t size;
    char data[BLOCK_FILE_MAX_BYTE_COUNT];
};
union block_payload{
    block_data data_block;
    block_directory_entry dir_block;
};
struct fblock_t {
    block_header header;
    block_payload payload;
};

void block_create_type_dir(p_fblock block, uint32_t id);
void block_create_type_data(p_fblock block,uint32_t id, char* data, uint32_t n);

int block_is_dir_block_empty(p_fblock block);
void block_dir_add_entry(p_fblock block, p_fnode entry);

void block_dir_remove_entry(p_fblock block, p_fnode entry);
void block_data_write(p_fblock block, int start, char* buf, int size);
int block_read_to_buffer(p_fblock block, int offset, char* buf, int size);
#endif //_FBLOCK_H
