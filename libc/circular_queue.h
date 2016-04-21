//
// Created by zaiyangli on 4/21/16.
//

#ifndef _CIRCULAR_QUEUE_H
#define _CIRCULAR_QUEUE_H

#include "allocator.h"
#include "array.h"
typedef struct circ_queue_node circ_queue_node;
typedef struct circ_queue_node* p_circ_queue_node;
typedef struct circ_queue circ_queue;
typedef struct circ_queue* p_circ_queue;


struct circ_queue_node {
    p_circ_queue_node next;
    void* object;
};

struct circ_queue {
    p_circ_queue_node top;
    p_circ_queue_node bottom;
    p_allocator alloc;
    array nodes;
};


p_circ_queue_node circ_queue_find_node(p_circ_queue queue, void* object);
void circ_queue_enque(p_circ_queue queue, void* object);
void* circ_queue_deque(p_circ_queue queue);
void circ_queue_create(p_circ_queue queue, p_allocator allocator);
void circ_queue_destroy(p_circ_queue queue);

void* circ_queue_peek_top(p_circ_queue queue);
void* circ_queue_peek_bottom(p_circ_queue queue);
void circ_queue_forward(p_circ_queue queue);
void circ_queue_for_each(p_circ_queue queue,void(*func)(void*));

#endif //_CIRCULAR_QUEUE_H
