#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
};
struct node *createNode(int data){
    struct node *newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->left = newnode->right = NULL;
    return newnode;
}
struct node *insert(struct node *root, int data){
    if(root == NULL) return createNode(data);
    if(root->data < data) root->right = insert(root->right, data);
    else root->left = insert(root->left, data);
    return root;
}
void display(struct node *root){
    if(root != NULL){
        display(root->left);
        printf("%d ", root->data);
        display(root->right);
    }
}
int n;
int front = -1, rear = -1;
void BFS(struct node *root, struct node **q){
    if(front == -1 && rear == -1){
        ++front;
        q[++rear] = root;
    }
    if(root->left != NULL) q[++rear] = (root->left);
    if(root->right != NULL) q[++rear] = (root->right);
    if(rear == n - 1) return;
    BFS(q[++front], q);
}
struct node *findMin(struct node *root){
    while(root->left != NULL) root = root->left;
    return root;
}
struct node *delete(struct node *root, int val){
    if(root == NULL) return root;
    if(root->data < val) root->right = delete(root->right, val);
    else if(root->data > val) root->left = delete(root->left, val);
    else {
        if(root->left == NULL) return root->right;
        else if(root->right == NULL) return root->left;
        struct node *temp = findMin(root->right);
        root->data = temp->data;
        root->right = delete(root->right, temp->data);
    }
    return root;
}
void main(){
    int data;
    struct node *root = NULL;
    printf("Enter the no.of nodes to insert : ");
    scanf("%d", &n);
    printf("Enter the value : ");
    for(int i=0; i<n; i++){
        scanf("%d", &data);
        root = insert(root, data);
    }
    printf("DFS traversal : ");
    display(root);
    printf("\n");

    struct node *q[n];
    printf("BFS traversal : ");
    BFS(root, q);
    for(int i=0; i< n; i++){
        printf("%d ", q[i]->data);
    }

    int d, val;
    printf("Enter the no.of data to be deleted : ");
    scanf("%d", &d);
    printf("Enter the data : ");
    for(int i=0; i<d; i++){
        scanf("%d", &val);
        root = delete(root, val);
    }
    printf("DFS traversal : ");
    display(root);
    printf("\n");

    return;
}