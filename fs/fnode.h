//
// Created by zaiyangli on 4/22/16.
//

#ifndef _FNODE_H
#define _FNODE_H
#include <stdint.h>

#define FNODE_TYPE_FILE 1
#define FNODE_TYPE_DIRECTORY 0


typedef struct fnode_t fnode;
typedef struct fnode_t* p_fnode;

struct fnode_t{
    uint32_t fid;
    uint32_t type;
    char name[16];
    uint32_t block_addr;
};

#endif //_FNODE_H
