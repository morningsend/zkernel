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
    th->id = next_thread_id;
    th->parent_id = 0;
    th->stack_base = stack_base;
    th->stack_size = stack_size;
    th->entry = entry_point;
    th->exit_code = 0;
    th->state = THREAD_STATE_NEW;
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
    switch(th->state){
        case THREAD_STATE_NEW:
            th->state = THREAD_STATE_RUNNING;
            asm(
            "mov r5, %[stack_base]\n"
                    "mov r6, %[entry]\n"
                    "mov r7, %[finish]\n"
                    "b thread_context_init"
            ::[stack_base] "r" (th->stack_base), [entry] "r" (th->entry), [finish] "r" (thread_exit)
            : "r5", "r6", "r7"
            );
            break;
        case THREAD_STATE_READY:
            th->state = THREAD_STATE_RUNNING;
            asm(
                "nop"
            );
        case THREAD_STATE_SUSPENDED:

            break;
        case THREAD_STATE_WAITING:
            break;
        default:
            break;
    }
}

void thread_suspend(p_thread th){
    th->state = THREAD_STATE_SUSPENDED;
}
void thread_destroy(p_thread th){

}
void thread_fork(p_thread parent, p_thread child, void* stack){
    child->priority = parent->priority;
    memcpy(&child->ctx,&parent->ctx, sizeof(context));
    int sp_offset = ((int) parent->stack_base ) - ((int)parent->ctx.stackPointer);
    child->ctx.stackPointer = (uint32_t) child->stack_base - sp_offset;
    child->stack_size = parent->stack_size;
    child->state = THREAD_STATE_READY;
    child->stack_base = stack + child->stack_size;
    child->parent_id = parent->id;
    child->id = next_thread_id;
    child->entry = parent->entry;
    child->exit_code = parent->exit_code;
    next_thread_id++;
}

void thread_load_init_context(p_thread th){
    memset(&th->ctx, sizeof(context),0);
    th->ctx.stackPointer = th->stack_base;
    th->ctx.programState = MODE_USER;
    th->ctx.linkRegister = th->entry;
    th->state = THREAD_STATE_READY;
    th->ctx.programCounter = th->entry;
}
