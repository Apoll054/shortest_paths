
#include <stdio.h>
#include "graph.h"

int main(void) {
    Graph graph;

    if (!initGraph(&graph)) {
        printf("Failed to initialize graph\n");
        return 1;
    }

    // Add two roads
    addRoad(&graph, "Houston", "Austin", 150);
    addRoad(&graph, "Austin", "Dallas", 200);

    printf("Number of cities: %d\n", graph.numVertices);
    printf("Graph capacity: %d\n", graph.capacity);
    printf("Hash capacity: %d\n", graph.cityTable.capacity);

    // Print every city's adjacency list
    for (int i = 0; i < graph.numVertices; i++) {
        printf("%s -> ", graph.cityNames[i]);

        EdgePT curr = graph.adjList[i];

        while (curr != NULL) {
            printf("%s (%d) -> ",
                   graph.cityNames[curr->destination_ID],
                   curr->distance);

            curr = curr->next;
        }

        printf("NULL\n");
    }
    

    freeGraph(&graph);
    return 0;
}
