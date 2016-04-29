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
    return (stream->block_num < (*stream->block_count -1));
}

int fstream_seek_to_pos(p_fstream stream, int pos){
    int block_num = pos / BLOCK_FILE_MAX_BYTE_COUNT;
    int offset = pos % BLOCK_FILE_MAX_BYTE_COUNT;
    if(block_num > * stream->block_count) return 0;
    if(block_num != stream->block_num){
        ftree_block_commit(&stream->buffer);
        stream->block_num = block_num;
        ftree_block_read(stream->blocks[stream->block_num], &stream->buffer);
    }
    stream->offset = offset;
    return OK;
}
int fstream_write(p_fstream stream, char* buf, int size){
    int block_bytes_free;
    int remaining = size;
    while(remaining > 0){
        block_bytes_free = BLOCK_FILE_MAX_BYTE_COUNT - stream->offset;
        if(block_bytes_free <= 0){
            if(fstream_has_more_block(stream)) {
                fstream_commit_read_block(stream);
            }else{
                break;
            }
        }else{
            remaining -= block_bytes_free;
            block_bytes_free = remaining > 0 ? block_bytes_free : (block_bytes_free + remaining);
            block_data_write(& stream->buffer, stream->offset, buf, block_bytes_free);
            buf += block_bytes_free;
        };
    }
    return remaining > 0 ? size - remaining : size;
}
void fstream_get_next_block(p_fstream stream){
    if(fstream_has_more_block(stream)){
        stream->block_num++;
        ftree_block_read(stream->blocks[stream->block_num], &stream->buffer);
    }
}
int fstream_read(p_fstream stream, char* buf, int size){

    int need_to_read = size;
    int block_available;
    int read;
    while(need_to_read > 0){
        block_available = (int) stream->buffer.payload.data_block.size - stream->offset;
        if(block_available > 0 ) {
            block_available = block_available > need_to_read ? need_to_read : block_available;
            block_read_to_buffer(&stream->buffer, stream->offset, buf, block_available);
            buf += block_available;
            need_to_read -= block_available;
        }else{
            if(fstream_has_more_block(stream)){
                fstream_get_next_block(stream);
            }else {
                break;
            }
        }
    }
    read = need_to_read > 0 ? size - need_to_read: size;
    if(read == 0){
        stream->flag = FILE_STREAM_EOF;
        read = -1;
    }
    return read;
}
int fstream_get_available_bytes(p_fstream stream, uint32_t filesize){
    int bytesUnavaliable = (stream->block_num ) * BLOCK_FILE_MAX_BYTE_COUNT + stream->offset;
    return (int ) filesize - bytesUnavaliable;
}

int fstream_is_eof(p_fstream stream){
    return fstream_has_more_block(stream) || stream->offset < stream->buffer.payload.data_block.size;
}