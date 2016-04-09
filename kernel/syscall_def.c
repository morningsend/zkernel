//
// Created by zaiyangli on 4/9/16.
//


#include "syscall_def.h"

static void* syscall_table[SYSTEM_CALL_TABLE_SIZE];
static void_func_void_t syscall_default_handler;

void syscall_init(){
    syscall_default_handler = NULL;
    for(int i = 0; i < SYSTEM_CALL_TABLE_SIZE; i++){
        syscall_table[i] = NULL;
    }
}
void register_syscall_handler(int syscall_number, void* function){
    if(syscall_number < 0 || syscall_number >= SYSTEM_CALL_TABLE_SIZE)
        return;
    syscall_table[syscall_number] = function;
}
void register_syscall_default_handler(void_func_void_t function){
    syscall_default_handler = function;
}

void_func_void_t get_syscall_default_handler(){
    return syscall_default_handler;
}

void* get_syscall_handler(int syscall_number){
    void* p_handler;
    if(syscall_number < 0 || syscall_number >= SYSTEM_CALL_TABLE_SIZE)
        p_handler = get_syscall_default_handler();
    else {
        if (syscall_table[syscall_number] == NULL) {
            p_handler = get_syscall_default_handler();
        } else {
            p_handler = syscall_table[syscall_number];
        }
    }
    return p_handler;
}