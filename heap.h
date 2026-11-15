#ifndef HEAP_H
#define HEAP_H
#include<stdbool.h>

typedef struct HeapNode{
    int cityID;
    int distance;
} HeapNode;

typedef struct MinHeap{
    HeapNode* data;
    int size;
    int capacity;
} MinHeap;

bool initHeap(MinHeap *heap);
bool heapPush(MinHeap *heap, int CityID, int distance);
bool heapPop(MinHeap *heap, HeapNode *min);
void freeHeap(MinHeap *heap);


#endif
