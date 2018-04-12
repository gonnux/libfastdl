#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <setjmp.h>
#include <cmocka.h>
#include <dlfcn.h>

void dl_test(void** state) {
    void* handle;
    handle = dlopen("./libfastdl_test_lib.so", RTLD_LAZY | RTLD_GLOBAL);
    int (*multiply)(int, int);
    for(int i = 0; i < 10000000; ++i) {
        multiply = dlsym(handle, "multiply");
        assert_int_equal(multiply(2, 4), 8);
    }
    assert_int_equal(dlclose(handle), 0);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(dl_test)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

