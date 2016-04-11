//
// Created by zaiyangli on 4/2/16.
//

#ifndef _STRING_H
#define _STRING_H

#include "math.h"

void strcpy(char* destination, char* source);
void strrevcpy(char *str, char * buf);
void strncpy(char* destination, char* source, int n);

void strrev(char *str, int length);

int strlen(const char* str);

int strcmp(const char* string1, const char* string2);

int format_int(int n, char *buf, int len);
int format_int_to_hex(int n, char* buf, int len);
int format_float(float n, char *buf, int len);

void memset(void* buf, int size, int value);
void memcpy(void* destination, void* source, int size);
#endif //_STRING_H
