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
        .auto_flush=1
};
const io_stream stdin_stream = {
        .buffer = &stdin_buffer,
        .id=stdin,
        .type=READ_ONLY,
        .auto_flush=0
};
const io_stream stderr_stream = {
        .buffer = &stderr_buffer,
        .id=stderr,
        .type=WRITE_ONLY,
        .auto_flush=1
};

void stream_flush(io_stream* stream){
    write(stream->id, stream->buffer->buf, stream->buffer->size);
    clear_buffer(stream->buffer);
}
int stream_write(io_stream* stream, char* bytes, int size){
    int written = 0;
    int moreBytes = size;
    char* cursor = bytes;
    do {
        written += append_to_buffer(stream->buffer, bytes, moreBytes);
        moreBytes =size - written;
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

}