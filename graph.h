typedef struct Edge Edge;
typedef Edge* EdgePT;

struct Edge {
    int destination_ID;
    int distance;
    EdgePT next;
};
typedef Graph {
    EdgePT *adjList;
    int numVertices;
    int capacity;
}

