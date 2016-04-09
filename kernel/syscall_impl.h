//
// Created by zaiyangli on 4/9/16.
//

#ifndef _SYSCALL_IMPL_H
#define _SYSCALL_IMPL_H

void syscall_def_handler();

void sys_exit(int code);
int sys_write(int stream, void* bytes, unsigned int size);
int sys_read(int stream, void* buffer, unsigned int size);
int sys_fork();
void sys_execute();
void sys_yield();
#endif //_SYSCALL_IMPL_H
