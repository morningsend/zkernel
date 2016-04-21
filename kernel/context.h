//
// Created by zaiyangli on 4/10/16.
//

#ifndef _CONTEXT_H
#define _CONTEXT_H
#include <stddef.h>
#include <stdint.h>
#define GPREGISTER_COUNT 13
typedef struct context_struct {
    uint32_t programState;
    uint32_t programCounter;
    uint32_t registers[GPREGISTER_COUNT];
    uint32_t stackPointer;
    uint32_t linkRegister;

} context;
typedef struct context_struct * p_context;
void init_context(context*);
void context_clone(context* con1, context* cont2);
#endif //_CONTEXT_H
