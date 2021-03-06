//
// Created by zaiyangli on 4/10/16.
//

#include "array.h"
#include "string.h"
#include <stddef.h>
#define ELEMENT_SIZE sizeof(void*)
static void array_expand(array* arr){
    uint32_t new_capacity = arr->capacity * ARRAY_GROWTH_FACTOR;
    void* memory = mem_alloc(arr->alloc, ELEMENT_SIZE * new_capacity);
    if(memory != NULL){
        arr->capacity = new_capacity;
        memset(memory, ELEMENT_SIZE*arr->capacity,0);
        memcpy(memory, arr->objects, ELEMENT_SIZE * arr->size);
        mem_free(arr->alloc, arr->objects);
        arr->objects = memory;
    }
}

void array_new(array* arr, allocator* alloc, uint32_t init_capacity){
    init_capacity = (init_capacity % 2 )== 0? init_capacity: (init_capacity + 1);
    arr->capacity = init_capacity < ARRAY_DEFAULT_CAPACITY ? ARRAY_DEFAULT_CAPACITY : init_capacity;
    arr->size = 0;
    arr->objects = mem_alloc(alloc, sizeof(void*) * arr->capacity);
    arr->alloc = alloc;
    memset(arr->objects, sizeof(void*) * arr->capacity, 0);
}
void array_push(array* arr, void* element){
    if(array_is_full(arr)) array_expand(arr);
    arr->objects[arr->size++] = element;
}
void* array_pop(array* arr){
    if(array_is_empty(arr)) return NULL;
    void* popped = arr->objects[--arr->size];
    return popped;
}
void* array_first_element(array* arr){
    if(arr->size > 0)
    return arr->objects[0];
    else return NULL;
}
void* array_last_elelment(array* arr){
    if(!array_is_empty(arr))
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
    if(array_is_full(arr)) array_expand(arr);

    for(int i =(int) arr->size - 1; i > index; i --){
        arr->objects[i] = arr->objects[i-1];
    }
    arr->size++;
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
void* array_delete_element(array* arr, void* object){
    int index = array_find_element(arr, object);
    if(index > -1){
        return array_delete(arr, index);
    }
    return NULL;
}
int array_find_element(array* arr, void* object){
    int index = -1;
    for(int i = 0; i < arr->size; i ++){
        if(arr->objects[i] == object){
            index = i;
            break;

        }
    }
    return index;
}
void array_for_each(array* arr, void(*func)(void*)){
    if(array_is_empty(arr)){
        return;
    }
    for( int i = 0; i < arr->size; i++){
        func(arr->objects[i]);
    }
}

void* array_get(array* arr, int index){
    if( index < 0 || index >= arr->size) return NULL;
    return arr->objects[index];
}
void array_set(array* arr, int index, void* element){
    if(index < 0 || index >= arr->size ) return;
    arr->objects[index] = element;
}

int array_is_full(array* arr){
    return arr->size >= arr->capacity;
}
int array_is_empty(array* arr){
    return arr->size <= 0;
}
void array_destroy(array* arr){
    mem_free(arr->alloc, arr->objects);
    arr->objects = NULL;
    arr->capacity = 0;
    arr->size = 0;
}