//
// Created by zaiyangli on 4/22/16.
//

#ifndef _FS_H
#define _FS_H
#include "ftree.h"
#include "file.h"
#include "../kernel/mutex.h"
#include "fstream.h"
#define FILE_TABLE_SIZE 64

#ifndef BITMAP_64
#define BITMAP_64
BITMAP_GEN_DEF(64)
#endif

typedef struct fs_table fs_table;
typedef struct fs_table* p_fs_table;
struct file_t;

struct fs_table{
    struct file_t file_table[FILE_TABLE_SIZE];
    uint32_t lock;
    bitmap_64 ft_alloc_map;
};

void fs_init();
void fs_table_init(p_fs_table table);
p_file fs_open_file(char* path, int mode);
void fs_close_file(p_file file);
void fs_flush_file(p_file file);
void fs_update_file_size(p_file file);
int fs_read_file(p_file file, char* buf, int size);
void fs_write_file(p_file file, char* buf, int size);

int fs_file_get_size(p_file file);

void fs_file_seek(p_file file, int seek_mode, int offset);
int fs_file_tell(p_file file);
int fs_create_dir(char* path);
#endif //_FS_H
