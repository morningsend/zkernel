//
// Created by zaiyangli on 4/2/16.
//

#ifndef _IO_H
#define _IO_H

#include <string.h>
#include <stdarg.h>
#include <stdint.h>
#define BUF_SIZE 128

#ifndef NULL
#define NULL ((void * )0)
#endif

typedef struct io_stream_struct{
    void* resource;
} io_stream;

typedef struct io_buffer_struct {
    char buf[BUF_SIZE];
    int size;
    int auto_flush;
    io_stream* stream;
} io_buffer;

void printf(const char* format, ...);

void initialize_buffer(io_buffer *buffer, int auto_flush, int clear);
void write_to_buffer(io_buffer* buffer, const char* str, int size);
void flush_buffer(io_buffer* buffer, io_stream* st);
int is_buffer_full(io_buffer* buffer);

void putchar(int c);
int getchar();

void puts(const char* str);
void puts_n(const char* str, int len);
void gets(const char* buf, int size);


extern io_buffer stdout_buffer;
extern io_buffer stdin_buffer;
extern io_buffer stderr_buffer;

#endif //_IO_H
