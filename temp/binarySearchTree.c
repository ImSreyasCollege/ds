#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
};
struct node *createNode(int val){
    struct node *newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = val;
    newnode->left = newnode->right = NULL;
    return newnode;
}
struct node *insert(struct node *root, int val){
    if(root==NULL) return createNode(val);
    if(val < root->data) root->left = insert(root->left, val);
    else if(val > root-> data) root->right = insert(root->right, val);
    else printf("\nValue already in tree.\n");
    return root;
}
struct node *findMin(struct node * root){
    while(root->left != NULL) root->left;
    return root;
}
struct node *delete(struct node *root, int val){
    if(root == NULL) return root;
    if(val < root->data) root->left = delete(root->left, val);
    else if(val > root->data) root->right = delete(root->right, val);
    else {
        if(root->left == NULL) root = root->right;
        else if(root->right == NULL) root = root->left;
        else {
            struct node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = delete(root->right, temp->data);
        }
    }
    return root;
}
void display(struct node *root){
    if(root != NULL){
        display(root->left);
        printf("%d ", root->data);
        display(root->right);
    }
}
void main(){
    int ch, val;
    struct node *root = NULL;
    while(1){
        printf("\n1. insert\n2. delete\n3. display\n4. exit\nEnter the operation : ");
        scanf("%d", &ch);
        switch(ch){
            case 1: {
                printf("Enter the value : ");
                scanf("%d", &val);
                root = insert(root, val);
                printf("\n%d inserted successfully.\n", val);
                break;
            }
            case 2: {
                int deleteVal;
                printf("\nEnter the data to delete : ");
                scanf("%d", &deleteVal);
                root = delete(root, deleteVal);
                printf("\n%d deleted from tree.\n", deleteVal);
                break;
            }
            case 3: {
                if(root == NULL) printf("\nTree is empty");
                else printf("\nIn order traversal : ");
                display(root);
                printf("\n");
                break;
            }
            case 4: return;
        }
    }
}