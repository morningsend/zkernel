//
// Created by zaiyangli on 4/10/16.
//

#ifndef _ARRAY_H
#define _ARRAY_H

#define ARRAY_CAPACITY 32

#ifndef NULL
#define NULL ((void*)0)
#endif

typedef struct array {
    int size;
    void* objects[ARRAY_CAPACITY];
    int capacity;
}array;

#define CHECK_BOUNDS(index, lower, upper)

void array_push(array* arr, void* element);
void* array_pop(array* arr);
void* array_first_element(array* arr);
void* array_last_elelment(array* arr);
void array_unshift(array* arr, void *element);
void* array_shift(array* arr);
void array_insert(array* arr, int index, void* element );
void* array_delete(array* arr, int index);

void array_for_each(array* arr, void(*func)(void*));
int array_is_full(array* arr);
int array_is_empty(array* arr);
void array_new(array* arr);
#endif //_ARRAY_H
