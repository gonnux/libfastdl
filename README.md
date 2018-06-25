# libfastdl [![Build Status](https://travis-ci.org/vinbero-server/libfastdl.svg?branch=master)](https://travis-ci.org/vinbero-server/libfastdl)
## About
A libdl wrapper library that hashes function pointers to a hash table
## Usage
```c
#include <dlfcn.h>
#include <fastdl.h>
int main() {
    struct fastdl_Handle handle; // fastdl handle
    fastdl_open(&handle, "libfastdl_test_lib.so", RTLD_LAZY | RTLD_GLOBAL); // returns 0 on success, -1 on error.
    int (*multiply)(int, int);
    fastdl_sym(&handle, "multiply", (void**)&multiply); // returns 0, 1 on success(fp is not hashed, hashed), -1 on error.
    // fastdl_sym(&handle, "multiply", (void**)&multiply);
    multiply(2, 4) // returns 8
    fastdl_close(&handle); // returns 0 on success, non-zero(same as dlclose() returns) on error.
    return 0;
}
```
## Performance
<img src="https://github.com/vinbero-server/libfastdl/blob/master/test-result.png"></img>
## Dependencies
libdl, uthash
## License
Mozilla Public License 2.0
