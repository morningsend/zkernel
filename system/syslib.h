//
// Created by zaiyangli on 4/7/16.
//

#ifndef _SYS_LIB_H
#define _SYS_LIB_H

#include "../kernel/syscall_def.h"
#include "systemcall.h"


void execute(const char* program);
void exit(int code);
int fork();
void yield();
int read(int stream, char* buffer, int size);
int write(int stream, char* buffer, int size);

#endif //_SYS_LIB_H
