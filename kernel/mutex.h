//
// Created by zaiyangli on 4/26/16.
//

#ifndef _MUTEX_H
#define _MUTEX_H

#include <stdint-gcc.h>

#define LOCK_FREE 0
#define LOCK_ACTIVE 1

void mutex_lock(uint32_t* lock);
void mutex_unlock(uint32_t* lock);
void mutex_spinlock(uint32_t* lock);


#endif //_MUTEX_H
