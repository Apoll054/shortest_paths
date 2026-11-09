#ifndef GRAPH_H
#define GRAPH_H
#include <stdbool.h>
typedef struct Edge Edge;
typedef Edge* EdgePT;

struct Edge {
    int destination_ID;
    int distance;
    EdgePT next;
};

typedef struct CityEntry CityEntry;
typedef struct CityEntry* CityEntryPT;

struct CityEntry{
    int ID;
    char* cityName;
    CityEntryPT next;
};

typedef struct HashTable{
    CityEntryPT* entries;
    int capacity;
    int size;
} HashTable;

typedef struct Graph {
    EdgePT *adjList;
    int numVertices;
    int capacity;
    char **cityNames;
    HashTable cityTable;
}Graph;





bool initGraph(Graph *graph);
#endif