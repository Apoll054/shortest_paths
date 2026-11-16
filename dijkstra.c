#include "dijkstra.h"
#include "graph.h"
#include "heap.h"
#include <limits.h>
#include <stdlib.h>

bool dijkstra(Graph *graph, int startID, int dist[], int prev[]) {
    if (graph ==NULL || dist == NULL || prev == NULL ||
        startID < 0 || startID >= graph->numVertices) {
        return false;
    }

    for (int i = 0; i < graph->numVertices; i++) {//initialize all distances to be inf and prev to be -1
        dist[i] = INT_MAX;
        prev[i] = -1;
    }

    dist[startID] = 0;
    MinHeap heap;
    if (!initHeap(&heap)) {
    return false;
    }
    if (!heapPush(&heap, startID, 0)) {
    freeHeap(&heap);
    return false;
    }
    HeapNode current;
    while(HeapPop())


    // We'll continue implementing Dijkstra here.
}