#include <stdio.h>
#include <stdlib.h>

// Node structure for Red-Black Tree
struct Node {
    int data;
    char color; // 'R' for red, 'B' for black
    struct Node *left, *right, *parent;
};

struct Node *createNode(int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->color = 'R'; // New nodes are always red
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

// Function prototypes
void leftRotate(struct Node **root, struct Node *x);
void rightRotate(struct Node **root, struct Node *y);
void insertFixup(struct Node **root, struct Node *z);
void insertNode(struct Node **root, int data);
void transplant(struct Node **root, struct Node *u, struct Node *v);
struct Node *treeMinimum(struct Node *x);
void deleteFixup(struct Node **root, struct Node *x);
void deleteNode(struct Node **root, int data);
void inOrderTraversal(struct Node *root);

int main() {
    struct Node *root = NULL;
    int choice, data;

    do {
        printf("\n------ Red-Black Tree Operations ------\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display (In-Order Traversal)\n");
        printf("4. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                insertNode(&root, data);
                printf("Data %d inserted successfully.\n", data);
                break;

            case 2:
                printf("Enter data to delete: ");
                scanf("%d", &data);
                deleteNode(&root, data);
                printf("Data %d deleted successfully.\n", data);
                break;

            case 3:
                printf("In-Order Traversal:\n");
                inOrderTraversal(root);
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

// Left rotation in Red-Black Tree
void leftRotate(struct Node **root, struct Node *x) {
    struct Node *y = x->right;
    x->right = y->left;
    
    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

// Right rotation in Red-Black Tree
void rightRotate(struct Node **root, struct Node *y) {
    struct Node *x = y->left;
    y->left = x->right;

    if (x->right != NULL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

// Fix the Red-Black Tree properties after insertion
void insertFixup(struct Node **root, struct Node *z) {
    while (z->parent != NULL && z->parent->color == 'R') {
        if (z->parent == z->parent->parent->left) {
            struct Node *y = z->parent->parent->right;
            
            if (y != NULL && y->color == 'R') {
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(root, z);
                }

                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                rightRotate(root, z->parent->parent);
            }
        } else {
            struct Node *y = z->parent->parent->left;
            
            if (y != NULL && y->color == 'R') {
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }

                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                leftRotate(root, z->parent->parent);
            }
        }
    }

    (*root)->color = 'B'; // Root should always be black
}

// Insert a node into the Red-Black Tree
void insertNode(struct Node **root, int data) {
    struct Node *z = createNode(data);
    struct Node *y = NULL;
    struct Node *x = *root;

    while (x != NULL) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;

    if (y == NULL)
        *root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;

    insertFixup(root, z);
}

// Transplant a subtree in the Red-Black Tree
void transplant(struct Node **root, struct Node *u, struct Node *v) {
    if (u->parent == NULL)
        *root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v != NULL)
        v->parent = u->parent;
}

// Find the minimum node in a Red-Black Tree
struct Node *treeMinimum(struct Node *x) {
    while (x->left != NULL)
        x = x->left;
    return x;
}

// Fix the Red-Black Tree properties after deletion
void deleteFixup(struct Node **root, struct Node *x) {
    while (x != NULL && x != *root && x->color == 'B') {
        if (x == x->parent->left) {
            struct Node *w = x->parent->right;
            
            if (w != NULL && w->color == 'R') {
                w->color = 'B';
                x->parent->color = 'R';
                leftRotate(root, x->parent);
                w = x->parent->right;
            }

            if (w != NULL && w->left != NULL && w->left->color == 'B' && w->right != NULL && w->right->color == 'B') {
                w->color = 'R';
                x = x->parent;
            } else {
                if (w != NULL && w->right != NULL && w->right->color == 'B') {
                    if (w->left != NULL)
                        w->left->color = 'B';
                    w->color = 'R';
                    rightRotate(root, w);
                    w = x->parent->right;
                }

                if (w != NULL)
                    w->color = x->parent->color;
                x->parent->color = 'B';

                if (w != NULL && w->right != NULL)
                    w->right->color = 'B';

                leftRotate(root, x->parent);
                x = *root;
            }
        } else {
            struct Node *w = x->parent->left;
            
            if (w != NULL && w->color == 'R') {
                w->color = 'B';
                x->parent->color = 'R';
                rightRotate(root, x->parent);
                w = x->parent->left;
            }

            if (w != NULL && w->right != NULL && w->right->color == 'B' && w->left != NULL && w->left->color == 'B') {
                w->color = 'R';
                x = x->parent;
            } else {
                if (w != NULL && w->left != NULL && w->left->color == 'B') {
                    if (w->right != NULL)
                        w->right->color = 'B';
                    w->color = 'R';
                    leftRotate(root, w);
                    w = x->parent->left;
                }

                if (w != NULL)
                    w->color = x->parent->color;
                x->parent->color = 'B';

                if (w != NULL && w->left != NULL)
                    w->left->color = 'B';

                rightRotate(root, x->parent);
                x = *root;
            }
        }
    }

    if (x != NULL)
        x->color = 'B';
}

// Delete a node from the Red-Black Tree
void deleteNode(struct Node **root, int data) {
    struct Node *z = *root;
    while (z != NULL) {
        if (data < z->data)
            z = z->left;
        else if (data > z->data)
            z = z->right;
        else
            break; // Node with data found
    }

    if (z == NULL) {
        printf("Data %d not found in the tree.\n", data);
        return;
    }

    struct Node *y = z;
    char yOriginalColor = y->color;
    struct Node *x;

    if (z->left == NULL) {
        x = z->right;
        transplant(root, z, z->right);
    } else if (z->right == NULL) {
        x = z->left;
        transplant(root, z, z->left);
    } else {
        y = treeMinimum(z->right);
        yOriginalColor = y->color;
        x = y->right;

        if (y->parent == z)
            x->parent = y;
        else {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    free(z);

    if (yOriginalColor == 'B')
        deleteFixup(root, x);
}

// Perform in-order traversal of the Red-Black Tree
void inOrderTraversal(struct Node *root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("%d%c ", root->data, root->color);
        inOrderTraversal(root->right);
    }
}
