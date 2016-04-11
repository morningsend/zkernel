//
// Created by zaiyangli on 4/11/16.
//

#ifndef _TEST_CASE_H
#define _TEST_CASE_H

#include "../libc/io.h"
#include "assert.h"

#define _TEST_CASE_STR_BUF_SIZE 128

typedef struct test_case_struct {
    int total;
    int pass;
    int fail;
    char description[_TEST_CASE_STR_BUF_SIZE];
}test_case_t;

void test_case_begin(char* description);
void test_case_end();

#endif //_TEST_CASE_H
