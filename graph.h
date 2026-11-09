#ifndef GRAPH_H
#define GRAPH_H
#include <stdbool.h>
typedef struct Edge Edge;
typedef Edge* EdgePT; //points to an Edge, can represents start of a Linked list of edges or any individual node

struct Edge {
    int destination_ID;
    int distance;
    EdgePT next;
};

typedef struct CityEntry CityEntry;
typedef struct CityEntry* CityEntryPT;// points to an entry, can represent entries in the hash table

struct CityEntry{ // maps a city name to it's ID
    int ID;
    char* cityName;
    CityEntryPT next;
};

typedef struct HashTable{//hash table with separate chaining
    CityEntryPT* entries;
    int capacity;
    int size;
} HashTable;

typedef struct Graph {//graph structure encapsulates all the structures here, each graph contains a hash table for the set
    EdgePT *adjList;
    int numVertices;
    int capacity;
    char **cityNames;
    HashTable cityTable;
}Graph;





bool initGraph(Graph *graph);
#endif