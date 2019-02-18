#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <setjmp.h>
#include <cmocka.h>
#include <dlfcn.h>
#include "../src/fastdl.h"

void fastdl_test(void** state) {
    struct fastdl_Handle handle;
    assert_int_equal(fastdl_open(&handle, "./libfastdl_test_lib.so", RTLD_LAZY | RTLD_GLOBAL), 0);
    int (*multiply)(int, int);
    for(int i = 0; i < 10000000; ++i) {
        int retVal = fastdl_sym(&handle, "multiply", (void**)&multiply);
        if(i == 0)
            assert_int_equal(retVal, 0);
        else
            assert_int_equal(retVal, 1);
        assert_int_equal(multiply(2, 4), 8);
    }
    assert_int_equal(fastdl_close(&handle), 0);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(fastdl_test)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

