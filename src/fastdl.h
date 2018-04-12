#ifndef _FASTDL_H
#define _FASTDL_H

#include <uthash.h>

struct fastdl_Symbol {
    const char* name;
    void* pointer;
    UT_hash_handle hashHandle;
};

struct fastdl_Handle {
    void* dlHandle;
    struct fastdl_Symbol* cache;
};

int fastdl_open(struct fastdl_Handle* handle, const char* path, int flag);
int fastdl_sym(struct fastdl_Handle* handle, const char* symbolName, void** symbolPointer);
int fastdl_close(struct fastdl_Handle* handle);

#endif
