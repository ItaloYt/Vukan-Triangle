#include "conventions.h"
#include <errno.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

struct MemoryBlock {
    void *pointer;

    MemoryFreeCallback callback;
};

struct MemoryList {
    struct MemoryBlock *blocks;

    unsigned block_size;
    unsigned length;
} list;

#define BLOCK_SIZE 10

void memory_init() {
    list.block_size = BLOCK_SIZE;
    list.length = 0;
    list.blocks = malloc(list.block_size * sizeof(struct MemoryBlock));

    if(!list.blocks) {
        TREAT fprintf(stderr, "error using malloc: %s\n", strerror(errno));

        exit(1);
    }
}

void memory_push(void *pointer, MemoryFreeCallback callback) {
    if(list.length >= list.block_size) {
        list.block_size += BLOCK_SIZE;
        list.blocks = realloc(list.blocks, list.block_size * sizeof(struct MemoryBlock));

        if(!list.blocks) {
            TREAT fprintf(stderr, "error using realloc: %s\n", strerror(errno));

            exit(1);
        }
    }

    list.blocks[list.length].pointer = pointer;
    list.blocks[list.length].callback = callback;

    ++list.length;
}

void memory_free() {
    for(int index = list.length - 1; index >= 0; --index) {
        if(list.blocks[index].callback)
            list.blocks[index].callback(list.blocks[index].pointer);
        else
            free(list.blocks[index].pointer);
    }

    free(list.blocks);
}
