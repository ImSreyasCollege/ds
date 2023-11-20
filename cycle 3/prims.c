#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 20

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// Structure to represent a graph
struct Graph {
    int vertices, edges;
    struct Edge* edge;
};

// Function prototypes
struct Graph* createGraph(int vertices, int edges);
void addEdge(struct Graph* graph, int src, int dest, int weight);
void primMST(struct Graph* graph);

int main() {
    struct Graph* graph = NULL;
    int choice, vertices, edges, i, src, dest, weight;

    do {
        printf("\nMenu:\n");
        printf("1. Create Graph\n");
        printf("2. Find Minimum Cost Spanning Tree using Prim's Algorithm\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the number of vertices: ");
                scanf("%d", &vertices);

                printf("Enter the number of edges: ");
                scanf("%d", &edges);

                graph = createGraph(vertices, edges);

                printf("Enter the edges (src dest weight):\n");
                for (i = 0; i < edges; i++) {
                    scanf("%d %d %d", &src, &dest, &weight);
                    addEdge(graph, src, dest, weight);
                }
                break;

            case 2:
                if (graph == NULL) {
                    printf("Graph not created. Please create a graph first.\n");
                    break;
                }

                primMST(graph);
                break;

            case 3:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}

struct Graph* createGraph(int vertices, int edges) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vertices = vertices;
    graph->edges = edges;
    graph->edge = (struct Edge*)malloc(edges * sizeof(struct Edge));
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest, int weight) {
    graph->edge[src].src = src;
    graph->edge[src].dest = dest;
    graph->edge[src].weight = weight;

    graph->edge[dest].src = dest;
    graph->edge[dest].dest = src;
    graph->edge[dest].weight = weight;
}

void primMST(struct Graph* graph) {
    int parent[MAX_VERTICES];
    int key[MAX_VERTICES];
    int inMST[MAX_VERTICES];

    // Initialize keys and inMST
    for (int i = 0; i < graph->vertices; i++) {
        key[i] = INT_MAX;
        inMST[i] = 0;
    }

    // Start with the first vertex
    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < graph->vertices - 1; count++) {
        int minKey = INT_MAX;
        int minIndex = -1;

        // Find the vertex with the minimum key value
        for (int v = 0; v < graph->vertices; v++) {
            if (inMST[v] == 0 && key[v] < minKey) {
                minKey = key[v];
                minIndex = v;
            }
        }

        inMST[minIndex] = 1;

        // Update key values and parent index of the adjacent vertices of the picked vertex
        for (int v = 0; v < graph->vertices; v++) {
            if (graph->edge[minIndex].weight && inMST[v] == 0 && graph->edge[v].weight < key[v]) {
                parent[v] = minIndex;
                key[v] = graph->edge[v].weight;
            }
        }
    }

    // Print the minimum cost spanning tree
    printf("\nMinimum Cost Spanning Tree using Prim's Algorithm:\n");
    for (int i = 1; i < graph->vertices; i++) {
        printf("Edge: %d - %d, Weight: %d\n", parent[i], i, graph->edge[i].weight);
    }
}
