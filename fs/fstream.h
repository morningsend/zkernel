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
    char buffer[BLOCK_FILE_MAX_BYTE_COUNT];
    int flag;
    int block_num;
    int block_count;
};


#endif //_FILE_STREAM_H