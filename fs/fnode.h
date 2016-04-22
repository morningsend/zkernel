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

typedef struct fnode_t fnode;
typedef struct fnode_t* p_fnode;

struct fnode_t{
    uint32_t fid;
    uint32_t type;
    char name[16];
    uint32_t blocks[10];
};

void get_root_node(p_fnode node);

#endif //_FNODE_H
