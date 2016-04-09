//
// Created by zaiyangli on 4/9/16.
//

#include "iobuffer.h"




void clear_buffer(io_buffer *buffer){
    buffer->size=0;
    memset(buffer->buf, BUF_SIZE, 0);
}
int write_to_buffer(io_buffer* buffer, char* str, int size){
    //assert(buffer->size <= BUF_SIZE);
    if(size < 0){
        size = 0;
    }
    else if(size > BUF_SIZE){
        size = BUF_SIZE;
    }
    memcpy(buffer->buf, str, size);
    buffer->size = size;
    return size;
}

int append_to_buffer(io_buffer* buffer, char* str, int size){
    if(size < 1){
        return 0;
    }
    int free = BUF_SIZE - buffer->size;
    int overflow = free - size;
    if(overflow > 0){
        size = free;
    }
    memcpy(buffer->buf + buffer->size, str, size);
    buffer->size +=size;
    return size;
}
int is_buffer_full(io_buffer* buffer){
    return buffer->size==BUF_SIZE;
}