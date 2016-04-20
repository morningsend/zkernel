//
// Created by zaiyangli on 4/9/16.
//

#include "syscall_impl.h"
#include "../device/device.h"

void syscall_def_handler(int syscall_number){
    PL011_puts(UART0, "default syscall handler called");
}
void sys_exit(int code){
    PL011_puts(UART0, "inside sys_exit");
    asm("b kernel_idle");
}
int sys_write(int stream, char* bytes, unsigned int size){
    if(stream==0){
        PL011_put_bytes(UART0, bytes, size);
    }
    return size;
}
int sys_read(int stream, char* buffer, unsigned int size){
    if(stream == 1){
        PL011_gets(UART0, buffer, size);
    }
}
int sys_fork(){
    return 0;
}
void sys_execute(char* program_name){

}
void sys_yield(){

}