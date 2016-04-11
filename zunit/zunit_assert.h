//
// Created by zaiyangli on 4/11/16.
//

#ifndef _ASSERT_H
#define _ASSERT_H


#include "../libc/io.h"
#include "../libc/string.h"
//
// Assertion Failed: Expect #condition to be True\False
// Assertion Failed: Expect #expected and #actual to be equal
#define assert_true(spec, condition) __assert_true( spec,#condition, condition, __LINE__, __FILE__ );
#define assert_false(spec, condition) __assert_false( spec, #condition, condition, __LINE__, __FILE__ );

#define assert_string_equal(spec, expected, actual) __assert_string_equal(spec, expected, actual, __LINE__, __FILE__ );
#define assert_int_equal(spec, expected, actual) __assert_int_equal(spec, expected, actual, __LINE__, __FILE__ );
#define assert_float_equal(spec, expected, actual) __assert_float_equal(spec, expected, actual, __LINE__, __FILE__ );
#define assert_double_equal(spec, expected, actual) __assert_double_equal(spec, expected, actual, __LINE__, __FILE__ );
#define assert_long_equal(spec, expected, actual) __assert_long_equal(spec, exptected, actual, __LINE__, __FILE__ );

#define assert_array_equal(spec, expected, actual, expected_size, actual_size, element_size, cmp) \
    __assert_array_equal(spec, expected, actual,expected_size, actual_size,element_size, cmp, __LINE__, __FILE__ );
#define assert_obj_equal(spec, expected, actual, cmp) __assert_obj_equal(spec, expected, actual, cmp, __LINE__, __FILE__ );

extern void test_case_assert_fail();
extern void test_case_assert_pass();

#ifdef _TEST_CASE_ASSERT_LINK
#define _TEST_CASE_REPORT_RESULT(pass) if(pass){test_case_assert_pass();}else{test_case_assert_fail();}
#else
#define _TEST_CASE_REPORT_RESULT(condition)
#endif


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
