//
// Created by zaiyangli on 4/15/16.
//

#ifndef _SCHEDULE_H
#define _SCHEDULE_H
#include "thread.h"
#include "../libc/array.h"
#include "../libc/allocator.h"
#include "kernel.h"

typedef struct scheduler_struct scheduler_t;
struct scheduler_struct {
    allocator* mem_allocator;
    array threads;
    int current_executing;
};

void init_scheduler(scheduler_t* scheduler, allocator *allocator1);
void scheduler_schedule_thread(scheduler_t* thread_scheduler, p_thread th);
p_thread scheduler_find_thread(scheduler_t* scheduler, uint32_t tid);
p_thread scheduler_next_thread(scheduler_t* scheduler);
p_thread scheduler_get_current_thread(scheduler_t* scheduler);
void scheduler_kill_current_thread(scheduler_t*);
void scheduler_update(scheduler_t* sch);
#endif //_SCHEDULE_H
