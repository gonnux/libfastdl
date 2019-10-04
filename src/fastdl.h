#ifndef _FASTDL_H
#define _FASTDL_H

#include <libgenc/genc_Map.h>
#include <stdint.h>

struct fastdl_Symbol {
    void* pointer;
    GENC_MAP_ELEM(struct fastdl_Symbol);
};

struct fastdl_Handle {
    void* dlHandle;
    GENC_MAP(struct fastdl_Symbol);
};

int fastdl_open(struct fastdl_Handle* handle, const char* path, int flag);
int fastdl_sym(struct fastdl_Handle* handle, const char* symbolName, void** symbolPointer);

#define FASTDL_SYM(handle, symbolName, symbolPointer, ret) \
do { \
    struct fastdl_Symbol* symbol = NULL; \
    struct fastdl_Symbol* oldSymbol = NULL; \
    size_t symbolNameLength = strlen(symbolName); \
    GENC_MAP_GET(handle, symbolName, symbolNameLength, &symbol); \
    if(symbol != NULL) { \
        *(symbolPointer) = symbol->pointer; \
        *(ret) = 1; \
        break; \
    } \
    *(symbolPointer) = dlsym((handle)->dlHandle, symbolName); \
    if(*(symbolPointer) == NULL) { \
        *(ret) = -1; \
        break; \
    } \
    symbol = malloc(sizeof(struct fastdl_Symbol)); \
    GENC_MAP_ELEM_INIT(symbol); \
    GENC_MAP_ELEM_KEY(symbol) = (uint8_t*)symbolName; \
    GENC_MAP_ELEM_KEY_LENGTH(symbol) = symbolNameLength; \
    symbol->pointer = *(symbolPointer); \
    GENC_MAP_SET(handle, symbol, &oldSymbol); \
    *(ret) = 0; \
} while(0)

int fastdl_close(struct fastdl_Handle* handle);
char* fastdl_error();

#endif
