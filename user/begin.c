//
// Created by zaiyangli on 4/8/16.
//

#include "begin.h"

#if defined(UNIT_TEST) && UNIT_TEST == 1
#include "test/test.h"
#endif

void _start(){
    startupTests();

#if !defined(UNIT_TEST) || UNIT_TEST == 0
    shell_main(0, NULL);
#endif
}
void startupTests(){
#if defined(UNIT_TEST) && UNIT_TEST == 1
    runTests();
#endif
}