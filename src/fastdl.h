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

#define FASTDL_SYM(handle, symbolName, symbolPointer, ret) \
do { \
    struct fastdl_Symbol* symbol = NULL; \
    size_t symbolNameLength = strlen(symbolName); \
    HASH_FIND(hashHandle, (handle)->cache, &(symbolName), symbolNameLength, symbol); \
    if(symbol != NULL) { \
        *(symbolPointer) = symbol->pointer; \
        *(ret) = 1; \
    } \
    *(symbolPointer) = dlsym((handle)->dlHandle, (symbolName)); \
    if(*(symbolPointer) == NULL) \
        *(ret) = -1; \
    symbol = calloc(1, sizeof(struct fastdl_Symbol)); \
    symbol->name = (symbolName); \
    symbol->pointer = *(symbolPointer); \
    HASH_ADD(hashHandle, (handle)->cache, name, symbolNameLength, symbol); \
    *(ret) = 0; \
} while(0);

int fastdl_close(struct fastdl_Handle* handle);
char* fastdl_error();

#endif
