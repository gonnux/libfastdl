#include <dlfcn.h>
#include <libgenc/genc_Map.h>
#include "fastdl.h"

int fastdl_open(struct fastdl_Handle* handle, const char* path, int flag) {
    handle->dlHandle = dlopen(path, flag);
    if(handle->dlHandle == NULL)
        return -1;
    GENC_MAP_INIT(handle);
    return 0;
}

int fastdl_sym(struct fastdl_Handle* handle, const char* symbolName, void** symbolPointer) {
    int ret;
    FASTDL_SYM(handle, symbolName, symbolPointer, &ret);
    return ret;
}

int fastdl_close(struct fastdl_Handle* handle) {
    GENC_MAP_FOREACH_BEGIN(handle, symbol)
        free(symbol);
    GENC_MAP_FOREACH_END(handle, symbol)
    GENC_MAP_FREE(handle);
    return dlclose(handle->dlHandle);
}

char* fastdl_error() {
    return dlerror();
}
