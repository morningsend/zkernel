//
// Created by zaiyangli on 4/26/16.
//

#ifndef _FIO_H
#define _FIO_H

typedef struct file_t file;

struct file_t {
    char name[16];
    
};

int fopen(char* path, int open_mode);
int fclose(int id);
int fread(int id, char* buf, int size);
int fwrite(int id, char* buf, int size);
int mkdir(char* buf, int size);
int ls(char*buf, void(*f)(char*));
#endif //_FIO_H
