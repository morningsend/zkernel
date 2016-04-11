//
// Created by zaiyangli on 4/8/16.
//

#include "programs.h"

#if defined(UNIT_TEST)
#include "test/test.h"
#endif

void _start(){
    startupTests();
}
void startupTests(){
#if defined(UNIT_TEST)
    runTests();
#endif
}