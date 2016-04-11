//
// Created by zaiyangli on 4/7/16.
//

#ifndef _PROCESS_H
#define _PROCESS_H


#include <stdint-gcc.h>
#include "context.h"
#define PROCESS_NEW 0
#define PROCESS_RUNNING 1
#define PROCESS_WAITING 2
#define PROCESS_TERMINATED -1

struct process_struct{
    int pid;
    int exit_code;
    int status;
    int stack_size;
    uint32_t base_addr;
} process_entry;

int createProcess(void(*task)());
void killProcess(int pid);
void pauseProcess(int pid);
void runProcess(int pid);
...................
..................................................................................................................................................






























































...................................................

#endif //_PROCESS_H
