//
// Created by zaiyangli on 4/2/16.
//

#include "string.h"

#define ASSERT_RETURN_ON_FAIL(cond) if (!( cond ) ) return;

void strcpy(char* destination, char* source){
    while(*source != '\0'){
        *destination = *source;
        destination++;
        source++;
    }
    *destination = '\0';
}

void strncpy(char* destination, char* source, int n){
    while( (n>0) && (*source != '\0')){
        *destination = *source;
        n--;
        source++;
        destination++;
    }
    *destination = '\0';
}

int format_int(int x, char *buf, int n){
    char* begin = buf;
    int negative = x < 0;
    int rem= 0;
    if(n<0){
        return 0;
    }
    x = absi(x);
    n = n - negative - 1;

    do{
        rem = x % 10;
        *buf = '0' + (char)rem;
        n--;
        buf++;
        x = x / 10;
    }while(n > 0 && x > 0);

    if (negative){
        *buf = '-';
        buf++;
    }
    *buf = '\0';

    strrev(begin, buf - begin);
    return buf-begin;
}
int format_float(float x, char *buf, int n){

    return 0;
}

int strlen(const char* str){
    int len = 0;
    while(*str != '\0'){
        len++;
        str++;
    }
    return len;
}


int strcmp(const char* string1, const char* string2) {
    int result = 0;
    while((*string1 != '\0') && (*string2 != '\0')){
        if(*string1 != *string2){
            break;
        }else {
            string1++;
            string2++;
        }
    }
    result = *string1 - *string2;
    return result;
}

void memset(void* buf, int size, int value) {
    ASSERT_RETURN_ON_FAIL(size >= 0);
    int words = size / sizeof(int);
    int i;
    int* ibuf = (int *)buf;
    value |= value << 8 | value << 16 | value << 24;
    for (i = 0; i < words; i++) {
        *ibuf = value;
        ibuf++;
    }
}

void strrev(char *str, int length){
    ASSERT_RETURN_ON_FAIL(length >=0);
    int i;
    int half = length / 2;
    int end = length - 1;
    char c;
    for(i = 0; i < half; i++){
        c = *(str + i);
        *(str + i) = *(str + end - i);
        *(str + end - i) = c;
    }
}
void strrevcpy(char *str, char * buf){
    int i = 0;
    int len = strlen(str);
    for(i = len - 1 ; i >= 0; i--){
        *buf = str[i];
        buf++;
    }
    *buf = '\0';
}

void memcpy(void* destination, void* source, int size){
    char* pdest = (char*) destination;
    char* psource = (char*) source;
    int i = size;
    while(i >0){
        *pdest= *psource;
        pdest++;
        psource++;
        i--;
    }
}

int format_int_to_hex(int n, char* buf, int len){
    return 0;
}

void strcat(char* destination, char* source){
    int len = strlen(destination);
    memcpy(destination+len, source, strlen(source)+1);
}