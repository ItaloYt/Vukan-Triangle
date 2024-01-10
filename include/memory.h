#ifndef MEMORY_HEADER
#define MEMORY_HEADER

typedef void (*MemoryFreeCallback)(void *pointer);

void memory_init();
void memory_push(void *pointer, MemoryFreeCallback callback);
void memory_free();

#endif
