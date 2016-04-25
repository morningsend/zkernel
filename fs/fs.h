//
// Created by zaiyangli on 4/22/16.
//

#ifndef _FS_H
#define _FS_H
#include "ftree.h"
#include "file.h"

void fs_init();
void fs_get_file_iterator(char* path, p_file* file);
void fs_create_file_at(char* path, char* name, void* data, int n_bytes, p_file* file, int overwrite);
void fs_create_dir_at(char* path, char* name, p_file* file);
void fs_open_file(char* path, p_file* file  );
void fs_close_file(p_file* file);

#endif //_FS_H
