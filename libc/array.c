//
// Created by zaiyangli on 4/10/16.
//

#include "array.h"
#include "string.h"
#include <stddef.h>
void array_new(array* arr){
    arr->capacity = ARRAY_CAPACITY;
    arr->size = 0;
    memset(arr->objects, sizeof(void*) * arr->capacity, 0);
}
void array_push(array* arr, void* element){
    CHECK_BOUNDS(arr->size+1, 0,ARRAY_CAPACITY);
    arr->objects[arr->size++] = element;
}
void* array_pop(array* arr){
    if(array_is_empty(arr)) return NULL;
    void* popped = arr->objects[arr->size--];
    return popped;
}
void* array_first_element(array* arr){
    if(arr->size > 0)
    return arr->objects[0];
    else return NULL;
}
void* array_last_elelment(array* arr){
    if(arr->size > 0)
        return arr->objects[arr->size-1];
    else
        return NULL;
}
void array_unshift(array* arr, void *element){
    if(array_is_full(arr)) return ;
    for(int i = arr->size; i > 1; i--){
        arr->objects[i] = arr->objects[i-1];
    }
    arr->objects[0] = element;
    arr->size++;
}
void* array_shift(array* arr){
    if(array_is_empty(arr)) return NULL;
    void* first = array_first_element(arr);
    int end = arr->size -1;
    for(int i = 0; i < end; i++){
        arr->objects[i] = arr->objects[i+1];
    }
    arr->size--;
    return first;
}
void array_insert(array* arr, int index, void* element ){
    CHECK_BOUNDS(index, 0, arr->size);
    if(array_is_full(arr)) return;

    for(int i = arr->size=1; i > index; i ++){
        arr->objects[i] = arr->objects[i-1];
    }
    arr->size ++;
    arr->objects[index] = element;
}
void* array_delete(array* arr, int index){
    CHECK_BOUNDS(index, 0, arr->size -1);
    if(array_is_empty(arr)) return NULL;

    void * deleted = arr->objects[index];

    arr->size --;
    for(int i = index; i < arr->size; i++){
        arr->objects[i] = arr->objects[i+1];
    }
    return deleted;
}

void array_for_each(array* arr, void(*func)(void*)){
    if(array_is_empty(arr)){
        return;
    }
    for( int i = 0; i < arr->size; i++){
        func(arr->objects[i]);
    }
}

int array_is_full(array* arr){
    return arr->size < arr->capacity;
}
int array_is_empty(array* arr){
    return arr->size <= 0;
}