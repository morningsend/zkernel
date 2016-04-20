//
// Created by zaiyangli on 4/7/16.
//

#include "thread.h"

#define CHECK_BOUNDS(n, lower, upper)

static uint32_t next_thread_id = 1;

void thread_exit(void){
    exit(0);
}
void thread_create(p_thread th,uint32_t priority, void* stack_base, uint32_t stack_size, void (*entry_point)() ){
    th->priority = priority;
    th->pid = next_thread_id;
    th->stack_base = stack_base;
    th->stack_size = stack_size;
    th->entry = entry_point;
    next_thread_id ++;
}

void thread_create_default_context(p_thread th){
    memset(& th->ctx, sizeof(context), 0);
}
void thread_save_context(p_thread th, p_context current){
    memcpy(&th->ctx, current, sizeof(context));
}
void thread_dispatch(p_thread th){
    if(th->entry == NULL) return;
    uint32_t program_state = MODE_USER;

    asm(
    "mov r5, %[stack_base]\n"
    "mov r6, %[entry]\n"
    "mov r7, %[finish]\n"
    "b thread_context_init"
    ::[stack_base] "r" (th->stack_base), [entry] "r" (th->entry), [finish] "r" (thread_exit)
    : "r5", "r6", "r7"
    );/*
    asm(
        "mov r0,#0x1F\n"
        "orr r0,r0, #0x80\n"
        "orr r0,r0, #0x40\n"
        "msr cpsr_c, r0\n"
        "mov sp, %[stack_base]\n"
        "mov lr, %[end]\n"
        "stmfd sp!, {lr}\n"
        "mov r0, %[entry]\n"
        "mov r1, %[program_state]\n"
        "msr spsr, r1\n"
        "movs pc, r0\n"
        :
        :[stack_base] "r" (th->stack_base),[entry] "r" (th->entry), [program_state] "r" (program_state),[end] "r" (thread_exit)
        :"r0", "r1"
    );*/


}

void thread_suspend(p_thread th){

}
void thread_destroy(p_thread th){

}