//
// Created by zaiyangli on 4/18/16.
//

#include "free_list.h"



void init_free_list(p_free_list list, void *memory, uint32_t size){
    p_free_list_node root_block = create_free_list_node(memory, size);
    free_list_init_with_node(list, root_block);
    list->base_address = memory;
    list->memory_size = size;
}
p_free_list free_list_init_with_node(p_free_list list, p_free_list_node node){
    list->head = node;
    list->tail = node;
    node->next = NULL;
    node->previous = NULL;
    return list;
}
p_free_list_node create_free_list_node(void* memory, uint32_t size){
    p_free_list_node newNode = NULL;
    if(size < sizeof(free_list_node)){

    }else {
        newNode = (p_free_list_node) memory;
        newNode->block_size = size;
        newNode->next = NULL;
        newNode->previous = NULL;
    }
    return newNode;
}

void free_list_node_link(p_free_list_node first, p_free_list_node second){
    first->next = second;
    second->previous = first;
}

p_free_list free_list_insert_node_head(p_free_list list, p_free_list_node node){
    if(list->head == NULL){
        free_list_init_with_node(list, node);
    }else {
        free_list_node_link(node, list->head);
        list->head = node;
        node->previous = NULL;
    }
    return list;
}
p_free_list free_list_insert_node_tail(p_free_list list, p_free_list_node node) {
    if(list->tail == NULL){
        free_list_init_with_node(list, node);
    }else {
        free_list_node_link(list->tail, node);
        node->next = NULL;
    }
    return list;
}
void free_list_insert_before(p_free_list_node target, p_free_list_node new_node){
    if(target->previous == NULL){
        free_list_node_link(new_node, target);
    }else {
        p_free_list_node beforeTarget = target->previous;
        free_list_node_link(beforeTarget, new_node);
        free_list_node_link(new_node, target);
    }
}
void free_list_insert_after(p_free_list_node target, p_free_list_node new_node){
    if(target->next == NULL){
        free_list_node_link(target, new_node);
    }else {
        p_free_list_node afterTarget = target->next;
        free_list_node_link(target, new_node);
        free_list_node_link(new_node, afterTarget);
    }
}
void* free_list_node_shrink(p_free_list list, p_free_list_node node, uint32_t new_size){
    free_list_node temp = *node;

    void* start = node;
    int offset = (int) temp.block_size - (int) new_size;
    node = ((void*)node) + offset;
    *node = temp;
    node->block_size = new_size;
    if(start == list->head){
        list->head = node;
    }
    if(start == list->tail){
        list->tail = node;
    }
    return start;
}
void free_list_node_combine(p_free_list list, p_free_list_node node1, p_free_list_node node2){
    int distance = (int) (((void*) node2) - ((void*)node1));
    if(distance == node1->block_size){
        node1->block_size += node2->block_size;
        node1->next = node2->next;
        node1->previous = node2->previous;
        if(list->head == node2){
            list->head = node1;
            node1->previous = NULL;
        }
        if(list->tail==node2){
            list->tail = node1;
            node1->next = NULL;
        }
    }
}

void free_list_node_unlink(p_free_list_node first , p_free_list_node second){
    first->next = NULL;
    second->previous = NULL;
}

p_free_list_node free_list_delete(p_free_list list, p_free_list_node node){
    if(list->head == NULL) return NULL;

    if(node == list->head || node-> previous == NULL){

        node->next = NULL;
        node->previous = NULL;

    }else if( (node == list->tail) || (node->next == NULL ) ){
        node->previous = NULL;
        node->next = NULL;
    }else {
        p_free_list_node prev = node->previous;
        p_free_list_node next = node->next;
        free_list_node_link(prev, next);
        node->next = NULL;
        node->previous = NULL;
    }
    return node;
}

p_free_list_node free_list_find_block_of_size(p_free_list list, uint32_t size){
    p_free_list_node current = list->head;
    while(current != NULL){
        if(current->block_size > size)
            break;
        current = current->next;
    }
    return current;
}

void free_list_insert_node(p_free_list list, p_free_list_node node){
    p_free_list_node current = list->head;
    if(node < list->head){
        free_list_insert_node_head(list, node);
        free_list_node_combine(list, list->head, node);
    }else if(node > list->tail){
        free_list_insert_node_tail(list, node);
        free_list_node_combine(list, list->tail, node);
    }else {
        for (; current != NULL; current = current->next) {
            if (node < current){
                free_list_insert_before(current, node);
                free_list_node_combine(list, current, node);
            }
        }
    }
}