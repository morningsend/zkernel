//
// Created by zaiyangli on 4/7/16.
//

#include "syslib.h"


void exit(int code){
    _SYS_CALL_ARG_1(SYSCALL_Exit, code);
}
int fork(){
    return 0;
}

void yield(){
    _SYS_CALL_(SYSCALL_Yield);
}

int read(int stream, char* buffer, int size){
    if(size > 0) {
        _SYS_CALL_ARG_3(SYSCALL_Read, stream, buffer, size);
    }
    return size;
}
int write(int stream, char* buffer, int size){
    if(size > 0){
        _SYS_CALL_ARG_3(SYSCALL_Write, stream, buffer, size);
    }
    return size;
}

void execute(void (*program)()){
    return;
}