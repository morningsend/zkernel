//
// Created by zaiyangli on 4/7/16.
//

#ifndef _PROCESS_H
#define _PROCESS_H


#include <stdint-gcc.h>
#include "context.h"


#define PROCESS_CONTROL_BLOCK_SIZE 32
#define PROCESS_ERROR -1


typedef struct process_struct{
    int pid;
    int exit_code;
    int stack_size;
    int heap_size;
    int parent_pid;
    uint32_t* stack_base_addr;
    uint32_t* heap_base_addr;
    void (*entry_point)(void);
    context exec_ctx;
} process;
void init_pcb();
int createProcess(process* p,void(*task)(),uint32_t* base_address, int stack_size );
void cloneProcess(process* p, uint32_t *stack_base, int stack_size);
process* getProcess(int pid);

void killProcess(process* p);
void pauseProcess(process* p);
void runProcess(process* p);

extern const process process_block[PROCESS_CONTROL_BLOCK_SIZE];

#endif //_PROCESS_H
