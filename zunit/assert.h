//
// Created by zaiyangli on 4/11/16.
//

#ifndef _ASSERT_H
#define _ASSERT_H

#include "../libc/assert.h"
#include "../libc/io.h"
#include "../libc/string.h"
//
// Assertion Failed: Expect #condition to be True\False
// Assertion Failed: Expect #expected and #actual to be equal
#define assert_true(spec, condition) __assert_true( spec,#condition, condition );
#define assert_false(spec, condition) __assert_false( spec, #condition, condition);

#define assert_string_equal(spec, expected, actual) __assert_string_equal(spec, expected, actual);
#define assert_int_equal(spec, expected, actual) __assert_int_equal(spec, expected, actual);
#define assert_float_equal(spec, expected, actual) __assert_float_equal(spec, expected, actual);
#define assert_double_equal(spec, expected, actual) __assert_double_equal(spec, expected, actual);
#define assert_long_equal(spec, expected, actual) __assert_long_equal(spec, exptected, actual);

#define assert_array_equal(spec, expected, actual, expected_size, actual_size, element_size, cmp) \
    __assert_array_equal(spec, expected, actual,expected_size, actual_size,element_size, cmp);
#define assert_obj_equal(spec, expected, actual, cmp) __assert_obj_equal(spec, expected, actual, cmp);


void __assert_true(const char* spec, const char* cond_str, int condition, int line, const char* file );
void __assert_false(const char* spec, const char* cond_str, int condition, int line, const char* file);

void __assert_string_equal(const char* spec, const char* expected,const char* actual, int line, const char* file);
void __assert_int_equal(const char* spec, int expected, int actual, int line, const char* file);
void __assert_float_equal(const char* spec, float expected, float actual, int line, const char* file);
void __assert_double_equal(const char* spec, double expected, double actual, int line, const char* file);
void __assert_long_equal(const char* spec, long expected, long actual, int line, const char* file);

void __assert_array_equal(const char* spec, void* expected,
                          void* actual, int size_expected,
                          int size_actual, int size_element, int(*cmp)(void*, void*), int line, const char* file );
void __assert_obj_equal(const char* spec, void* expected, void* actual, int(*cmp)(void*, void*), int line, const char* file);

#endif //_ASSERT_H
