//
// Created by zaiyangli on 4/15/16.
//

#ifndef _SCHEDULE_H
#define _SCHEDULE_H
#include "thread.h"

void init_scheduler();
void scheduler_dispatch_thread(p_thread th);
void scheduler_suspend_thread(p_thread th);
void scheduler_kill_thread(p_thread th);
p_thread get_current_thread();
#endif //_SCHEDULE_H
