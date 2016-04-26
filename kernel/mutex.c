//
// Created by zaiyangli on 4/26/16.
//

#include "mutex.h"


int mutex_try_acquire(uint32_t *lock){
    int lock_status;
    int locked = LOCK_ACTIVE;
    int unlocked = LOCK_FREE;
    asm volatile (
        "mov r1, %[locked]\n"
        "ldrex r2, [r0] \n"
        "cmp r1, r2 \n"
        "moveq %[status], %[unlocked]\n"
        "beq mutex_try_lock_end\n"
        "strexne r2, r1, [r0]\n"
        "cmpne r2,#1\n"
        "moveq %[status], %[unlocked]\n"
        "movne %[status], %[locked]\n"
        "mutex_try_lock_end: nop\n"
        :[status] "=r" (lock_status)
        :[locked] "r" (locked),[unlocked] "r" (unlocked), [addr] "r" (lock)
        : "r0","r1", "r2"
    );
    return lock_status;
}
void mutex_unlock(uint32_t* lock){
    int unlocked = LOCK_FREE;
    asm volatile(
        "mov r1, %[unlocked]\n"
        "dmb \n"
        "str r1,[r0]\n"
        :
        :[addr] "r" (lock), [unlocked] "r" (unlocked)
        :"r0", "r1"
    );
}
void mutex_spinlock(uint32_t* lock){
    while(!mutex_try_acquire(lock)){
        asm volatile("nop");
    }
}
