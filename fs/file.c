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
    if(size < 1) 0;
    return fs_read_file(file, buffer, size);
}
void _fwrite(p_file file, char* buffer, int size){
    if(size < 1) return;
    fs_write_file(file, buffer, size);
}

void _fseek(p_file file, int seek_mode, int offset){
    fs_file_seek(file, seek_mode, offset);
}
int _ftell(p_file file){
    return fs_file_tell(file);
}
void _fflush(p_file file){
    fs_flush_file(file);
}

void file_init(p_file fp, p_fnode node, int id, int flag){
    fp->flag = flag;
    fp->id = id;
    if(&fp->node != node)
    fp->node = *node;
    fstream_init(&fp->stream, &fp->node);
}
int _mkdir(char*path){
    fs_create_dir(path);
}

int _fexists(char*path){
    return fs_file_exists(path);
}
int _dir_exists(char* path){
    return fs_dir_exists(path);
}