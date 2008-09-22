#ifndef _test_h_
#define _test_h_

#include "defs.h"
#include "cdc_pcode.h"

#ifdef TEST_C
Ident pabort_id, pclose_id, popen_id;
#else
extern Ident pabort_id, pclose_id, popen_id;
#endif

void init_test(Int argc, char ** argv);
void uninit_test(void);

#ifndef _test_
extern module_t test_module;
#endif

extern NATIVE_METHOD(test1);
extern NATIVE_METHOD(test2);
extern NATIVE_METHOD(test3);
extern NATIVE_METHOD(test4);
extern NATIVE_METHOD(test5);
extern NATIVE_METHOD(test6);
extern NATIVE_METHOD(test7);
extern NATIVE_METHOD(test8);
extern NATIVE_METHOD(test9);

#endif
