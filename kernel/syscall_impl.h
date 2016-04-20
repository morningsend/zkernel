//
// Created by zaiyangli on 4/9/16.
//

#ifndef _SYSCALL_IMPL_H
#define _SYSCALL_IMPL_H

#include "schedule.h"
#include "thread.h"
void syscall_def_handler(int syscall_number);
void sys_exit(int code);
int sys_write(int stream, char* bytes, unsigned int size);
int sys_read(int stream, char* buffer, unsigned int size);
int sys_fork();
void sys_execute(void(*func)());
void sys_yield(p_thread th, p_context thread_context);

#endif //_SYSCALL_IMPL_H
