//
// Created by zaiyangli on 4/15/16.
//

#ifndef _TIMER_H
#define _TIMER_H
#define TIMER_COUNT 8
#include "SP804.h"

void timer_enable(int id);
void timer_disable(int id);
void timer_enable_interrupt(int id);
void timer_disable_interrupt(int id);
int request_timer_device();
void reset_timer(int id);
void release_timer_device(int id);
void timer_set_ticks(int id, uint32_t  ticks);
void timer_set_periodic_mode(int id);
void timer_set_free_running_mode(int id);
void timer_set_prescale(int id, int factor);
void timer_set_size_32bit(int id);
void timer_set_size_16bit(int id);
void timer_set_wrapping(int id);
void timer_set_one_shot(int id);
void timer_clear_interrupt(int id);
void timer_set_ticks_background(int id, uint32_t ticks);

#endif //_TIMER_H
