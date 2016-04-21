//
// Created by zaiyangli on 4/2/16.
//

#include <stddef.h>
#include "test.h"
#include "../../libc/assert.h"
#include "../../libc/array.h"

#if !defined(assert)
#define assert(cond) ""
#endif


void testString(){

    /**
     * strcmp should return 0 when str1 == str2,
     * > 0 when str2 < str1,
     * < 0 when str1 > str2
     */
    int c = strcmp("hello1", "hello");
    assert(c > 0);
    c = strcmp("hello", "hello");
    assert(c == 0);
    c = strcmp("", "\0");
    assert(c==0);
    c = strcmp("a", "bb");
    assert(c < 0);

    /**
     * strlen should return 0 for ""
     * and len(str1) == strlen(str1)
     */
    int len = strlen("");
    assert(len == 0);
    len = strlen("1234");
    assert(len == 4);
    /**
     * str1 == str2 after strcpy(str2, str1)
     */
    char buf[8];
    strcpy(buf, "1234");
    assert(strcmp(buf, "1234")==0);
    strcpy(buf, "");
    assert(strcmp(buf, "")==0);
    assert(buf[strlen(buf)]=='\0');

    /**
     * strncpy(str2, str1, n) copies the first n characters from str1 into str2.
     * If
     */
    strncpy(buf, "12345678", 4);
    assert(strcmp(buf, "1234")==0);
    /**
     * If n is greater the length of str2,
     */
    strncpy(buf, "123", 8);
    assert(strcmp(buf, "123")==0);


    /**
     * memset(buf, size, val) will set each byte of buf to have the value val
     */

    memset(buf, 8, 5);
    for(int i = 0; i < 8; i++ ){
        assert(buf[i]==5);
    }
    /**
     * strrevcpy(str, buf) should store reversed str in buf
     */
    strrevcpy("1234", buf);
    assert(strcmp("4321", buf)==0);
    strrevcpy("", buf);
    assert(strcmp("", buf)==0);

    /***
     * strrev(str, len) reverses a string in place
     */
    /* string of even length should world */
    strcpy(buf, "1234");
    strrev(buf, 4);
    assert(strcmp(buf, "4321")==0);
    /* string of odd length should also work */
    strcpy(buf, "12345");
    strrev(buf, strlen(buf));
    assert(strcmp(buf, "54321")==0);

    /**
     * format_int(n, buf, len) should convert n into string stored in buf of size len.
     */
    int length = 0;
    length = format_int(10, buf, 8);
    assert(length == 2);
    assert(strcmp(buf, "10")==0);

    length = format_int(-10, buf, 8);
    assert(length == 3);
    assert(strcmp(buf, "-10")==0);
}

void testPrintf(){
    /*
     * printf should output strings to the console
     */
    printf("printf should output strings to the console");

    /***
     * printf should output integers to the console
     *
     */
    printf("%d", 12);
    /**
     * printf should print nothing for empty string
     */
    printf("");

    /*
     * print should print both string and integers when having mixed formatting flags
     */
    printf("Hello, %d\n", 123);

    printf("%s, 123", "tom");

    printf("%s, %d ", "hello", 123);

    /**
     * printf should work for any number of arguments
     */
    printf("%d %d %d %d %d %d %d %d %d %d", 1 ,2,3,4,5,6,7,8,9,10);

}
void testPuts(){
    char m[] = "hello world\n";
    int written = puts(m);
    assert_int_equal("puts(str) returns strlen(str)", strlen(m), written);
}
void testExit(){
    exit(10);
}
void testRead(){
    char buf[21];
    int received = 0;
    received = read(stdin, buf, 20);
    buf[received] = '\0';
    puts(buf);
}
void testMath(){
    int c = 32;
    assert(absi(c) == c);

    c = -32;
    assert(absi(c)==(-c));
}
void testAssert(){
    assert(0);
    assert(3!=3);
}

void testTestCase(){
    test_case_begin("Test case Spec");


    assert_int_equal("1 should equal to 1", 1, 1);
    assert_true("1 ==1 should be true", 1==1);
    assert_int_equal("sizeof(inti) should equal 4", 4, (int)sizeof(int));
    test_case_end();
    test_case_summary();
}


void testFreeList(){
#define MEM_SIZE 128
    char mem[MEM_SIZE];
    test_case_begin("Free List Data Structure Test");
    free_list list;
    init_free_list(&list, mem, MEM_SIZE);
    assert_int_equal("list should have size MEM_SIZE", MEM_SIZE, list.memory_size);
    assert_long_equal("list should have memory location equal to mem", ((long) mem) ,((long) list.base_address ));
    assert_true("list head/tail pointer is not null", (list.head != NULL) && (list.tail != NULL));

    void* free_mem = free_list_node_shrink(&list, list.head, 64);
    assert_true("after split, head will have address offset by 64", (list.base_address + 64) == list.head);
    p_free_list_node node = create_free_list_node(free_mem,64);

    free_list_insert_node_head(&list, node);
    assert_false("memory after shrink is not null", free_mem == NULL);
    assert_true("after inserting new node, head should point to new node", list.head == node);
    assert_int_equal("block size of new node should equal to size after split", 64, node->block_size);

    p_free_list_node found = free_list_find_block_of_size(&list, 20+sizeof(free_list_node));
    assert_true("free_list will contain node of block size 20+sizeof(free_list_node)", list.head == found);

    free_list_node_combine(&list, list.head, list.head->next);
    assert_true("free_list combine nodes will create node with combined size", list.head->block_size == MEM_SIZE);
    assert_true("after combine nodes, head will have address equal to mem", (void*)list.head ==(void*) mem);

    test_case_end();
    test_case_summary();
}

void testAllocator(){
#define MEMSIZE2 256
    char memory[MEMSIZE2];
    allocator alloc;
    init_alloc_with_pool(&alloc, memory, MEMSIZE2);
    test_case_begin("Testing memory allocation and deallocation");

    int* n = (int*) mem_alloc(&alloc, sizeof(int));
    assert_false("allocating an integer returns address Not NULL", n ==NULL);
    int* m = (int*) mem_alloc(&alloc, sizeof(int));
    assert_false("allocating an integer returns address Not NULL", m ==NULL);
    assert_false("m and n have different address", m ==n);
    *m = 10;
    p_alloc_entry entry = get_mem_alloc_entry((void*) n);
    assert_int_equal("entry for n has size 12", sizeof(free_list_node), entry->block_size);
    entry = get_mem_alloc_entry((void*) m);
    assert_int_equal("entry for m has size 12", sizeof(free_list_node), entry->block_size);

    mem_free(&alloc, m);
    mem_free(&alloc, n);
    assert_false("after deallocation, m is not 10", (int)m == 10);
    test_case_end();
    test_case_summary();
}
void testStressAllocator(){
    char memory[MEMSIZE2];
    allocator alloc;
    init_alloc_with_pool(&alloc, memory, MEMSIZE2);
    test_case_begin("Allocator Stress Testing");
    char* str1 = (char*) mem_alloc(&alloc, 20);
    strcpy(str1, "hello world");
    char* str2 = (char*) mem_alloc(&alloc, 20);
    strcpy(str2, "good day");
    char* str3 = (char*) mem_alloc(&alloc, 60);
    str3[0] = '\0';
    strcpy(str3, str1);
    strcat(str3, str2);
    assert_true("str3 should equal to hello worldgood day", strcmp(str3, "hello worldgood day")==0);
    test_case_end();
    test_case_summary();
}
void testArray(){
    char memory[256];
    int numbers[17] = {1,2,3,4,5,6,7,8,9,0,11,12,13,14,15,16,17};
    allocator alloc;
    init_alloc_with_pool(&alloc, memory, MEMSIZE2);
    array arr;
    array_new(&arr, &alloc, 16);
    test_case_begin("Dynamic array test cases");

    assert_int_equal("new array should have size 0", 0, arr.size );
    assert_int_equal("new array should have capacity 16", 16, arr.capacity);

    array_push(&arr, &numbers[0]);
    assert_int_equal("array should have size 1 after pushing", 1, arr.size );
    assert_int_equal("array capacity should be the same as before", 16, arr.capacity);

    int* p = (int*) array_pop(&arr);
    assert_true("popping array should get back the same value", *p == numbers[0]);
    assert_true("popping should decrease array size by 1", arr.size == 0);


    for(int i = 0; i < 17; i++){
        array_push(&arr, &numbers[i]);
    }

    assert_true("array should grow after exceeding capacity", arr.capacity == 16*ARRAY_GROWTH_FACTOR);
    int n = 100;
    array_insert(&arr, 2, &n);
    assert_int_equal("array insert at index", 100, *(int*)array_get(&arr, 2));

    array_delete(&arr, 2);
    assert_false("array delete index removes the element", array_get(&arr, 2) == &n);

    test_case_end();
    test_case_summary();
}
void print_number(void* p_int){
    printf("%d\n", *(int*)p_int);
}
void testCircQueue(){
    char memory[256];
    allocator al;
    init_alloc_with_pool(&al, memory, 256);
    circ_queue queue;
    circ_queue_create(&queue, &al);

    int a=5,b=20,c=10;

    test_case_begin("Circular Queue Tests");

    assert_true("new queue have NULL top and bottom pointers",
                queue.top == NULL && queue.bottom == NULL);

    circ_queue_enque(&queue, &a);

    assert_true("both top and bottom will point to same node if 1 element in queue",
                queue.top == queue.bottom);
    assert_true("node's next pointer will point to itself", queue.top->next == queue.top);
    circ_queue_enque(&queue, &b);
    circ_queue_enque(&queue, &c);

    assert_int_equal("top of the queue is a", a, *(int*)queue.top->object);

    assert_int_equal("bottom of the queue is c", c, *(int*)queue.bottom->object);
    int n = *(int*)circ_queue_deque(&queue);
    assert_int_equal("deque will return first object in queue", a, n);
    n = *(int*) circ_queue_deque(&queue);

    assert_int_equal("dequeue second time will return b", b, n);

    assert_int_equal("backing array should have size equal to number of nodes",2, queue.nodes.size);
    circ_queue_enque(&queue, &a);
    assert_int_equal("mem cache array should decrease by 1 when create a new node,", 1, queue.nodes.size);

    circ_queue_for_each(&queue, print_number);

    test_case_end();
    test_case_summary();
}
void runTests(){

    testString();
    testPrintf();
    testMath();
    testAssert();
    testPuts();
    testTestCase();
    testFreeList();
    testAllocator();
    testStressAllocator();
    testArray();
    testCircQueue();
    exit(0);
}
