#include "heap.h"
#include <stdlib.h>

//helper bubble up function;
static void bubbleUp(MinHeap *heap, int i){
    while(i>0){
        int parent=(i-1)/2;
        if(heap->data[parent].distance <=heap->data[i].distance){
            return;
        }
        else{
            HeapNode temp= heap->data[parent];
            heap->data[parent]=heap->data[i];
            heap->data[i]=temp;
        }
        i=parent;
    
    }
}

static void bubbleDown(MinHeap *heap, int i) {//helper bubble down
    while (true) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < heap->size &&//need to make sure left and right are in bounds
            heap->data[left].distance < heap->data[smallest].distance) {
            smallest = left;
        }

        if (right < heap->size &&
            heap->data[right].distance < heap->data[smallest].distance) {
            smallest = right;
        }

        if (smallest == i) {
            return;
        }

        HeapNode temp = heap->data[i];
        heap->data[i] = heap->data[smallest];
        heap->data[smallest] = temp;

        i = smallest;
    }
}

bool initHeap(MinHeap *heap) {
    if (heap == NULL) return false;

    heap->size = 0;
    heap->capacity = 10;
    heap->data=malloc(heap->capacity*sizeof(HeapNode));//allocate size for heapNodes
    return heap->data!=NULL;

}
bool heapPush(MinHeap *heap, int CityID, int distance){
    if (heap == NULL || heap->data == NULL) {
    return false;
    }
    if (heap->size >= heap->capacity) {//resize if mem full
        int newCapacity = heap->capacity * 2;

        HeapNode *temp = realloc(heap->data,newCapacity * sizeof(HeapNode));

        if (temp == NULL) {
            return false;
        }

        heap->data = temp;
        heap->capacity = newCapacity;

    }
    heap->data[heap->size].cityID = CityID;//enter new data at the end
    heap->data[heap->size].distance = distance;
    heap->size++;
    bubbleUp(heap, heap->size - 1);
    return true;


}

bool heapPop(MinHeap *heap, HeapNode *min){
    if (heap == NULL || min == NULL || heap->data == NULL || heap->size == 0) {
    return false;
    }

    *min = heap->data[0];
    // Move the last node to the root
    heap->data[0]=heap->data[heap->size-1];
    // Decrease size
    heap->size--;
    // Restore heap order
    bubbleDown(heap,0);


    return true;
}
void freeHeap(MinHeap *heap) {
    if (heap == NULL) {
        return;
    }

    free(heap->data);
    heap->data = NULL;
    heap->size = 0;
    heap->capacity = 0;
}