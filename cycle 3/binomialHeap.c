#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the Binomial Heap
struct Node {
    int data;
    int degree;  // Degree of the node
    struct Node *parent;
    struct Node *child;
    struct Node *sibling;
};

// Structure to represent a Binomial Heap
struct BinomialHeap {
    struct Node *head;
};

// Function to create a new node
struct Node *createNode(int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->degree = 0;
    newNode->parent = NULL;
    newNode->child = NULL;
    newNode->sibling = NULL;
    return newNode;
}

// Function to merge two Binomial Heaps
struct Node *mergeHeaps(struct Node *h1, struct Node *h2) {
    if (h1 == NULL)
        return h2;
    if (h2 == NULL)
        return h1;

    struct Node *mergedHeap = NULL;
    struct Node *temp1 = h1;
    struct Node *temp2 = h2;

    // Choose the node with smaller degree as the root of the merged heap
    if (temp1->degree <= temp2->degree) {
        mergedHeap = temp1;
        temp1 = temp1->sibling;
    } else {
        mergedHeap = temp2;
        temp2 = temp2->sibling;
    }

    struct Node *current = mergedHeap;

    // Merge the remaining nodes
    while (temp1 != NULL && temp2 != NULL) {
        if (temp1->degree <= temp2->degree) {
            current->sibling = temp1;
            temp1 = temp1->sibling;
        } else {
            current->sibling = temp2;
            temp2 = temp2->sibling;
        }
        current = current->sibling;
    }

    // Attach the remaining nodes, if any
    if (temp1 != NULL)
        current->sibling = temp1;
    else
        current->sibling = temp2;

    return mergedHeap;
}

// Function to link two Binomial Trees
void linkNodes(struct Node *root1, struct Node *root2) {
    root1->parent = root2;
    root1->sibling = root2->child;
    root2->child = root1;
    root2->degree++;
}

// Function to union two Binomial Heaps
struct Node *unionHeaps(struct Node *h1, struct Node *h2) {
    struct Node *mergedHeap = mergeHeaps(h1, h2);

    if (mergedHeap == NULL)
        return NULL;

    struct Node *prev = NULL;
    struct Node *current = mergedHeap;
    struct Node *next = mergedHeap->sibling;

    while (next != NULL) {
        if ((current->degree != next->degree) || (next->sibling != NULL && next->sibling->degree == current->degree)) {
            prev = current;
            current = next;
        } else {
            if (current->data <= next->data) {
                current->sibling = next->sibling;
                linkNodes(next, current);
            } else {
                if (prev == NULL)
                    mergedHeap = next;
                else
                    prev->sibling = next;
                linkNodes(current, next);
                current = next;
            }
        }

        next = current->sibling;
    }

    return mergedHeap;
}

// Function to insert a new key into the Binomial Heap
struct Node *insert(struct Node *heap, int key) {
    struct BinomialHeap *newHeap = (struct BinomialHeap *)malloc(sizeof(struct BinomialHeap));
    newHeap->head = createNode(key);

    return unionHeaps(heap, newHeap->head);
}

// Function to find the minimum key in the Binomial Heap
struct Node *findMin(struct Node *heap) {
    if (heap == NULL)
        return NULL;

    struct Node *minNode = heap;
    struct Node *current = heap;

    while (current != NULL) {
        if (current->data < minNode->data)
            minNode = current;
        current = current->sibling;
    }

    return minNode;
}

// Function to delete the minimum key from the Binomial Heap
struct Node *deleteMin(struct Node *heap) {
    if (heap == NULL)
        return NULL;

    struct Node *minNode = findMin(heap);
    struct Node *prev = NULL;
    struct Node *current = heap;

    // Find the parent of the minNode
    while (current != minNode) {
        prev = current;
        current = current->sibling;
    }

    // Remove minNode from the list
    if (prev == NULL)
        heap = minNode->sibling;
    else
        prev->sibling = minNode->sibling;

    // Reverse the order of minNode's children to form a new Binomial Heap
    struct Node *newHeap = NULL;
    struct Node *child = minNode->child;

    while (child != NULL) {
        struct Node *nextChild = child->sibling;
        child->sibling = newHeap;
        child->parent = NULL;
        newHeap = child;
        child = nextChild;
    }

    // Union the two heaps
    heap = unionHeaps(heap, newHeap);

    free(minNode);

    return heap;
}

// Function to display the Binomial Heap
void displayHeap(struct Node *heap) {
    while (heap != NULL) {
        printf("%d ", heap->data);
        heap = heap->sibling;
    }
    printf("\n");
}


int main() {
    struct Node *heapHead = NULL;  // Use a separate pointer for the heap head

    int choice, key;

    do {
        printf("\n------ Binomial Heap Operations ------\n");
        printf("1. Insert\n");
        printf("2. Delete Min\n");
        printf("3. Display\n");
        printf("4. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                heapHead = insert(heapHead, key);
                printf("Key %d inserted successfully.\n", key);
                break;

            case 2:
                heapHead = deleteMin(heapHead);
                printf("Minimum key deleted.\n");
                break;

            case 3:
                printf("Binomial Heap Root Nodes:\n");
                displayHeap(heapHead);  // Call the modified display function
                printf("\n");
                break;

            case 4:
                printf("Quitting the program.\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 4);

    return 0;
}
