//
// Created by zaiyangli on 4/10/16.
//

#include "context.h"
#include "../libc/string.h"


void init_context(context* con){
    memset(con->registers, GPREGISTER_COUNT* sizeof(uint32_t), 0);
    con->programCounter = 0;
}

void context_clone(context* con1, context* cont2){

}