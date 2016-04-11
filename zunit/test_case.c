//
// Created by zaiyangli on 4/11/16.
//

#include "test_case.h"
static void _print_test_case_summary(test_case_t* info);
static void test_runner_init(char* description);

static test_case_t current_test_case = {
        .description = "",
        .fail = 0,
        .pass = 0,
        .total = 0
};

static void test_runner_init(char* description){
    strncpy(current_test_case.description, description, _TEST_CASE_STR_BUF_SIZE);
    current_test_case.fail = 0;
    current_test_case.pass = 0;
    current_test_case.total = 0;
}
void test_case_begin(char* description){
    test_runner_init(description);
}
void test_case_end(){

}
void test_case_summary(){
    _print_test_case_summary(&current_test_case);
}
static void _print_test_case_summary(test_case_t* info){
    printf("Test case summary: %s\n", info->description);
    printf("Total: %d| %d passed/ %d failed\n", info->total, info->pass, info->fail);
}

void test_case_assert_fail(){
    current_test_case.fail++;
    current_test_case.total++;
}
void test_case_assert_pass(){
    current_test_case.pass++;
    current_test_case.total++;
}