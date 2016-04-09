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

}

int read(int stream, void* buffer, int size){

    return size;
}
int write(int stream, void* buffer, int size){
    _SYS_CALL_ARG_3(SYSCALL_Write, stream, buffer, size);
    return size;
}

void execute(const char* program){
    return;
}