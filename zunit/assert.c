//
// Created by zaiyangli on 4/11/16.
//

#include "assert.h"

static const char fail_message_boolean[] = "%s | Failed: Expect %s to be %s\n\t on line: %d, file: %s\n";
static const char fail_message_equal[] = "%s | Failed: Expect %s to equal %s\n\t on line: %d, file: %s\n";
static const char fail_message_object_equal[] = "%s | Failed: Expect objects to be equal\n\t on line: %d, file: %s\n";
static const char fail_message_array_equal[] = "%s | Failed: Expect arrays to be equal\n\t on line: %d, file: %s\n";

void __assert_true(const char* spec, const char* cond_str, int condition, int line, const char* file){
    if(!condition){
        printf(fail_message_boolean, spec, cond_str, "true", line, file);
    }
}
void __assert_false(const char* spec, const char* cond_str, int condition, int line, const char* file){
    if(condition){
        printf(fail_message_boolean, spec, cond_str, "false", line, file);
    }
}

void __assert_string_equal(const char* spec, const char* expected,const char* actual, int line, const char* file){
    int relation = strcmp(expected, actual);
    if(relation != 0){
        printf(fail_message_equal, spec, expected, actual, line, file);
    }
}
void __assert_int_equal(const char* spec, int expected, int actual, int line, const char* file){
    char buf1[31];
    char buf2[31];
    if(expected!=actual){
        format_int(expected, buf1, 31);
        format_int(actual, buf2, 31);
        printf(fail_message_equal, spec, buf1, buf2, line, file);
    }
}
void __assert_float_equal(const char* spec, float expected, float actual, int line, const char* file){
    char buf1[31];
    char buf2[31];
    if(expected!=actual){
        format_float(expected, buf1, 31);
        format_float(actual, buf2, 31);
        printf(fail_message_equal, spec, buf1, buf2, line, file);
    }
}
void __assert_double_equal(const char* spec, double expected, double actual, int line, const char* file){

}
void __assert_long_equal(const char* spec, long expected, long actual, int line, const char* file){

}

void __assert_array_equal(const char* spec, void* expected,
                          void* actual, int size_expected,
                          int size_actual, int size_element, int(*cmp)(void*, void*), int line, const char* file ){
    int equal = 1;
    int relation = 0;
    if(size_expected!=size_actual){
        equal = 0;
    }else{

        for(int i = 0; i < size_actual; i++){
            relation = cmp(expected, actual);
            if(relation !=0){
                equal = 0;
                break;
            }
            actual += size_element;
            expected += size_element;
        }
    }
    if(!equal){
        printf(fail_message_array_equal, spec, line, file);
    }
}
void __assert_obj_equal(const char* spec, void* expected, void* actual, int(*cmp)(void*, void*), int line, const char* file){
    int relation = cmp(expected, actual);
    if(relation != 0){
        printf(fail_message_object_equal, spec, line, file);
    }
}
