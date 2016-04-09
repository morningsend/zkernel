//
// Created by zaiyangli on 4/8/16.
//

#include "sys_init.h"


void system_init(){
    register_syscall_default_handler(syscall_def_handler);
    register_syscall_handler(SYSCALL_Write, sys_write);
    register_syscall_handler(SYSCALL_Read, sys_read);
    register_syscall_handler(SYSCALL_Exit, sys_exit);
}

void user_init(){
    _start();
}