//
// Created by zaiyangli on 4/15/16.
//

#ifndef _SCHEDULE_H
#define _SCHEDULE_H
#include "process.h"

#define PROCESS_READY 4
#define PROCESS_RUNNING 2
#define PROCESS_WAITING 3
#define PROCESS_TERMINATED 0
#define PROCESS_UNALLOCATED -1
#define PROCESS_NEW 1

typedef struct schedule_queue_node_struct schedule_queue_node;

typedef struct schedule_queue_struct {
    schedule_queue_node* root;

}schedule_queue;

struct schedule_queue_node_struct{
    schedule_queue_node* next;
    process* proc;
    int status;
};


void init_scheduler();
void add_new_process_to_queue(process* p);
void remove_process_from_queue(process* p);
void restore_context(process* p);
void save_context(process* p);
void dispatch(process* p);

#endif //_SCHEDULE_H
