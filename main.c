// Linear Allocators
// Fixed Size Chunks Allocator

// https://docstore.mik.ua/manuals/hp-ux/en/B2355-60130/pthread_resume_np.3T.html

// 33:47

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define HEAP_CAPACITY 640000
#define ALLOCATED_CAPACITY 1024

typedef struct {
    void* start;
    size_t size;
} HeapChunk;


char heap[HEAP_CAPACITY] = { 0x00, };
size_t heap_size = 0;

HeapChunk heap_allocated[ALLOCATED_CAPACITY] = { 0x00, };
size_t heap_allocated_size = 0;

void* allocateHeap(size_t size) {
    assert(heap_size + size <= HEAP_CAPACITY);
    void* res = heap + heap_size;
    heap_size += size;

    const HeapChunk chunk = {res, size};
    
    assert(heap_allocated_size < ALLOCATED_CAPACITY);
    heap_allocated[heap_allocated_size++] = chunk;

    return res;
}

void dumpAllocatedChunksHeap(void) {
    printf("Allocated Chunks (%zu):\n", heap_allocated_size);
    for (size_t i = 0; i < heap_allocated_size; i++) {
        printf(" start:%p, size: %zu\n",
                heap_allocated[i].start,
                heap_allocated[i].size);
    }
}

void freeHeap(void *ptr) {
    assert(false && "TODO: 'freeHeap' is not implemented");
}

void collectHeap() {
    assert(false && "TODO: 'collectHeap' is not implemented");
}

int main() {
    // printf("Malloc: %p\n", malloc(0));
    for (int i = 0; i < 5; i++) {
        char* p = malloc(0);
        printf("%p\n", p);
        *p = 69;
    }
    printf("\n");

    for (int i = 0; i < 100; i++) {
        allocateHeap(i);
    }

    // char* root = allocateHeap(69);
    // for (int i = 0; i < 26; i++)
    //     *(root + i) = i + 'A'; // 'A' = (65)_10 = 0x41 = 0b01000001
    
    dumpAllocatedChunksHeap();

    // freeHeap(root);

    return 0;
}