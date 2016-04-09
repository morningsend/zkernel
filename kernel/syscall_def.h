//
// Created by zaiyangli on 4/9/16.
//

#ifndef _SYSCALL_DEF_H
#define _SYSCALL_DEF_H
#include <stddef.h>
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

#define SYSCALL_Exit SYSTEM_CALL_1
#define SYSCALL_Fork SYSTEM_CALL_2
#define SYSCALL_Yield SYSTEM_CALL_3
#define SYSCALL_Execute SYSTEM_CALL_4
#define SYSCALL_Read SYSTEM_CALL_5
#define SYSCALL_Write SYSTEM_CALL_6

typedef void (*void_func_void_t)() ;


void register_syscall_handler(int syscall_number, void* function);
void register_syscall_default_handler(void_func_void_t function);
void syscall_init();
void_func_void_t get_syscall_default_handler();
void* get_syscall_handler(int syscall_number);
#endif //_SYSCALL_DEF_H
