#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// Structure to represent a subset for union-find
struct Subset {
    int parent;
    int rank;
};

// Structure to represent a graph
struct Graph {
    int vertices, edges;
    struct Edge* edge;
};

// Function prototypes
struct Graph* createGraph(int vertices, int edges);
void addEdge(struct Graph* graph, int src, int dest, int weight);
int find(struct Subset subsets[], int i);
void unionSets(struct Subset subsets[], int x, int y);
int compareEdges(const void* a, const void* b);
void kruskalMST(struct Graph* graph);

int main() {
    struct Graph* graph = NULL;
    int choice, vertices, edges, i, src, dest, weight;

    do {
        printf("\nMenu:\n");
        printf("1. Create Graph\n");
        printf("2. Find Minimum Cost Spanning Tree using Kruskal's Algorithm\n");
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

                kruskalMST(graph);
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

int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

void unionSets(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    } else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parent = xroot;
    } else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int compareEdges(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

void kruskalMST(struct Graph* graph) {
    int vertices = graph->vertices;
    struct Edge result[vertices]; // To store the result MST
    int e = 0; // Index variable for result[]

    // Step 1: Sort all the edges in non-decreasing order of their weight
    qsort(graph->edge, graph->edges, sizeof(graph->edge[0]), compareEdges);

    // Allocate memory for creating subsets
    struct Subset* subsets = (struct Subset*)malloc(vertices * sizeof(struct Subset));

    // Create subsets with single elements
    for (int v = 0; v < vertices; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Number of edges to be taken is equal to V-1
    while (e < vertices - 1 && graph->edge[e].src != -1) {
        struct Edge nextEdge = graph->edge[e++];

        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);

        // If including this edge does not cause cycle, include it in the result and update union of sets
        if (x != y) {
            result[e - 1] = nextEdge;
            unionSets(subsets, x, y);
        }
    }

    // Print the result MST
    printf("\nMinimum Cost Spanning Tree using Kruskal's Algorithm:\n");
    for (int i = 0; i < e - 1; i++) {
        printf("Edge: %d - %d, Weight: %d\n", result[i].src, result[i].dest, result[i].weight);
    }

    free(subsets);
}
