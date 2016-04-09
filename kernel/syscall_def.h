//
// Created by zaiyangli on 4/9/16.
//

#ifndef _SYSCALL_DEF_H
#define _SYSCALL_DEF_H

//System call definitions:

#define SYSTEM_CALL_TABLE_SIZE 10
#define SYSTEM_CALL_1 1
#define SYSTEM_CALL_2 2
#define SYSTEM_CALL_3 3
#define SYSTEM_CALL_4 4
#define SYSTEM_CALL_5 5
#define SYSTEM_CALL_6 6
#define SYSTEM_CALL_7 7
#define SYSTEM_CALL_8 8
#define SYSTEM_CALL_9 9
#define SYSTEM_CALL_10 10

#define SYSCALL_DEFAULT_HANDLER

extern void* syscall_table[SYSTEM_CALL_TABLE_SIZE];

void register_syscall_handler(int syscall_number, void* function);
void register_syscall_default_handler();

#endif //_SYSCALL_DEF_H
