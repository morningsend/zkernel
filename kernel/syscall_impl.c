//
// Created by zaiyangli on 4/9/16.
//

#include "syscall_impl.h"
#include "../device/device.h"

void syscall_def_handler(){
    PL011_puts(UART0, "default syscall handler called");
}

void sys_exit(int code){

}
int sys_write(int stream, void* bytes, unsigned int size){
    if(stream==0){
        PL011_put_bytes(UART0, bytes, size);
    }
    return size;
}
int sys_read(int stream, void* buffer, unsigned int size){
    return size;
}
int sys_fork(){

}
void sys_execute(){

}
void sys_yield(){

}