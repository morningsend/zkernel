//
// Created by zaiyangli on 4/26/16.
//

#ifndef _FILE_STREAM_H
#define _FILE_STREAM_H
#include "fblock.h"

#define FILE_STREAM_OK 0x01
#define FILE_STREAM_EOF 0x02
#define FILE_STREAM_ERROR 0x03
#define FILE_STREAM_CLOSED 0x04
typedef struct fstream fstream;
typedef struct fstream* p_fstream;
struct fstream {
    int offset;
    fblock buffer;
    int flag;
    int block_num;
    uint32_t* block_count;
    uint32_t* blocks;
    uint32_t* block_capacity;
};

void fstream_commit_read_block(p_fstream stream);
int fstream_has_more_block(p_fstream stream);
void fstream_init(p_fstream stream, p_fnode node);
int fstream_seek_to_pos(p_fstream stream, int currentPos);
int fstream_write(p_fstream stream, char* buf, int size);
int fstream_read(p_fstream stream, char* buf, int size);
int fstream_get_available_bytes(p_fstream stream, uint32_t filesize);
int fstream_is_eof(p_fstream stream);
int fstream_tell_pos(p_fstream stream);
void fstream_flush(p_fstream stream);
#endif //_FILE_STREAM_H