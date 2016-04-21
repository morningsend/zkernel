//
// Created by zaiyangli on 4/15/16.
//

#include "schedule.h"

static scheduler_t scheduler;

void init_scheduler(scheduler_t* scheduler, allocator *allocator1){
    scheduler->mem_allocator = allocator1;
    array_new(&scheduler->threads, scheduler->mem_allocator, 16);
    scheduler->current_executing = -1;
}

void scheduler_schedule_thread(scheduler_t* thread_scheduler, p_thread th){
    array_push(&thread_scheduler->threads, th);
}
p_thread scheduler_find_thread(scheduler_t* scheduler, uint32_t tid){
    p_thread th = NULL;
    for(int i = 0; i < scheduler->threads.size; i++){
        th = (p_thread) scheduler->threads.objects[i];
        if (th->id == tid){
            return th;
        }
    }
    return NULL;
}
void scheduler_update(scheduler_t* sch){
    /*do nothing for now */;
}
p_thread scheduler_next_thread(scheduler_t* scheduler){
    p_thread th = NULL;
    if(scheduler->threads.size > 0)
        th =scheduler->threads.objects[0];
    return th;
}
p_thread scheduler_get_current_thread(scheduler_t* scheduler){
    p_thread th = NULL;
    if(scheduler->threads.size > 0)
        th =scheduler->threads.objects[0];
    return th;
}
p_thread scheduler_kill_current_thread(scheduler_t* scheduler){
    p_thread th = scheduler_get_current_thread(scheduler);
    array_delete_element(&scheduler->threads, th);
    return th;
}
void scheduler_update(scheduler_t* sch);