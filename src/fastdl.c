#include <dlfcn.h>
#include <uthash.h>
#include "fastdl.h"

int fastdl_open(struct fastdl_Handle* handle, const char* path, int flag) {
    handle->cache = NULL;
    handle->dlHandle = dlopen(path, flag);
    if(handle->dlHandle == NULL)
        return -1;
    return 0;
}

int fastdl_sym(struct fastdl_Handle* handle, const char* symbolName, void** symbolPointer) {
    struct fastdl_Symbol* symbol;
    size_t symbolNameLength = strlen(symbolName);

    HASH_FIND(hashHandle, handle->cache, &symbolName, symbolNameLength, symbol);
    if(symbol != NULL) {
        *symbolPointer = symbol->pointer;
        return 1;
    }

    *symbolPointer = dlsym(handle->dlHandle, symbolName);
    if(*symbolPointer == NULL)
        return -1;
    symbol = calloc(1, sizeof(struct fastdl_Symbol));
    symbol->name = symbolName;
    symbol->pointer = *symbolPointer;
    HASH_ADD(hashHandle, handle->cache, name, symbolNameLength, symbol);
    return 0;
}

int fastdl_close(struct fastdl_Handle* handle) {
    struct fastdl_Symbol* symbol;
    struct fastdl_Symbol* tmpSymbol;
    HASH_ITER(hashHandle, handle->cache, symbol, tmpSymbol) {
        HASH_DELETE(hashHandle, handle->cache, symbol);
        free(symbol);
    }
    return dlclose(handle->dlHandle);
}

char* fastdl_error() {
    return dlerror();
}
