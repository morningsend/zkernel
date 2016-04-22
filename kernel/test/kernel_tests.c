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

    assert_true("scheduler should have 2 threads", 2 == scheduler.threads.size);

    p_thread t = scheduler_get_current_thread(&scheduler);
    assert_true("first thread is th1", t == th1);

    scheduler_yield_next_thread(&scheduler);
    t = scheduler_get_current_thread(&scheduler);

    assert_true("after yield the 1st thread, scheduler should make th2 current", t == th2);
    t = scheduler_kill_current_thread(&scheduler);
    assert_true("kill the thread will leave thread control block size -1", scheduler.threads.size == 1);
    assert_true("current thread is returned when killed", t == th2);


    t = scheduler_get_current_thread(&scheduler);
    assert_true(("next current thread is th1"), t == th1);
    assert_int_equal("thread id should stay the same", 1, t->id);
    t = scheduler_schedule_next(&scheduler);
    assert_true("scheduling the next thread will use up one cpu time", t->cpu_time = PRIORITY_NORMAL_CPU_TIME-1);
    t = scheduler_yield_next_thread(&scheduler);
    assert_true("next thread should still be t1", t == th1);
    t = scheduler_yield_next_thread(&scheduler);
    assert_true("next thread should still be t1", t == th1);
    test_case_end();
    test_case_summary();
}

void runKernelTests(){
    testScheduler();
    runDiskTest();
}