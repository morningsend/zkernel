//
// Created by zaiyangli on 4/22/16.
//

#include "file.h"
#include "fs.h"

int _fsize(p_file file){

    return fs_file_get_size(file);
}
p_file _fopen(char* path, int mode){
    return fs_open_file(path, mode);
}
void _fclose(p_file file){
    fs_close_file(file);
}
int _fread(p_file file, char* buffer, int size){
    return fs_read_file(file, buffer, size);
}
void _fwrite(p_file file, char* buffer, int size){
    fs_write_file(file, buffer, size);
}

void _fseek(p_file file, int seek_mode, int offset){
    fs_file_seek(file, seek_mode, offset);
}
void _fflush(p_file file){
    fs_file_flush(file);
}