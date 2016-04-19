//
// Created by zaiyangli on 4/7/16.
//

#include "process.h"

#define CHECK_BOUNDS(n, lower, upper)

static void init_pcb_entry(process* p);
static int find_free_pcb_entry(process* pcb);
const process process_block[PROCESS_CONTROL_BLOCK_SIZE];

void init_pcb(){
    for(int i = 0 ; i < PROCESS_CONTROL_BLOCK_SIZE; i++){
        init_pcb_entry(&process_block[i]);
    }
}
static int find_free_pcb_entry(process pcb[]){
    for(int i = 0 ; i < PROCESS_CONTROL_BLOCK_SIZE; i++){
        process* proc = &pcb[i];
    }
    return PROCESS_ERROR;
}
static void init_pcb_entry(process* p){
    p->entry_point = NULL;
    p->pid = -1;
    p->parent_pid = -1;
    p->exit_code = 0;
    p->heap_base_addr = NULL;
    p->stack_base_addr = NULL;
    p->heap_size = 0;
    p->stack_size = 0;
}
static uint32_t process_count = 0;



int createProcess(process *task, void (*stack_base)(), uint32_t *stack_size, int i){
    int pid = find_free_pcb_entry(process_block);
    if(pid < 0){
        return PROCESS_ERROR;
    }
    process* proc = getProcess(pid);
    init_pcb_entry(proc);
    proc->entry_point = task;
    proc->stack_base_addr = stack_base;
    proc->stack_size = stack_size;

    return pid;
}

void cloneProcess(process *pid, uint32_t *stack_base, int stack_size){

}

process* getProcess(int pid){
    return &process_block[pid];
}

void killProcess(process *pid){

}
void pauseProcess(process *pid){

}
void runProcess(process *pid){
    process* proc = getProcess(pid);

}