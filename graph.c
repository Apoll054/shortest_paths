#include "graph.h"
#include <stdlib.h>
static bool initHashTable(HashTable* table);
static unsigned int HashCity(const char *name, int capacity);//use unsigned int for hash and const 
                                                            //to ensure no changes 
bool initGraph(Graph *graph){

    if(graph==NULL) return false;

    graph->capacity=10;
    graph->numVertices=0;
    graph->cityTable = (HashTable){0};//initialization to 0 ensures predictable initial state
    graph->adjList = calloc(graph->capacity,sizeof(EdgePT));
    graph->cityNames=calloc(graph->capacity,sizeof(char*));


    if (graph->adjList == NULL || 
        graph->cityNames == NULL||
        !initHashTable(&graph->cityTable))
        {


        free(graph->adjList);
        free(graph->cityNames);

        graph->adjList=NULL;
        graph->cityNames=NULL;
        graph->cityTable = (HashTable){0};

        return false;
    }

    return true;
}


static bool initHashTable(HashTable* table){
    table->capacity=17;
    table->size=0;
    table->entries= calloc(table->capacity,sizeof(CityEntryPT));
    return table->entries!=NULL;
}
static unsigned int HashCity(const char *name, int capacity){
    unsigned int hash=0;
    for(int i=0; name[i]!='\0';i++){//casting name[i] as unsigned char to prevent negatives
        hash=( hash * 31 + (unsigned char)name[i])% capacity;//31 is a prime number good to use in this case
    }
    return hash;
}
