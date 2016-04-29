//
// Created by zaiyangli on 4/22/16.
//

#ifndef _FILE_H
#define _FILE_H

#include <stdint-gcc.h>
#include "fnode.h"
#include "fstream.h"
#include "ftree.h"

#define FILE_CREATE 0x80
#define FILE_READ_ONLY 0x10
#define FILE_WRITE_ONLY 0x20
#define FILE_APPEND 0x40
#define READ_WRITE (READ_ONLY | WRITE_ONLY)

#define FILE_SEEK_BEGIN 0x01
#define FILE_SEEK_END 0x02
#define FILE_SEEK_CURRENT 0x03

typedef struct file_t file;
typedef struct file_t* p_file;
/**
 * File descriptor.
 * library functions that handles file i/o requires a file descriptor objector as argument
 * It is not meant to modified by the user
 */


struct file_t {
    fnode node;
    int flag;
    int id;
    fstream stream;
};

int _fsize(p_file file);
p_file _fopen(char* path, int mode);
void _fclose(p_file file);
int _fread(p_file file, char* buffer, int size);
void _fwrite(p_file file, char* buffer, int size);
void _fseek(p_file file, int seek_mode, int offset);
int _ftell(p_file file);
void _fflush(p_file file);
void file_init(p_file file, p_fnode node, int id, int flag);
int _mkdir(char*path);
#endif //_FILE_H
