//
// Created by zaiyangli on 4/21/16.
//

#include "circular_queue.h"

p_circ_queue_node circ_queue_node_new(p_circ_queue_node node, void* object){
    node->object = object;
    node->next = NULL;
}
p_circ_queue_node circ_queue_find_node(p_circ_queue queue, void* object){
    if(queue->top == NULL) return NULL;
    p_circ_queue_node current = queue->top;
    p_circ_queue_node found = NULL;
    do{
        if(current->object == object){
            found = current;
            break;
        }
        current = current->next;
    }while(current != queue->top && current != NULL);

    return found;
}
void circ_queue_enque(p_circ_queue queue, void* object){
    p_circ_queue_node new_node;
    //free nodes keeps track of unused node object that has been allocated previously
    //does not free memory to keep a good performance
    if(queue->nodes.size <= 0) {
        new_node = mem_alloc(queue->alloc, sizeof(circ_queue_node));
        circ_queue_node_new(new_node, object);
    }else {
        new_node = array_pop(&queue->nodes);
    }
    if(queue->top == NULL){
        queue->top = new_node;
        queue->bottom = new_node;
        new_node->next = new_node;
    }
    else {
        queue->bottom->next = new_node;
        new_node->next = queue->top;
        queue->bottom = new_node;
    }
}
void* circ_queue_peek_top(p_circ_queue queue){
    return queue->top->object;
}
void* circ_queue_peek_bottom(p_circ_queue queue){
    return queue->bottom->object;
}
void* circ_queue_deque(p_circ_queue queue){
    void* object = NULL;
    if(queue->top != NULL) {
        object = queue->top->object;
        array_push(&queue->nodes,queue->top);
        if(queue->top->next == queue->top){
            queue->top = NULL;
            queue->bottom = NULL;

        }else {
            queue->top = queue->top->next;
            queue->bottom->next = queue->top;
        }

    }
    return object;
}
void circ_queue_create(p_circ_queue queue, p_allocator alloc){
    queue->alloc = alloc;
    array_new(&queue->nodes, alloc, 16);
    queue->top = NULL;
    queue->bottom = NULL;
}

void circ_queue_destroy(p_circ_queue queue){
    p_circ_queue_node node = queue->top;
    p_circ_queue_node next = node->next;
    if(node != NULL) {
        do
        {
            mem_free(queue->alloc, node);
            node= next;
            next = node->next;
        }while(node != NULL && node!=queue->top);
    }
    array_destroy(&queue->nodes);
    queue->top = NULL;
    queue->bottom = NULL;
}

void circ_queue_for_each(p_circ_queue queue,void(*func)(void*)){
    p_circ_queue_node current = queue->top;
    if(current == NULL) return;
    do{
        func(current->object);
        current = current->next;
    }while(current !=NULL && current != queue->top);
}

void circ_queue_forward(p_circ_queue queue){
    if(queue->top != NULL){
        queue-> top = queue->top->next;
        queue-> bottom = queue->top;
    }
}