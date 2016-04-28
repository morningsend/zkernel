//
// Created by zaiyangli on 4/26/16.
//

#include "fstream.h"
#include "fnode.h"
#include "ftree.h"

void fstream_init(p_fstream stream, p_fnode node){
    stream->offset = 0;
    stream->block_num = -1;
    stream->block_count = &node->block_count;
    stream->blocks = node->blocks;
    stream->flag = FILE_STREAM_OK;
}

void fstream_commit_read_block(p_fstream stream){
    if(stream->block_num > 0 && stream->block_num < *stream->block_count) {
        ftree_block_commit(&stream->buffer);
        stream->offset = 0;
    }
    stream->block_num++;
    if(stream->block_num > 0 && stream->block_num < *stream->block_count){
        ftree_block_read(stream->blocks[stream->block_num], & stream->buffer);
    }
}
int fstream_has_more_block(p_fstream stream){
    return (stream->block_num < *stream->block_count);
}

int fstream_seek_to_pos(p_fstream stream, int pos){
    int block_num = pos / BLOCK_FILE_MAX_BYTE_COUNT;
    int offset = pos % BLOCK_FILE_MAX_BYTE_COUNT;
    if(block_num > * stream->block_count) return 0;
    if(block_num != stream->block_num){
        ftree_block_commit(&stream->buffer);
        stream->block_num = block_num;
    }
    stream->offset = offset;
    return OK;
}