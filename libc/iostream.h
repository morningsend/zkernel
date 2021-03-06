//
// Created by zaiyangli on 4/9/16.
//

#ifndef _IOSTREAM_H
#define _IOSTREAM_H

#include "iobuffer.h"
#include "../system/syslib.h"


#define stdout 0
#define stdin 1
#define stderr 2

#define READ_ONLY 0x01
#define WRITE_ONLY 0x02


#define EOF (-1)

typedef struct io_stream_struct{
    io_buffer* buffer;
    int id;
    int type;
    int auto_flush;
    int pos;
} io_stream;

typedef enum stream_seek_mode {
    BEGIN, END, CURRENT
}stream_seek_mode;

void stream_flush(io_stream* stream);
int stream_write(io_stream* stream, char* bytes, int size);
int stream_read(io_stream* stream, char* buf, int size);

void stream_fill(io_stream* stream);
extern const io_stream stdout_stream;
extern const io_stream stdin_stream;
extern const io_stream stderr_stream;

#endif //_IOSTREAM_H
