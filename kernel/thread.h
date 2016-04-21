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

#define PRIORITY_LOW_CPU_TIME 1
#define PRIORITY_NORMAL_CPU_TIME 3
#define PRIORITY_HIGH_CPU_TIME 5

#define THREAD_STATE_SUSPENDED 0x02
#define THREAD_STATE_WAITING 0x03
#define THREAD_STATE_READY 0x04
#define THREAD_STATE_NEW 0x05
#define THREAD_STATE_RUNNING 0x01

#define THREAD_STACK_SIZE 0x400

typedef struct thread_struct{
    uint32_t id;
    uint32_t parent_id;
    context ctx;
    uint32_t priority;
    void* stack_base;
    uint32_t stack_size;
    uint32_t state;
    void (*entry) ();
    int exit_code;
    uint32_t cpu_time;
}thread;

typedef struct thread_struct* p_thread;

void thread_create_default_context(p_thread th);
void thread_save_context(p_thread, p_context current);
void thread_dispatch(p_thread th);
void thread_suspend(p_thread th);
void thread_resume(p_thread th);
void thread_create(p_thread th, uint32_t priority, void* stack_base, uint32_t stack_size, void (*entry_point)() );
void thread_destroy(p_thread th);

void thread_fork(p_thread parent, p_thread child, void* stack);

void thread_exit(void);
void thread_load_init_context(p_thread th);

uint32_t thread_get_cpu_time(uint32_t priority);
extern void thread_context_init();
#endif //_PROCESS_H
