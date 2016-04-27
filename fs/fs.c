//
// Created by zaiyangli on 4/22/16.
//

#include "fs.h"
static fs_table file_open_table;
void fs_init(){
    int error;
    disk_mount(&error);
    if(error == DISK_UNFORMATTED_ERROR){
        disk_format();
        disk_mount;
    }else if(error == DISK_NO_ROOT_FOUND){
        disk_format();
        disk_mount;
    }
    fs_table_init(&file_open_table);
}
void fs_table_init(p_fs_table table){

    table->lock = LOCK_FREE;
}

p_file fs_open_file(char* path, int mode){
    p_fnode root = ftree_get_root_node();

}
void fs_close_file(p_file file){

}
void fs_flush_file(p_file file){

}

int fs_read_file(p_file file, char* buf, int size){

}
void fs_write_file(p_file file, char* buf, int size){

}
int fs_file_get_size(p_file file){

}

void fs_file_seek(p_file file, int seek_mode, int offset){

}
void fs_file_flush(p_file file){

}