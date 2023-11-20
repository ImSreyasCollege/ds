#include <stdio.h>
#include <stdlib.h>

#define MAX_KEYS 3
#define MAX_CHILDREN 4

struct BTreeNode {
    int keys[MAX_KEYS];
    struct BTreeNode *children[MAX_CHILDREN];
    int keyCount;
    int isLeaf;
};

struct BTreeNode *createNode() {
    struct BTreeNode *newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
    newNode->keyCount = 0;
    newNode->isLeaf = 1;
    for (int i = 0; i < MAX_CHILDREN; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

void splitChild(struct BTreeNode *parent, int index, struct BTreeNode *child) {
    struct BTreeNode *newNode = createNode();
    newNode->isLeaf = child->isLeaf;
    newNode->keyCount = MAX_KEYS / 2;

    for (int i = 0; i < MAX_KEYS / 2; i++) {
        newNode->keys[i] = child->keys[i + MAX_KEYS / 2];
    }

    if (!child->isLeaf) {
        for (int i = 0; i < MAX_CHILDREN / 2; i++) {
            newNode->children[i] = child->children[i + MAX_CHILDREN / 2];
        }
    }

    child->keyCount = MAX_KEYS / 2;
    parent->children[parent->keyCount + 1] = NULL;

    for (int i = parent->keyCount; i > index; i--) {
        parent->keys[i] = parent->keys[i - 1];
        parent->children[i] = parent->children[i - 1];
    }

    parent->keys[index] = child->keys[MAX_KEYS / 2 - 1];
    parent->children[index + 1] = newNode;
    parent->keyCount++;
}

void insertNonFull(struct BTreeNode *node, int key) {
    int i = node->keyCount - 1;

    if (node->isLeaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }

        node->keys[i + 1] = key;
        node->keyCount++;
    } else {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }

        i++;
        if (node->children[i]->keyCount == MAX_KEYS) {
            splitChild(node, i, node->children[i]);
            if (key > node->keys[i]) {
                i++;
            }
        }

        insertNonFull(node->children[i], key);
    }
}

struct BTreeNode *search(struct BTreeNode *node, int key) {
    int i = 0;
    while (i < node->keyCount && key > node->keys[i]) {
        i++;
    }

    if (i < node->keyCount && key == node->keys[i]) {
        return node;
    }

    if (node->isLeaf) {
        return NULL;
    }

    return search(node->children[i], key);
}

struct BTreeNode *findPredecessor(struct BTreeNode *node) {
    while (!node->isLeaf) {
        node = node->children[node->keyCount];
    }
    return node;
}

struct BTreeNode *removeKey(struct BTreeNode *node, int key) {
    int i = 0;
    while (i < node->keyCount && key > node->keys[i]) {
        i++;
    }

    if (i < node->keyCount && key == node->keys[i]) {
        if (node->isLeaf) {
            for (int j = i; j < node->keyCount - 1; j++) {
                node->keys[j] = node->keys[j + 1];
            }
            node->keyCount--;
            return node;
        } else {
            struct BTreeNode *predecessor = findPredecessor(node->children[i]);
            int predecessorKey = predecessor->keys[predecessor->keyCount - 1];
            node->keys[i] = predecessorKey;
            node->children[i] = removeKey(node->children[i], predecessorKey);
            return node;
        }
    } else {
        if (node->isLeaf) {
            printf("Key %d not found in the tree.\n", key);
            return node;
        }

        int childIndex = i;
        if (node->children[childIndex]->keyCount == MAX_KEYS / 2) {
            // If the child has only t-1 keys, we need to ensure it has enough keys for the deletion
            if (childIndex > 0 && node->children[childIndex - 1]->keyCount > MAX_KEYS / 2 - 1) {
                // Borrow from the left sibling
                node = borrowFromLeft(node, childIndex);
            } else if (childIndex < node->keyCount && node->children[childIndex + 1]->keyCount > MAX_KEYS / 2 - 1) {
                // Borrow from the right sibling
                node = borrowFromRight(node, childIndex);
            } else {
                // Merge with a sibling
                node = mergeWithSibling(node, childIndex);
            }
        }

        node->children[childIndex] = removeKey(node->children[childIndex], key);
        return node;
    }
}

struct BTreeNode *borrowFromLeft(struct BTreeNode *node, int childIndex) {
    // Borrow a key from the left sibling
    struct BTreeNode *child = node->children[childIndex];
    struct BTreeNode *leftSibling = node->children[childIndex - 1];

    // Make space for the borrowed key in the child node
    for (int i = child->keyCount; i > 0; i--) {
        child->keys[i] = child->keys[i - 1];
    }

    // Move the key from the parent to the child
    child->keys[0] = node->keys[childIndex - 1];

    // If the child is not a leaf, move the last child of the left sibling to the child's first position
    if (!child->isLeaf) {
        for (int i = child->keyCount + 1; i > 0; i--) {
            child->children[i] = child->children[i - 1];
        }
        child->children[0] = leftSibling->children[leftSibling->keyCount];
    }

    // Move the last key from the left sibling to the parent
    node->keys[childIndex - 1] = leftSibling->keys[leftSibling->keyCount - 1];

    // Update key counts
    child->keyCount++;
    leftSibling->keyCount--;

    return node;
}

struct BTreeNode *borrowFromRight(struct BTreeNode *node, int childIndex) {
    // Borrow a key from the right sibling
    struct BTreeNode *child = node->children[childIndex];
    struct BTreeNode *rightSibling = node->children[childIndex + 1];

    // Move the key from the parent to the child
    child->keys[child->keyCount] = node->keys[childIndex];

    // If the child is not a leaf, move the first child of the right sibling to the child's last position
    if (!child->isLeaf) {
        child->children[child->keyCount + 1] = rightSibling->children[0];
    }

    // Move the first key from the right sibling to the parent
    node->keys[childIndex] = rightSibling->keys[0];

    // Shift keys in the right sibling
    for (int i = 0; i < rightSibling->keyCount - 1; i++) {
        rightSibling->keys[i] = rightSibling->keys[i + 1];
    }

    // If the right sibling is not a leaf, shift children
    if (!rightSibling->isLeaf) {
        for (int i = 0; i < rightSibling->keyCount; i++) {
            rightSibling->children[i] = rightSibling->children[i + 1];
        }
    }

    // Update key counts
    child->keyCount++;
    rightSibling->keyCount--;

    return node;
}

struct BTreeNode *mergeWithSibling(struct BTreeNode *node, int childIndex) {
    // Merge the child with its right sibling
    struct BTreeNode *child = node->children[childIndex];
    struct BTreeNode *rightSibling = node->children[childIndex + 1];

    // Move the key from the parent to the child
    child->keys[child->keyCount] = node->keys[childIndex];

    // Copy keys from the right sibling to the child
    for (int i = 0; i < rightSibling->keyCount; i++) {
        child->keys[child->keyCount + 1 + i] = rightSibling->keys[i];
    }

    // If the child is not a leaf, copy children from the right sibling to the child
    if (!child->isLeaf) {
        for (int i = 0; i <= rightSibling->keyCount; i++) {
            child->children[child->keyCount + 1 + i] = rightSibling->children[i];
        }
    }

    // Shift keys in the parent
    for (int i = childIndex; i < node->keyCount - 1; i++) {
        node->keys[i] = node->keys[i + 1];
        node->children[i + 1] = node->children[i + 2];
    }

    // Update key counts
    child->keyCount += 1 + rightSibling->keyCount;
    node->keyCount--;

    // Free the memory of the right sibling
    free(rightSibling);

    return node;
}

void delete(struct BTreeNode **root, int key) {
    struct BTreeNode *node = *root;
    if (!node) {
        printf("Tree is empty.\n");
        return;
    }

    *root = removeKey(node, key);

    // If the root has no keys, replace it with its only child
    if ((*root)->keyCount == 0 && !(*root)->isLeaf) {
        struct BTreeNode *newRoot = (*root)->children[0];
        free(*root);
        *root = newRoot;
    }

    printf("Key %d deleted successfully.\n", key);
}

void display(struct BTreeNode *node, int level) {
    if (node != NULL) {
        int i;
        for (i = node->keyCount - 1; i >= 0; i--) {
            display(node->children[i + 1], level + 1);

            for (int j = 0; j < level; j++) {
                printf("    ");
            }
            printf("%d\n", node->keys[i]);
        }

        display(node->children[i + 1], level + 1);
    }
}

int main() {
    struct BTreeNode *root = createNode();
    int choice, key;

    do {
        printf("\n------ B-Tree Operations ------\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display\n");
        printf("4. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insertNonFull(root, key);
                printf("Key %d inserted successfully.\n", key);
                break;

            case 2:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                delete(&root, key);
                break;

            case 3:
                printf("B-Tree:\n");
                display(root, 0);
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
    
