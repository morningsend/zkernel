//
// Created by zaiyangli on 4/22/16.
//

#ifndef _FILE_H
#define _FILE_H

#include <stdint-gcc.h>
#define R_ONLY 0
#define W_ONLY 1
#define R_W 3
typedef struct file file;
typedef struct file* p_file;

struct file{
    uint32_t fnode_id;
    int cursor;

};

file* fopen(char* path, uint32_t mode);
int fread(file* fp, char* buf, int size);
void parse_path(char* path, char** breadcrumb, int* n);

#endif //_FILE_H
