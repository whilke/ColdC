/*
// Full copyright information is available in the file ../doc/CREDITS
//
// VEIL packets buffer manipulation module
//
// look at http://www.cold.org/VEIL/ for more information.
//
*/

#define NATIVE_MODULE "$test"

#define TEST_C

#include "test.h"

module_t test_module = {YES, init_test, YES, uninit_test};

#define HEADER_SIZE    5

void init_test(Int argc, char ** argv) {
    pabort_id = ident_get("abort");
    pclose_id = ident_get("close");
    popen_id  = ident_get("open");
}

void uninit_test(void) {
    ident_discard(pabort_id);
    ident_discard(pclose_id);
    ident_discard(popen_id);
}

NATIVE_METHOD(test1){}

NATIVE_METHOD(test2){}

NATIVE_METHOD(test3){}

NATIVE_METHOD(test4){}

NATIVE_METHOD(test5){}

NATIVE_METHOD(test6){}

NATIVE_METHOD(test7){}

NATIVE_METHOD(test8){}

NATIVE_METHOD(test9){}
