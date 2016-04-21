//
// Created by zaiyangli on 4/9/16.
//

#ifndef _IOBUFFER_H
#define _IOBUFFER_H
#include "string.h"
#define BUF_SIZE 128

typedef struct io_buffer_struct {
    char buf[BUF_SIZE];
    int size;
} io_buffer;

void clear_buffer(io_buffer *buffer);
int write_to_buffer(io_buffer* buffer, char* str, int size);
int append_to_buffer(io_buffer* buffer, char* str, int size);
int is_buffer_full(io_buffer* buffer);
int is_buffer_empty(io_buffer* buffer);

#endif //_IOBUFFER_H
