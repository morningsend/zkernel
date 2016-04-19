//
// Created by zaiyangli on 4/15/16.
//

#include "timer.h"
#include "SP804.h"

#define FREE 0
#define USE 1
static int timer_usage[TIMER_COUNT] = { FREE,FREE,FREE,FREE,FREE,FREE,FREE,FREE};

static volatile SP804_t* _get_timer(int id){
    if(id < 0 || id >= TIMER_COUNT){
        return NULL;
    }
    int index = id >>1;
    int which = id & 0x01;
    volatile void* address = TIMERS[index];
    address += which * (0x20);
    return (volatile SP804_t*) address;
}

int request_timer_device(){
    int free_device = -1;
    for(int i = 0; i < 8; i++){
        if ( timer_usage[i] == FREE){
            timer_usage[i] = USE;
            free_device = i;
            break;
        }
    }
    reset_timer(free_device);
    return free_device;
}

void release_timer_device(int i){
    if(timer_usage[i] == USE){
        timer_usage[i] = FREE;
        reset_timer(i);
    }
}
void reset_timer(int i){
    SP804_t* timer = _get_timer(i);
    timer->Timer1BGLoad = 0;
    timer->Timer1Ctrl = SP804_TIMER_INTERRUPT_ENABLE_BIT;
    timer->Timer1Load = 0;
    timer->Timer1IntClr = 0;
}

void timer_set_ticks(int id, uint32_t ticks){
    SP804_t* timer = _get_timer(id);
    if(timer != NULL){
        timer->Timer1Load = ticks;
    }
}
void timer_set_periodic_mode(int id){
    SP804_t* timer = _get_timer(id);
    if(timer != NULL){
        timer->Timer1Ctrl |= SP804_TIMER_MODE_BIT;
    }
}
void timer_set_free_running_mode(int id){
    SP804_t* timer = _get_timer(id);
    if(timer != NULL){
        timer->Timer1Ctrl &= ~SP804_TIMER_MODE_BIT;
    }
}
void timer_set_prescale(int id, int factor){

}
void timer_set_size_32bit(int id){
    SP804_t* timer = _get_timer(id);
    if(timer != NULL){
        timer->Timer1Ctrl |= SP804_TIMER_SIZE_BIT;
    }
}
void timer_set_size_16bit(int id){
    SP804_t* timer = _get_timer(id);
    if(timer != NULL){
        timer->Timer1Ctrl &= ~SP804_TIMER_SIZE_BIT;
    }
}
void timer_set_wrapping(int id){
    SP804_t* timer = _get_timer(id);
    if(timer != NULL){
        timer->Timer1Ctrl &= ~SP804_TIMER_ONE_SHOT;
    }
}
void timer_set_one_shot(int id){
    SP804_t* timer = _get_timer(id);
    if(timer != NULL){
        timer->Timer1Ctrl |= SP804_TIMER_ONE_SHOT;
    }
}
void timer_clear_interrupt(int id){
    volatile SP804_t* timer = _get_timer(id);
    if(timer != NULL) {
        timer->Timer1IntClr = 0;
    }
}
void timer_set_ticks_background(int id, uint32_t  ticks){
    volatile SP804_t* timer = _get_timer(id);
    if(timer != NULL) {
        timer->Timer1BGLoad = ticks;
    }
}

void timer_enable(int id){
    SP804_t* timer = _get_timer(id);
    if(timer != NULL){
        timer->Timer1Ctrl |=  SP804_TIMER_ENABLE_BIT;
    }
}
void timer_disable(int id){
    SP804_t* timer = _get_timer(id);
    if(timer != NULL){
        timer->Timer1Ctrl &=  ~SP804_TIMER_ENABLE_BIT;
    }
}
void timer_enable_interrupt(int id){
    SP804_t* timer = _get_timer(id);
    if(timer != NULL){
        timer->Timer1Ctrl |=  SP804_TIMER_INTERRUPT_ENABLE_BIT;
    }
}
void timer_disable_interrupt(int id){
    SP804_t* timer = _get_timer(id);
    if(timer != NULL){
        timer->Timer1Ctrl &=  ~SP804_TIMER_INTERRUPT_ENABLE_BIT;
    }
}