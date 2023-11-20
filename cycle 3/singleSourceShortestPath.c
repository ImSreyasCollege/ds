#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure to represent a vertex in the graph
struct Vertex {
    int id;
    int distance;
};

// Structure to represent a binary heap
struct BinaryHeap {
    int capacity;
    int size;
    struct Vertex* array;
};

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
struct BinaryHeap* createHeap(int capacity);
void insert(struct BinaryHeap* heap, int id, int distance);
struct Vertex extractMin(struct BinaryHeap* heap);
void decreaseKey(struct BinaryHeap* heap, int id, int newDistance);
int isInHeap(struct BinaryHeap* heap, int id);
void dijkstra(struct Graph* graph, int source);

int main() {
    struct Graph* graph = NULL;
    int choice, vertices, edges, i, src, dest, weight, source;

    do {
        printf("\nMenu:\n");
        printf("1. Create Graph\n");
        printf("2. Find Single Source Shortest Path using Dijkstra's Algorithm\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the number of vertices: ");
                scanf("%d", &vertices);

                printf("Enter the number of edges: ");
                scanf("%d", &edges);

                graph = (struct Graph*)malloc(sizeof(struct Graph));
                graph->vertices = vertices;
                graph->edges = edges;
                graph->edge = (struct Edge*)malloc(edges * sizeof(struct Edge));

                printf("Enter the edges (src dest weight):\n");
                for (i = 0; i < edges; i++) {
                    scanf("%d %d %d", &src, &dest, &weight);
                    graph->edge[i].src = src;
                    graph->edge[i].dest = dest;
                    graph->edge[i].weight = weight;
                }
                break;

            case 2:
                if (graph == NULL) {
                    printf("Graph not created. Please create a graph first.\n");
                    break;
                }

                printf("Enter the source vertex: ");
                scanf("%d", &source);

                dijkstra(graph, source);
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

struct BinaryHeap* createHeap(int capacity) {
    struct BinaryHeap* heap = (struct BinaryHeap*)malloc(sizeof(struct BinaryHeap));
    heap->capacity = capacity;
    heap->size = 0;
    heap->array = (struct Vertex*)malloc(capacity * sizeof(struct Vertex));
    return heap;
}

void insert(struct BinaryHeap* heap, int id, int distance) {
    if (heap->size == heap->capacity) {
        printf("Heap overflow\n");
        return;
    }

    int i = heap->size++;
    heap->array[i].id = id;
    heap->array[i].distance = distance;

    // Fix the min heap property
    while (i != 0 && heap->array[(i - 1) / 2].distance > heap->array[i].distance) {
        // Swap the current node with its parent
        struct Vertex temp = heap->array[i];
        heap->array[i] = heap->array[(i - 1) / 2];
        heap->array[(i - 1) / 2] = temp;

        i = (i - 1) / 2; // Move to the parent index
    }
}

struct Vertex extractMin(struct BinaryHeap* heap) {
    if (heap->size <= 0) {
        struct Vertex nullVertex = {-1, -1};
        return nullVertex;
    }

    if (heap->size == 1) {
        heap->size--;
        return heap->array[0];
    }

    // Store the minimum value, and remove it from the heap
    struct Vertex root = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;

    // Fix the min heap property
    int i = 0;
    while (1) {
        int leftChild = 2 * i + 1;
        int rightChild = 2 * i + 2;
        int smallest = i;

        if (leftChild < heap->size && heap->array[leftChild].distance < heap->array[smallest].distance) {
            smallest = leftChild;
        }

        if (rightChild < heap->size && heap->array[rightChild].distance < heap->array[smallest].distance) {
            smallest = rightChild;
        }

        if (smallest != i) {
            // Swap the current node with the smallest child
            struct Vertex temp = heap->array[i];
            heap->array[i] = heap->array[smallest];
            heap->array[smallest] = temp;

            i = smallest; // Move to the smallest child index
        } else {
            break;
        }
    }

    return root;
}

void decreaseKey(struct BinaryHeap* heap, int id, int newDistance) {
    int i;
    for (i = 0; i < heap->size; i++) {
        if (heap->array[i].id == id) {
            heap->array[i].distance = newDistance;
            break;
        }
    }

    // Fix the min heap property
    while (i != 0 && heap->array[(i - 1) / 2].distance > heap->array[i].distance) {
        // Swap the current node with its parent
        struct Vertex temp = heap->array[i];
        heap->array[i] = heap->array[(i - 1) / 2];
        heap->array[(i - 1) / 2] = temp;

        i = (i - 1) / 2; // Move to the parent index
    }
}

int isInHeap(struct BinaryHeap* heap, int id) {
    for (int i = 0; i < heap->size; i++) {
        if (heap->array[i].id == id) {
            return 1;
        }
    }
    return 0;
}

void dijkstra(struct Graph* graph, int source) {
    int vertices = graph->vertices;
    int* distance = (int*)malloc(vertices * sizeof(int));
    int* parent = (int*)malloc(vertices * sizeof(int));

    struct BinaryHeap* heap = createHeap(vertices);

    // Initialize distances and parent array
    for (int i = 0; i < vertices; i++) {
        distance[i] = INT_MAX;
        parent[i] = -1;
    }

    // Set the distance of the source vertex to 0
    distance[source] = 0;
    insert(heap, source, 0);

    while (heap->size > 0) {
        struct Vertex minVertex = extractMin(heap);
        int u = minVertex.id;

        // Iterate through all adjacent vertices of u
        for (int i = 0; i < graph->edges; i++) {
            if (graph->edge[i].src == u) {
                int v = graph->edge[i].dest;
                int weight = graph->edge[i].weight;

                // Relaxation step
                if (isInHeap(heap, v) && distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                    parent[v] = u;
                    decreaseKey(heap, v, distance[v]);
                }
            }
        }
    }

    // Print the result
    printf("\nSingle Source Shortest Path using Dijkstra's Algorithm:\n");
    for (int i = 0; i < vertices; i++) {
        printf("Vertex %d -> Distance: %d, Parent: %d\n", i, distance[i], parent[i]);
    }

    free(distance);
    free(parent);
    free(heap->array);
    free(heap);
}
