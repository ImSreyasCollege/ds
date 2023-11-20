#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

struct Stack {
    int items[MAX_VERTICES];
    int top;
};

struct Graph {
    int vertices;
    int** adjacencyMatrix;
};

// Function prototypes
struct Stack* createStack();
void push(struct Stack* stack, int item);
int pop(struct Stack* stack);
void dfs(struct Graph* graph, int vertex, int* visited, struct Stack* stack);
struct Graph* transposeGraph(struct Graph* graph);
void printSCCs(struct Graph* graph);

int main() {
    struct Graph* graph = NULL;
    int choice, vertices, edges, i, j, src, dest;

    do {
        printf("\nMenu:\n");
        printf("1. Create Graph\n");
        printf("2. Find Strongly Connected Components\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the number of vertices: ");
                scanf("%d", &vertices);

                graph = (struct Graph*)malloc(sizeof(struct Graph));
                graph->vertices = vertices;
                graph->adjacencyMatrix = (int**)malloc(vertices * sizeof(int*));

                for (i = 0; i < vertices; i++) {
                    graph->adjacencyMatrix[i] = (int*)malloc(vertices * sizeof(int));
                    for (j = 0; j < vertices; j++) {
                        graph->adjacencyMatrix[i][j] = 0;
                    }
                }

                printf("Enter the number of edges: ");
                scanf("%d", &edges);

                printf("Enter the edges (src dest):\n");
                for (i = 0; i < edges; i++) {
                    scanf("%d %d", &src, &dest);
                    graph->adjacencyMatrix[src][dest] = 1;
                }
                break;

            case 2:
                if (graph == NULL) {
                    printf("Graph not created. Please create a graph first.\n");
                    break;
                }

                printSCCs(graph);
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

struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    return stack;
}

void push(struct Stack* stack, int item) {
    stack->items[++stack->top] = item;
}

int pop(struct Stack* stack) {
    if (stack->top == -1) {
        return -1; // Empty stack
    }
    return stack->items[stack->top--];
}

void dfs(struct Graph* graph, int vertex, int* visited, struct Stack* stack) {
    visited[vertex] = 1;

    for (int i = 0; i < graph->vertices; i++) {
        if (graph->adjacencyMatrix[vertex][i] && !visited[i]) {
            dfs(graph, i, visited, stack);
        }
    }

    push(stack, vertex);
}

struct Graph* transposeGraph(struct Graph* graph) {
    struct Graph* transposedGraph = (struct Graph*)malloc(sizeof(struct Graph));
    transposedGraph->vertices = graph->vertices;
    transposedGraph->adjacencyMatrix = (int**)malloc(graph->vertices * sizeof(int*));

    for (int i = 0; i < graph->vertices; i++) {
        transposedGraph->adjacencyMatrix[i] = (int*)malloc(graph->vertices * sizeof(int));
        for (int j = 0; j < graph->vertices; j++) {
            transposedGraph->adjacencyMatrix[i][j] = graph->adjacencyMatrix[j][i];
        }
    }

    return transposedGraph;
}

void printSCCs(struct Graph* graph) {
    struct Stack* stack = createStack();
    int* visited = (int*)malloc(graph->vertices * sizeof(int));

    for (int i = 0; i < graph->vertices; i++) {
        visited[i] = 0;
    }

    for (int i = 0; i < graph->vertices; i++) {
        if (!visited[i]) {
            dfs(graph, i, visited, stack);
        }
    }

    struct Graph* transposedGraph = transposeGraph(graph);

    for (int i = 0; i < graph->vertices; i++) {
        visited[i] = 0;
    }

    printf("Strongly Connected Components:\n");

    while (stack->top != -1) {
        int vertex = pop(stack);

        if (!visited[vertex]) {
            struct Stack* sccStack = createStack();
            dfs(transposedGraph, vertex, visited, sccStack);

            printf("{ ");
            while (sccStack->top != -1) {
                int sccVertex = pop(sccStack);
                printf("%d ", sccVertex);
            }
            printf("}\n");

            free(sccStack);
        }
    }

    free(stack);
    free(visited);
    free(transposedGraph);
}
