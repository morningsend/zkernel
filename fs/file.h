//
// Created by zaiyangli on 4/22/16.
//

#ifndef _FILE_H
#define _FILE_H

#include <stdint-gcc.h>
#include "fnode.h"
#include "../libc/iostream.h"

#define FILE_TYPE_DIRECTORY
#define FILE_TYPE_FILE

typedef struct file_t file;
typedef struct file_t* p_file;
typedef struct directory_t directory;
typedef struct directory_t* p_directory;
/**
 * File descriptor.
 * library functions that handles file i/o requires a file descriptor objector as argument
 * It is not meant to modified by the user
 */

struct file_t {
    fnode node;
    io_stream stream;
    int open_mode;
};

struct directory_t{
    fnode node;
    uint32_t dir_entry_buffer[16];
};

int _fsize(p_file file);
void _fopen(char* path, int mode, p_file file);
void _fclose(p_file file);
int _fread(p_file file, char* buffer, int size);
void _fwrite(p_file file, char* buffer, int size);
void _fseek(p_file file, int seek_mode, int offset);
void _dir_entries(p_directory dir, char** entries, int* argc);
#endif //_FILE_H
