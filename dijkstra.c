#include "dijkstra.h"
#include "graph.h"
#include "heap.h"
#include <limits.h>
#include <stdlib.h>

bool dijkstra(Graph *graph, int startID, int dist[], int prev[]) {
    if (graph ==NULL || dist == NULL || prev == NULL ||//validating input
        startID < 0 || startID >= graph->numVertices) {
        return false;
    }

    for (int i = 0; i < graph->numVertices; i++) {//initialize all distances to be inf and prev to be -1
        dist[i] = INT_MAX;
        prev[i] = -1;
    }

    dist[startID] = 0;//distance for the starting city will be 0
    MinHeap heap;
    if (!initHeap(&heap)) {//validating heap initialization;
    return false;
    }
    if (!heapPush(&heap, startID, 0)) {//validating heapPush
    freeHeap(&heap);
    return false;
    }
    HeapNode current;
    while(heapPop(&heap, &current)){//looping until we cannot pop anymore
        int cityID=current.cityID;
        if(current.distance>dist[cityID]){//skips outdated distances
            continue;
        }
        EdgePT Edge=graph->adjList[cityID];//we explore possible neighbors from current node;
        while(Edge!=NULL){//loop until we reach the end of adjlist;
            int neighborID=Edge->destination_ID;
            if (Edge->distance > INT_MAX - current.distance) {//prevents integer overflow while calculating neighbor distance
                Edge = Edge->next;
                continue;
            }
            int neighborDist=current.distance + Edge->distance;//total distance from our startcity to this neighbor
            if(neighborDist<dist[neighborID]){//if this distance<the distance we have then we push and update
                if (!heapPush(&heap, neighborID, neighborDist)) {
                freeHeap(&heap);
                return false;
                }

                dist[neighborID] = neighborDist;
                prev[neighborID]=current.cityID;
            }
            Edge=Edge->next;


        }
    }
    freeHeap(&heap);//free allocated heap
    return true;






}