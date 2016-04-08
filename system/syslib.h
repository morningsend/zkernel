//
// Created by zaiyangli on 4/7/16.
//

#ifndef _SYS_LIB_H
#define _SYS_LIB_H

void execute(const char* program);
void exit(int code);
int fork();
void yield();
int read(int stream, void* buffer, unsigned int size);
int write(int stream, void* buffer, unsigned int size);

#endif //_SYS_LIB_H
