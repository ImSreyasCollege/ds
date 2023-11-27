#include <stdio.h>
#include <stdlib.h>

// Structure to represent a disjoint-set element
struct DisjointSet {
    int parent; // Parent of the element
    int rank;   // Rank of the element (used for union by rank)
};

// Function to make a set with a single element
void makeSet(struct DisjointSet* sets, int size) {
    for (int i = 0; i < size; i++) {
        sets[i].parent = i;
        sets[i].rank = 0;
    }
}

// Function to find the representative (root) of a set
int find(struct DisjointSet* sets, int i) {
    if (sets[i].parent != i) {
        // Path compression: Set the parent of i to its root
        sets[i].parent = find(sets, sets[i].parent);
    }
    return sets[i].parent;
}

// Function to union two sets by rank
void unionSets(struct DisjointSet* sets, int x, int y) {
    int rootX = find(sets, x);
    int rootY = find(sets, y);

    // Union by rank: Attach the smaller rank tree under the root of the higher rank tree
    if (sets[rootX].rank < sets[rootY].rank) {
        sets[rootX].parent = rootY;
    } else if (sets[rootX].rank > sets[rootY].rank) {
        sets[rootY].parent = rootX;
    } else {
        sets[rootY].parent = rootX;
        sets[rootX].rank++;
    }
}

int main() {
    int size;
    
    printf("Enter the size of the disjoint-set: ");
    scanf("%d", &size);

    struct DisjointSet* sets = (struct DisjointSet*)malloc(size * sizeof(struct DisjointSet));
    makeSet(sets, size);

    int choice, x, y;
    
    while (1) {
        printf("\nOperations:\n");
        printf("1. Union (Merge two sets)\n");
        printf("2. Find (Check if elements are in the same set)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter two elements to merge: ");
            scanf("%d %d", &x, &y);
            if (x < 0 || x >= size || y < 0 || y >= size) {
                printf("Invalid elements\n");
            } else {
                unionSets(sets, x, y);
                printf("Union performed.\n");
            }
        } else if (choice == 2) {
            printf("Enter two elements to check if they are in the same set: ");
            scanf("%d %d", &x, &y);
            if (x < 0 || x >= size || y < 0 || y >= size) {
                printf("Invalid elements\n");
            } else {
                if (find(sets, x) == find(sets, y)) {
                    printf("They are in the same set.\n");
                } else {
                    printf("They are in different sets.\n");
                }
            }
        } else if (choice == 3) {
            break;
        } else {
            printf("Invalid choice\n");
        }
    }

    free(sets);
    return 0;
}
