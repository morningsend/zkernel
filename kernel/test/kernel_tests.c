//
// Created by zaiyangli on 4/18/16.
//

#include "kernel_tests.h"

void testScheduler(){
    char memory[1024];
    /** set up scheduler with 2 dummy threads,
     * try run scheduling algorithm on it
     * Test the result
     * */
    allocator allocator1;
    init_alloc_with_pool(&allocator1, memory, 1024);

    scheduler_t scheduler;
    init_scheduler(&scheduler, &allocator1);

    p_thread th1 = mem_alloc(&allocator1, sizeof(thread));
    p_thread th2 = mem_alloc(&allocator1, sizeof(thread));

    thread_create(th1, PRIORITY_NORMAL, NULL, 0, NULL);
    thread_create(th2, PRIORITY_NORMAL, NULL, 0, NULL);

    scheduler_schedule_thread(&scheduler, th1);
    scheduler_schedule_thread(&scheduler, th2);

    scheduler_update(&scheduler);


    test_case_begin("Scheduler Priority based Test case");





    test_case_end();
    test_case_summary();
}

void runKernelTests(){
    void testScheduler();
}