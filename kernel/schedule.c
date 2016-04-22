//
// Created by zaiyangli on 4/15/16.
//

#include "schedule.h"


void init_scheduler(scheduler_t* scheduler, allocator *allocator1){
    scheduler->mem_allocator = allocator1;
    array_new(&scheduler->threads, scheduler->mem_allocator, 16);
    circ_queue_create(&scheduler->thread_queue, allocator1);
}

void scheduler_schedule_thread(scheduler_t* sched, p_thread th){
    array_push(&sched->threads, th);
    if(th->state == THREAD_STATE_READY || th->state == THREAD_STATE_NEW){
        circ_queue_enque(&sched->thread_queue,th);
    }
}
void scheduler_update(scheduler_t* sch){
    /*do nothing for now */;
}
p_thread scheduler_schedule_next(scheduler_t *scheduler){
    p_thread th = scheduler_get_current_thread(scheduler);
    if(th->cpu_time > 0)
        th->cpu_time--;
    else {
        th->cpu_time = thread_get_cpu_time(th->priority);
        circ_queue_forward(&scheduler->thread_queue);
        th = (p_thread) scheduler->thread_queue.top->object;
    }
    return th;
}
p_thread scheduler_yield_next_thread(scheduler_t* sched){
    p_thread th;
    circ_queue_forward(&sched->thread_queue);
    th = (p_thread) sched->thread_queue.top->object;
    return th;
}
p_thread scheduler_get_current_thread(scheduler_t* sched){
    return sched->thread_queue.top->object;
}
p_thread scheduler_kill_current_thread(scheduler_t* scheduler){
    p_thread th = circ_queue_deque(&scheduler->thread_queue);
    array_delete_element(&scheduler->threads, th);
    return th;
}

void scheduler_destroy(scheduler_t* sched){
    array_destroy(&sched->threads);
    circ_queue_destroy(&sched->thread_queue);
}