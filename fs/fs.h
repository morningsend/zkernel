//
// Created by zaiyangli on 4/22/16.
//

#ifndef _FS_H
#define _FS_H
#include "ftree.h"
#include "file.h"
#include "../libc/array.h"
#include "../kernel/mutex.h"
typedef struct fs_table fs_table;
typedef struct fs_table* p_fs_table;
typedef struct fs_entry fs_entry;
typedef struct fs_entry* p_fs_entry;

struct fs_operations;
struct fs_entry;
typedef struct fs_operations fs_operations;
typedef struct fs_operations* p_fs_operations;

#define FILE_TABLE_SIZE 64
struct fs_entry{
    int id;
    uint32_t flag;
    fnode node;
};
struct fs_operations {
    int (*fread) (p_file file, char* buf, int size);
    int (*fopen) (p_file file,char* path, int open_mode);
    void (*fclose) (p_file file);
    int (* fwrite) (p_file file, char* buf, int size);
    int (*mkdir) (p_file file,char* path, char* dir_name);
};
struct fs_table{
    fs_entry file_table[FILE_TABLE_SIZE];
    uint32_t lock;
    fs_operations driver;
};

extern const fs_operations fs_driver;




void fs_init();
void fs_table_init(p_fs_table table);
void fs_table_insert(p_fs_table table, p_fs_entry entry);
void fs_table_remove(p_fs_table table, p_fs_entry entry);
void fs_table_get(p_fs_table, int eid, p_fs_entry entry);
void fs_table_set(p_fs_table, int eid, p_fs_entry entry);


#endif //_FS_H
