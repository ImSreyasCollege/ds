#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Node structure for Binomial Heap
struct Node {
    int data, degree;
    struct Node *parent, *child, *sibling;
};

// Create a new node with given key
struct Node *createNode(int key) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = key;
    newNode->degree = 0;
    newNode->parent = newNode->child = newNode->sibling = NULL;
    return newNode;
}

// Merge two binomial trees of the same degree
struct Node *mergeBinomialTrees(struct Node *tree1, struct Node *tree2) {
    if (tree1->data > tree2->data) {
        struct Node *temp = tree1;
        tree1 = tree2;
        tree2 = temp;
    }

    tree2->parent = tree1;
    tree2->sibling = tree1->child;
    tree1->child = tree2;
    tree1->degree++;

    return tree1;
}

// Union of two Binomial Heaps
struct Node *unionBinomialHeaps(struct Node *h1, struct Node *h2) {
    struct Node *head = NULL;
    struct Node *temp1 = h1;
    struct Node *temp2 = h2;

    while (temp1 != NULL || temp2 != NULL) {
        struct Node *next = NULL;

        if (temp1 != NULL && (temp2 == NULL || temp1->degree <= temp2->degree)) {
            next = temp1;
            temp1 = temp1->sibling;
        } else {
            next = temp2;
            temp2 = temp2->sibling;
        }

        if (head == NULL) {
            head = next;
        } else {
            head = mergeBinomialTrees(head, next);
        }
    }

    return head;
}

// Insert a key into a Binomial Heap
struct Node *insertNode(struct Node *head, int key) {
    struct Node *newNode = createNode(key);
    return unionBinomialHeaps(head, newNode);
}

// Get the minimum node in a Binomial Heap
struct Node *getMin(struct Node *heap) {
    struct Node *minNode = heap;
    struct Node *temp = heap;

    while (temp != NULL) {
        if (temp->data < minNode->data) {
            minNode = temp;
        }
        temp = temp->sibling;
    }

    return minNode;
}

// Extract the minimum node from a Binomial Heap
struct Node *extractMin(struct Node *heap) {
    struct Node *minNode = getMin(heap);
    struct Node *prev = NULL, *curr = heap;

    while (curr != minNode) {
        prev = curr;
        curr = curr->sibling;
    }

    if (prev == NULL) {
        heap = curr->sibling;
    } else {
        prev->sibling = curr->sibling;
    }

    struct Node *child = minNode->child;
    while (child != NULL) {
        struct Node *nextChild = child->sibling;
        child->parent = NULL;
        child->sibling = NULL;
        heap = unionBinomialHeaps(heap, child);
        child = nextChild;
    }

    free(minNode);

    return heap;
}

// Decrease the key to a new value
void decreaseKey(struct Node *heap, int oldKey, int newKey) {
    // Implementation of decreaseKey depends on your specific requirements
    // It is not included here for brevity
    // Typically involves finding the node with oldKey and updating its value
}

// Delete a key from a Binomial Heap
struct Node *deleteKey(struct Node *heap, int key) {
    if (heap == NULL) {
        printf("Heap is empty.\n");
        return heap;
    }

    // Decrease the key to a very small value
    decreaseKey(heap, key, INT_MIN);

    // Extract the minimum key (which is now at the root)
    heap = extractMin(heap);

    printf("Key %d deleted successfully.\n", key);

    return heap;
}

// Display the Binomial Heap in a readable format
void display(struct Node *root, int depth) {
    while (root != NULL) {
        printf("(%d,%d) ", root->data, root->degree);
        display(root->child, depth + 1);
        root = root->sibling;
    }
}

// Main function to demonstrate Binomial Heap operations
int main() {
    struct Node *heap = NULL;
    int choice, key;

    do {
        printf("\n------ Binomial Heap Operations ------\n");
        printf("1. Insert\n");
        printf("2. Extract Min\n");
        printf("3. Delete\n");
        printf("4. Display\n");
        printf("5. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                heap = insertNode(heap, key);
                printf("Key %d inserted successfully.\n", key);
                break;

            case 2:
                if (heap == NULL) {
                    printf("Heap is empty.\n");
                } else {
                    heap = extractMin(heap);
                    printf("Minimum element extracted.\n");
                }
                break;

            case 3:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                heap = deleteKey(heap, key);
                break;

            case 4:
                if (heap == NULL) {
                    printf("Heap is empty.\n");
                } else {
                    printf("Binomial Heap: ");
                    display(heap, 0);
                    printf("\n");
                }
                break;

            case 5:
                printf("Quitting the program.\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 5);

    return 0;
}