//
// Created by zaiyangli on 4/2/16.
//

#ifndef _IO_H
#define _IO_H

#include "string.h"
#include <stdarg.h>
#include <stdint.h>

#include "iostream.h"



#ifndef NULL
#define NULL ((void * )0)
#endif

void printf(const char* format, ...);

void putchar(int c);
int getchar();

void puts( char* str);
void puts_n( char* str, int len);
void gets( char* buf, int size);

extern const io_stream stdout_stream;
extern const io_stream stdin_stream;
extern const io_stream stderr_stream;


#endif //_IO_H
