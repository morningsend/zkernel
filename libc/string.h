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

void strcat(char* buffer, char* source);

int format_int(int n, char *buf, int len);
int format_int_to_hex(int n, char* buf, int len);
int format_float(float n, char *buf, int len);

void memset(void* buf, int size, int value);
void memcpy(void* destination, void* source, int size);

void str_splt(char separator, char* str, char** parts, int n, int* part_count );
void str_splt_ws(char* str, char** parts, int n, int* part_count);
char* skip_ws(char* string);
char* skip_non_ws(char* string);
char* skip_char_match(char ch, char* str);
char* skip_char_not_match(char ch, char* str);

void strsubn(char* str, int begin, int length, char* buf);
void strsub(char* str, int begin, char* buf);

#endif //_STRING_H
