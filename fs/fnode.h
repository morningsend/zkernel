//
// Created by zaiyangli on 4/22/16.
//

#ifndef _FNODE_H
#define _FNODE_H

#include <stdint.h>
#include "fblock.h"

#define ROOT_NODE_ID 0
#define FNODE_TYPE_FILE 1
#define FNODE_TYPE_DIRECTORY 0
#define FNODE_ALIGN_SIZE sizeof(fnode)
#define FNODE_PER_BLOCK (BLOCK_SIZE_BYTES/FNODE_ALIGN_SIZE)
#define FNODE_MAX_BLOCK_COUNT 23
#define FNODE_MAX_FILE_NAME_LENGTH 15
typedef struct fnode_t fnode;
typedef struct fnode_t* p_fnode;
struct fnode_t{
    uint32_t fid;
    uint32_t parent_id;
    uint32_t type;
    char name[FNODE_MAX_FILE_NAME_LENGTH + 1];
    union {
        uint32_t filesize;
        uint32_t files_in_dir;
    };
    uint32_t block_count;
    uint32_t blocks[FNODE_MAX_BLOCK_COUNT];
};

void fnode_create_dir(p_fnode node, uint32_t fid, uint32_t parent_id,  char* name);
void fnode_create_file(p_fnode node, uint32_t fid, uint32_t parent_id, char* name);

void fnode_remove_file_from_dir(p_fnode dir, p_fnode file);

void fnode_file_append(p_fnode file, const char* data, int n);

void fnode_add_block(p_fnode node, p_fblock block);


int fnode_name_matches(p_fnode, const char* name);
#endif //_FNODE_H
