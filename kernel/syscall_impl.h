//
// Created by zaiyangli on 4/9/16.
//

#ifndef _SYSCALL_IMPL_H
#define _SYSCALL_IMPL_H

void syscall_def_handler(int syscall_number);
void sys_exit(int code);
int sys_write(int stream, char* bytes, unsigned int size);
int sys_read(int stream, char* buffer, unsigned int size);
int sys_fork();
void sys_execute(char* program_name);
void sys_yield();

#endif //_SYSCALL_IMPL_H
