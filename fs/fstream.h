//
// Created by zaiyangli on 4/26/16.
//

#ifndef _FILE_STREAM_H
#define _FILE_STREAM_H
#include "fblock.h"

#define FILE_STREAM_OK 0x01
#define FILE_STREAM_EOF 0x02
#define FILE_STREAM_ERROR 0x03

typedef struct fstream fstream;
typedef struct fstream* p_fstream;
struct fstream {
    int offset;
    fblock buffer;
    int flag;
    int block_num;
    uint32_t* block_count;
    uint32_t* blocks;
};

void fstream_commit_read_block(p_fstream stream);
int fstream_has_more_block(p_fstream stream);
void fstream_init(p_fstream stream, p_fnode node);


#endif //_FILE_STREAM_H