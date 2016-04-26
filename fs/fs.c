//
// Created by zaiyangli on 4/22/16.
//

#include "fs.h"



void fs_init(){
    int error;
    disk_mount(&error);
    if(error == DISK_UNFORMATTED_ERROR){
        disk_format();
    }else if(error == DISK_NO_ROOT_FOUND){
        disk_format();
    }
}
void fs_table_init(p_fs_table table){
    for(int i = 0; i < FILE_TABLE_SIZE; i++){
        table->file_table[i] = NULL;
    }
    table->driver = fs_driver;
    table->lock = LOCK_FREE;
}
void fs_table_insert(p_fs_table table, p_fs_entry entry){

}
void fs_table_remove(p_fs_table table, p_fs_entry entry){

}
void fs_table_get(p_fs_table table, int eid, p_fs_entry entry){

}
void fs_table_set(p_fs_table table, int eid, p_fs_entry entry){

}

const fs_operations fs_driver = {
    
};