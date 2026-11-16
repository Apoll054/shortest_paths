#include <stdio.h>
#include "graph.h"
#include "dijkstra.h"

int main() {
    Graph graph;

    if (!initGraph(&graph)) {
        printf("Failed to initialize graph\n");
        return 1;
    }

    // Create roads
    addRoad(&graph, "Houston", "Austin", 100);
    addRoad(&graph, "Houston", "Dallas", 400);
    addRoad(&graph, "Austin", "Waco", 150);
    addRoad(&graph, "Waco", "Dallas", 100);

    int dist[4];
    int prev[4];

    // Houston is city ID 0
    if (!dijkstra(&graph, 0, dist, prev)) {
        printf("Dijkstra failed\n");
        freeGraph(&graph);
        return 1;
    }

    for (int i = 0; i < graph.numVertices; i++) {
        printf("City: %s, Distance: %d, Previous: ",
               graph.cityNames[i], dist[i]);

        if (prev[i] == -1) {
            printf("None\n");
        } else {
            printf("%s\n", graph.cityNames[prev[i]]);
        }
    }

    freeGraph(&graph);
    return 0;
}