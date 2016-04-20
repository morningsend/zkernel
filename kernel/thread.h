//
// Created by zaiyangli on 4/7/16.
//

#ifndef _PROCESS_H
#define _PROCESS_H


#include <stdint-gcc.h>
#include "context.h"
#include "../libc/string.h"
#include "arm.h"
#include "../system/syslib.h"

#define PRIORITY_HIGH 0x4
#define PRIORITY_NORMAL 0x2
#define PRIORITY_LOW 0x1

#define THREAD_STACK_SIZE 0x400

typedef struct thread_struct{
    uint32_t pid;
    context ctx;
    uint32_t priority;
    void* stack_base;
    uint32_t stack_size;
    void (*entry) ();
}thread;

typedef struct thread_struct* p_thread;

void thread_create_default_context(p_thread th);
void thread_save_context(p_thread, p_context current);
void thread_dispatch(p_thread th);
void thread_suspend(p_thread th);
void thread_resume(p_thread th);
void thread_create(p_thread th, uint32_t priority, void* stack_base, uint32_t stack_size, void (*entry_point)() );
void thread_destroy(p_thread th);

void thread_exit(void);

extern void thread_context_init();
#endif //_PROCESS_H
