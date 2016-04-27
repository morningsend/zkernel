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
    ftree_file_read()
}
int fstream_has_more_block(p_fstream stream){
    return (stream->block_num < stream->block_count);
}