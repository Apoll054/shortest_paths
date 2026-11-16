#include <stdio.h>
#include "heap.h"

int main() {
    MinHeap heap;

    if (!initHeap(&heap)) {
        printf("Failed to initialize heap\n");
        return 1;
    }

    // Insert 12 nodes to test resizing
    for (int i = 0; i < 12; i++) {
        if (!heapPush(&heap, i, 12 - i)) {
            printf("Insertion failed\n");
            freeHeap(&heap);
            return 1;
        }
    }

    printf("Heap size: %d\n", heap.size);
    printf("Heap capacity: %d\n", heap.capacity);

    HeapNode min;

    while (heapPop(&heap, &min)) {
        printf("City %d, Distance %d\n", min.cityID, min.distance);
    }

    if (!heapPop(&heap, &min)) {
        printf("Heap is empty\n");
    }

    freeHeap(&heap);

    return 0;
}