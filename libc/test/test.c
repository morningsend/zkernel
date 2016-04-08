//
// Created by zaiyangli on 4/2/16.
//

#include "test.h"



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
    /**
     * printf should print formatted string
     */
    /**
     * printf should print integer with %d flag.
     */
    initialize_buffer(&stdout_buffer, 1, 1);
    printf("%d", 10);
    assert(strcmp(stdout_buffer.buf, "10")==0);
    /**
     * printf should print string with %s flag.
     */
    initialize_buffer(&stdout_buffer, 1, 1);
    printf("%s", "hello world");
    assert(strcmp(stdout_buffer.buf, "hello world")==0);

    /***
     * printf should print a character with %c flag
     */
    initialize_buffer(&stdout_buffer,1, 1);
    printf("%c", 'a');
    assert(strcmp(stdout_buffer.buf, "a")==0);
    /**
     * printf should print unformatted text
     */
    initialize_buffer(&stdout_buffer, 1, 1);
    printf("hello world");
    assert(strcmp(stdout_buffer.buf, "hello world")==0);

    /**
     * printf should print unformatted text with formatted data
     */
    initialize_buffer(&stdout_buffer, 1, 1);
    printf("a=%d;", 10);
    assert(strcmp(stdout_buffer.buf, "a=10;")==0);

    /**
     * printf should work with any number of arguments
     */
    initialize_buffer(&stdout_buffer, 1, 1);
    printf("%d,%d,%d,%d,%d,%d,%d,%d,%d",1,2,3,4,5,6,7,8,9);
    assert(strcmp(stdout_buffer.buf, "1,2,3,4,5,6,7,8,9")==0);
}

void runTests(){
    testString();
    testPrintf();
}
