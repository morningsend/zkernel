//
// Created by zaiyangli on 4/22/16.
//

#include "fs.h"

void fs_init(int* error){
    disk_mount(error);
    if(*error == DISK_UNFORMATTED_ERROR){
        disk_format();
    }else if(*error == DISK_NO_ROOT_FOUND){
        disk_format();
    }
}
void fs_get_file_iterator(char* path, p_file* file){

}
void fs_create_file_at(char* path, char* name, void* data, int n_bytes, p_file* file, int overwrite){

}
void fs_create_dir_at(char* path, char* name, p_file* file){

}
void fs_open_file(char* path, p_file* file  ){

}
void fs_close_file(p_file* file){

}