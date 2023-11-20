#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

struct Queue {
    int front, rear, capacity;
    int* array;
};

struct Stack {
    int top;
    int capacity;
    int* array;
};

struct Queue* createQueue(int capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->rear = -1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

int isEmpty(struct Queue* queue) {
    return queue->front == -1;
}

void enqueue(struct Queue* queue, int item) {
    if (queue->rear == queue->capacity - 1) {
        printf("Queue overflow\n");
        return;
    }
    if (queue->front == -1)
        queue->front = 0;
    queue->rear++;
    queue->array[queue->rear] = item;
}

int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue underflow\n");
        return -1;
    }
    int item = queue->array[queue->front];
    queue->front++;
    if (queue->front > queue->rear)
        queue->front = queue->rear = -1;
    return item;
}

int isEmptyStack(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, int item) {
    if (stack->top == stack->capacity - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack->array[++stack->top] = item;
}

int pop(struct Stack* stack) {
    if (isEmptyStack(stack)) {
        printf("Stack underflow\n");
        return -1;
    }
    return stack->array[stack->top--];
}

struct Graph {
    int vertices;
    int** adjacencyMatrix;
};

struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vertices = vertices;

    // Allocating memory for the adjacency matrix
    graph->adjacencyMatrix = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        graph->adjacencyMatrix[i] = (int*)malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++) {
            graph->adjacencyMatrix[i][j] = 0; // Initializing with 0
        }
    }

    return graph;
}

void addEdge(struct Graph* graph, int source, int destination) {
    graph->adjacencyMatrix[source][destination] = 1;
}

void displayMatrix(struct Graph* graph) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < graph->vertices; i++) {
        for (int j = 0; j < graph->vertices; j++) {
            printf("%d ", graph->adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
}

void DFSUtil(struct Graph* graph, int vertex, int* visited) {
    printf("%d ", vertex);
    visited[vertex] = 1;

    for (int i = 0; i < graph->vertices; i++) {
        if (graph->adjacencyMatrix[vertex][i] == 1 && !visited[i]) {
            DFSUtil(graph, i, visited);
        }
    }
}

void DFS(struct Graph* graph, int startVertex) {
    int* visited = (int*)malloc(graph->vertices * sizeof(int));
    for (int i = 0; i < graph->vertices; i++) {
        visited[i] = 0;
    }

    printf("DFS Traversal starting from vertex %d: ", startVertex);
    DFSUtil(graph, startVertex, visited);
    printf("\n");

    free(visited);
}

void BFS(struct Graph* graph, int startVertex) {
    int* visited = (int*)malloc(graph->vertices * sizeof(int));
    for (int i = 0; i < graph->vertices; i++) {
        visited[i] = 0;
    }

    struct Queue* queue = createQueue(graph->vertices);
    printf("BFS Traversal starting from vertex %d: ", startVertex);

    visited[startVertex] = 1;
    enqueue(queue, startVertex);

    while (!isEmpty(queue)) {
        int vertex = dequeue(queue);
        printf("%d ", vertex);

        for (int i = 0; i < graph->vertices; i++) {
            if (graph->adjacencyMatrix[vertex][i] == 1 && !visited[i]) {
                visited[i] = 1;
                enqueue(queue, i);
            }
        }
    }

    printf("\n");

    free(visited);
    free(queue->array);
    free(queue);
}

void topologicalSortUtil(struct Graph* graph, int vertex, int* visited, struct Stack* stack) {
    visited[vertex] = 1;

    for (int i = 0; i < graph->vertices; i++) {
        if (graph->adjacencyMatrix[vertex][i] == 1 && !visited[i]) {
            topologicalSortUtil(graph, i, visited, stack);
        }
    }

    push(stack, vertex);
}

void topologicalSort(struct Graph* graph) {
    struct Stack* stack = createStack(graph->vertices);
    int* visited = (int*)malloc(graph->vertices * sizeof(int));
    for (int i = 0; i < graph->vertices; i++) {
        visited[i] = 0;
    }

    printf("Topological Sorting: ");

    for (int i = 0; i < graph->vertices; i++) {
        if (!visited[i]) {
            topologicalSortUtil(graph, i, visited, stack);
        }
    }

    while (!isEmptyStack(stack)) {
        printf("%d ", pop(stack));
    }

    printf("\n");

    free(visited);
    free(stack->array);
    free(stack);
}

int main() {
    int choice, vertices, source, destination, startVertex;

    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &vertices);

    struct Graph* graph = createGraph(vertices);

    do {
        printf("\n------ Graph Traversal Techniques ------\n");
        printf("1. Add Edge\n");
        printf("2. Display Adjacency Matrix\n");
        printf("3. DFS Traversal\n");
        printf("4. BFS Traversal\n");
        printf("5. Topological Sorting\n");
        printf("6. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter source and destination vertices for the edge: ");
                scanf("%d %d", &source, &destination);
                addEdge(graph, source, destination);
                printf("Edge added between %d and %d.\n", source, destination);
                break;

            case 2:
                displayMatrix(graph);
                break;

            case 3:
                printf("Enter the starting vertex for DFS: ");
                scanf("%d", &startVertex);
                DFS(graph, startVertex);
                break;

            case 4:
                printf("Enter the starting vertex for BFS: ");
                scanf("%d", &startVertex);
                BFS(graph, startVertex);
                break;

            case 5:
                topologicalSort(graph);
                break;

            case 6:
                printf("Quitting the program.\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 6);

    return 0;
}
