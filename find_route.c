#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "graph.h"
#include "dijkstra.h"
#define END_MARKER "END OF INPUT"

static void printRoads(Graph *graph, int startID, int destID, int dist[], int prev[]);

int main() {
    char filename[256];
    char origin[100];
    char destination[100];

    printf("Enter filename: ");
    scanf("%255s", filename);

    printf("Enter origin city: ");
    scanf("%99s", origin);

    printf("Enter destination city: ");
    scanf("%99s", destination);

    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Could not open file\n");
        return 1;
    }

    Graph graph;

    if (!initGraph(&graph)) {//initializes and checks a graph
        fclose(file);
        return 1;
    }
    char line[256];//buffers for reading while data
    char from[100];
    char to[100];
    int distance;
    while(fgets(line,sizeof(line),file)!=NULL){//read each line

        if(strncmp(line,END_MARKER,sizeof(END_MARKER)-1)==0){//break if we reach end marker
            break;

        }
        if(sscanf(line, "%99s %99s %d", from, to, &distance) != 3){//if scanned line doesnot have the 3 variables
            printf("Invalid input file\n");
            fclose(file);
            freeGraph(&graph);
            return 1;

        }
        if (!addRoad(&graph, from, to, distance)) {//if failed to add road
            printf("Failed to add road\n");
            fclose(file);
            freeGraph(&graph);
            return 1;
        }   

    }

    fclose(file);

     int startID = getCityID(&graph, origin);
     int destID = getCityID(&graph, destination);
     if (startID == -1 || destID == -1) {
        printf("distance: infinity\n");
        printf("route:\n");
        printf("none\n");

        freeGraph(&graph);
        return 0;
    }
    int numVertices=graph.numVertices;
    int *dist=malloc(numVertices*sizeof(int));
    int *prev=malloc(numVertices*sizeof(int));

    if (dist == NULL || prev == NULL) {//check if allocation was successful
        free(dist);
        free(prev);
        freeGraph(&graph);
        return 1;
    }
    if (!dijkstra(&graph, startID, dist, prev)) {//calling the algorithm and checking if it was successful
        printf("Dijkstra failed\n");
        free(dist);
        free(prev);
        freeGraph(&graph);
        return 1;
    }

    if (dist[destID] == INT_MAX) {
        printf("distance: infinity\n");
        printf("route:\n");
        printf("none\n");
    }
    else {
        printf("distance: %d km\n", dist[destID]);
        printf("route:\n");

        printRoads(&graph, startID, destID, dist, prev);
    }





    free(dist);
    free(prev);
    freeGraph(&graph);

    return 0;
}

static void printRoads(Graph *graph, int startID, int destID,int dist[], int prev[]){
    if(startID=destID){
        return;
    }
    int previous=prev[destID];
    printRoads(graph,startID,previous,dist,prev);
    printf("%s to %s, %d km\n",graph->cityNames[previous],graph->cityNames[destID],dist[destID]-dist[previous]);

    
}