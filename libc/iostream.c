//
// Created by zaiyangli on 4/9/16.
//

#include "iostream.h"


static io_buffer stdout_buffer = {
    .buf="", .size=0
};
static io_buffer stdin_buffer = {
    .buf="", .size=0
};
static io_buffer stderr_buffer = {
    .buf="", .size=0
};

const io_stream stdout_stream = {
        .buffer = &stdout_buffer,
        .id=stdout,
        .type=WRITE_ONLY,
        .auto_flush=1,
        .pos = 0
};
const io_stream stdin_stream = {
        .buffer = &stdin_buffer,
        .id=stdin,
        .type=READ_ONLY,
        .auto_flush=0,
        .pos = 0
};
const io_stream stderr_stream = {
        .buffer = &stderr_buffer,
        .id=stderr,
        .type=WRITE_ONLY,
        .auto_flush=1,
        .pos = 0
};
void stream_flush(io_stream* stream){
    if(stream->type==WRITE_ONLY) {
        write(stream->id, stream->buffer->buf, stream->buffer->size);
        clear_buffer(stream->buffer);
        stream -> pos = 0;
    }else if(stream->type == READ_ONLY){
        clear_buffer(stream->buffer);
        stream -> pos = 0;
    }
}
int stream_write(io_stream* stream, char* bytes, int size){
    int written = 0;
    int moreBytes = size;
    char* cursor = bytes;
    do {
        written += append_to_buffer(stream->buffer, cursor, moreBytes);
        moreBytes =size - written;
        cursor = bytes+written;
        if(is_buffer_full(stream->buffer)){
            if(stream->auto_flush)
            stream_flush(stream);
            else {
                break;
            }
        }

    }while(written < size);
    return written;
}
int stream_read(io_stream* stream, char* buf, int size){
    if(stream->type!=READ_ONLY || size < 1) return 0;

    if(is_buffer_empty(stream->buffer)){
        stream_fill(stream);
    }
    if (size >= stream->buffer->size) {
        size = stream->buffer->size - stream-> pos;
    }

    memcpy(buf, stream->buffer->buf + stream->pos, size);
    stream_flush(stream);
    return size;
}

void stream_fill(io_stream* stream){
    int chars_read = read(stream->id, stream->buffer->buf, BUF_SIZE);
    stream->buffer->size = chars_read;
    stream->pos = 0;
}
