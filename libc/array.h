//
// Created by zaiyangli on 4/10/16.
//

#ifndef _ARRAY_H
#define _ARRAY_H

#include "allocator.h"

#ifndef NULL
#define NULL ((void*)0)
#endif


#define ARRAY_GROWTH_FACTOR 2
#define ARRAY_DEFAULT_CAPACITY 16
typedef struct array {
    uint32_t size;
    uint32_t capacity;
    allocator* alloc;
    void** objects;

}array;

#define CHECK_BOUNDS(index, lower, upper)


void array_push(array* arr, void* element);
void* array_pop(array* arr);

void* array_get(array* arr, int index);
void* array_first_element(array* arr);
void* array_last_elelment(array* arr);

void array_set(array* arr, int index, void* element);
void array_unshift(array* arr, void *element);
void* array_shift(array* arr);
void array_insert(array* arr, int index, void* element );
void* array_delete(array* arr, int index);

void array_for_each(array* arr, void(*func)(void*));
int array_is_full(array* arr);
int array_is_empty(array* arr);

void array_new(array* arr, allocator* alloc, uint32_t init_capacity);

#endif //_ARRAY_H
