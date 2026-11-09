#include "graph.h"
#include <stdlib.h>
#include <string.h>
bool initGraph(Graph *graph);
static bool initHashTable(HashTable* table);
static unsigned int HashCity(const char *name, int capacity);//use unsigned int for hash and const 
                                                            //to ensure no changes
static int findCityID(HashTable *table, const char* name);
static int insertCity(Graph *graph, const char *name);  
static bool resizeGraph(Graph *graph); 
static bool resizeHash(HashTable* table);                                    
                            

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
static int findCityID(HashTable *table, const char* name){//if city present, returns ID otherwise -1
    unsigned int index= HashCity(name, table->capacity);
    CityEntryPT currCity = table->entries[index];
    while(currCity!=NULL){
        if (strcmp(name,currCity->cityName)==0){
            return currCity->ID;
        }
        currCity=currCity->next;

    }
    return -1;
}
static bool resizeHash(HashTable* table){
    int oldCapacity=(table->capacity);
    int newCapacity= (table->capacity)*2;
    CityEntryPT* newEntries = calloc(newCapacity, sizeof(CityEntryPT));

    if (newEntries == NULL) {
        return false;
    }
    for (int i=0; i<oldCapacity;i++){
        CityEntryPT curr=table->entries[i];
        while(curr!=NULL){

            CityEntryPT next=curr->next; //save next city
            int index = HashCity(curr->cityName,newCapacity);

            curr->next = newEntries[index]; // link to new bucket
            newEntries[index]=curr; //update bucket

            curr= next; // continue

        }
    }
    free(table->entries);
    table->entries=newEntries;
    table->capacity=newCapacity;
    return true;
}

static bool resizeGraph(Graph *graph){
    int oldCapacity = graph->capacity;
    int newCapacity = oldCapacity * 2;

    EdgePT *temp= realloc(graph->adjList,newCapacity*sizeof(EdgePT));
    if (temp==NULL){
        return false;
    }
    graph->adjList=temp;
    char **temp1= realloc(graph->cityNames,newCapacity*sizeof(char*));
    if(temp1==NULL){
        return false;
    }
    graph->cityNames=temp1;

    for (int i = oldCapacity; i < newCapacity; i++) {//making newly allocated spaces NULL
        graph->adjList[i] = NULL;
        graph->cityNames[i] = NULL;
    }

    graph->capacity = newCapacity;
    return true;

}

static int insertCity(Graph *graph, const char *name){
    HashTable * table= &(graph->cityTable);
    int ID= findCityID(table,name);

    if(ID!=-1){//if city already exists return the ID
        return ID;  
    }
    if(graph->numVertices >= graph->capacity){//if no of vertices exceeds capacity resize
        if(!resizeGraph(graph)){//if fail to resize then return
            return -1;
        }
    }
    int bucket= HashCity(name,(table->capacity));
    CityEntryPT entry= malloc(sizeof(CityEntry));//allocate space for new entry
    if (entry==NULL){
        return -1;
    }
    char *newName = malloc(strlen(name) + 1);//allocate space for name in city entry

    if (newName == NULL) {//free entry and return -1 if allocation fails
        free(entry);
        return -1;
    }

    strcpy(newName, name);//copy name into newName

    entry->cityName = newName;//asign cityName pointer to point to newName

    entry->ID=graph->numVertices;//the id will be ordered in the order it was added in
    graph->cityNames[entry->ID]=newName;//add name to city names


    entry->next = table->entries[bucket];//insert entry in the beginning of the linked list
    table->entries[bucket] = entry;

    graph->numVertices++;//increase vertices and table size
    table->size++;

    return entry->ID;




}
