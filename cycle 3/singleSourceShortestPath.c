#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure to represent a node in the graph
struct Node {
    int vertex;
    int weight;
    struct Node* next;
};

// Structure to represent the graph
struct Graph {
    int V;          // Number of vertices
    struct Node** adjList;  // Adjacency list
};

// Structure to represent a node in the heap
struct HeapNode {
    int vertex;
    int distance;
};

// Structure to represent the heap
struct BinaryHeap {
    struct HeapNode* array;
    int capacity;
    int size;
};

// Function to create a new graph
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->adjList = (struct Node**)malloc(V * sizeof(struct Node*));

    for (int i = 0; i < V; ++i) {
        graph->adjList[i] = NULL;
    }

    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = dest;
    newNode->weight = weight;
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
}

// Function to create a new heap node
struct HeapNode* createHeapNode(int vertex, int distance) {
    struct HeapNode* node = (struct HeapNode*)malloc(sizeof(struct HeapNode));
    node->vertex = vertex;
    node->distance = distance;
    return node;
}

// Function to create a new binary heap
struct BinaryHeap* createBinaryHeap(int capacity) {
    struct BinaryHeap* heap = (struct BinaryHeap*)malloc(sizeof(struct BinaryHeap));
    heap->array = (struct HeapNode*)malloc(capacity * sizeof(struct HeapNode));
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

// Function to swap two heap nodes
void swapHeapNodes(struct HeapNode* a, struct HeapNode* b) {
    struct HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify a subtree rooted with the given index
void heapify(struct BinaryHeap* heap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->array[left].distance < heap->array[smallest].distance) {
        smallest = left;
    }

    if (right < heap->size && heap->array[right].distance < heap->array[smallest].distance) {
        smallest = right;
    }

    if (smallest != index) {
        swapHeapNodes(&heap->array[index], &heap->array[smallest]);
        heapify(heap, smallest);
    }
}

// Function to extract the minimum node from the heap
struct HeapNode extractMin(struct BinaryHeap* heap) {
    if (heap->size == 1) {
        heap->size--;
        return heap->array[0];
    }

    struct HeapNode root = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    heapify(heap, 0);

    return root;
}

// Function to decrease the distance value of a given vertex
void decreaseKey(struct BinaryHeap* heap, int vertex, int newDistance) {
    int i;
    for (i = 0; i < heap->size; i++) {
        if (heap->array[i].vertex == vertex) {
            break;
        }
    }

    heap->array[i].distance = newDistance;

    // Fix the min heap property if it is violated
    while (i > 0 && heap->array[i].distance < heap->array[(i - 1) / 2].distance) {
        swapHeapNodes(&heap->array[i], &heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Function to check if a vertex is in the heap
int isInHeap(struct BinaryHeap* heap, int vertex) {
    for (int i = 0; i < heap->size; i++) {
        if (heap->array[i].vertex == vertex) {
            return 1;
        }
    }
    return 0;
}

// Function to print the distance values of vertices
void printDistances(int* dist, int n) {
    printf("Shortest distances from source:\n");
    for (int i = 0; i < n; i++) {
        printf("To vertex %d: %d\n", i, dist[i]);
    }
}

// Function to perform Dijkstra's algorithm using a binary heap
void dijkstra(struct Graph* graph, int startVertex) {
    int V = graph->V;
    int* dist = (int*)malloc(V * sizeof(int));
    struct BinaryHeap* heap = createBinaryHeap(V);

    // Initialize distances and heap
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        heap->array[i] = *createHeapNode(i, dist[i]);
        heap->size++;
    }

    // Set the distance of the start vertex to 0
    dist[startVertex] = 0;
    decreaseKey(heap, startVertex, 0);

    // Dijkstra's algorithm
    while (heap->size > 0) {
        struct HeapNode minNode = extractMin(heap);
        int u = minNode.vertex;

        struct Node* temp = graph->adjList[u];
        while (temp != NULL) {
            int v = temp->vertex;
            int weight = temp->weight;

            if (isInHeap(heap, v) && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                decreaseKey(heap, v, dist[v]);
            }

            temp = temp->next;
        }
    }

    // Print the shortest distances
    printDistances(dist, V);

    free(dist);
    free(heap->array);
    free(heap);
}

int main() {
    int V, E;

    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    struct Graph* graph = createGraph(V);

    printf("Enter the number of edges: ");
    scanf("%d", &E);

    printf("Enter edges in the format (src dest weight):\n");
    for (int i = 0; i < E; i++) {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(graph, src, dest, weight);
    }

    int startVertex;
    printf("Enter the starting vertex: ");
    scanf("%d", &startVertex);

    dijkstra(graph, startVertex);

    return 0;
}