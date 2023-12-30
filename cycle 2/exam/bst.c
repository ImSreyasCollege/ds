#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node* left;
    struct node* right;
};

struct node *createNode(int data){
    struct node *newnode = (struct node*)malloc(sizeof(struct node*));
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}
struct node *insert(struct node *current, int value){
    if(current==NULL) return createNode(value);
    if(value > current->data){
        current->right = insert(current->right, value);
    } else if(value < current->data){
        current->left = insert(current->left, value);
    }
    return current;
}

void display(struct node *root){
    if(root != NULL){
        display(root->left);
        printf("%d ", root->data);
        display(root->right);
    }
}

struct node *findMin(struct node *root){
    while(root->left != NULL){
        root = root->left;
    }
    return root;
}

struct node *delete(struct node *root, int value){
    if(root == NULL) return root;
    if(root->data < value){
        root->right = delete(root->right, value);
    } else if(root->data > value){
        root->left = delete(root->left, value);
    } else {
        if(root->left == NULL){
            return root->right;
        } else if(root->right == NULL){
            return root->left;
        }
        struct node *temp = findMin(root);
        root->data = temp->data;
        root->right = delete(root->right, temp->data);
    }
    return root;
}

int main(){
    struct node *root = NULL;
    int ch, data;
    while(1){
        printf("\n1.insert\n2.delete\n3.display\n4.exit\nEnter the operation to perform : ");
        scanf("%d", &ch);
        switch(ch){
            case 1 : 
                printf("enter the data to insert : ");
                scanf("%d", &data);
                root = insert(root, data);
                break;
            case 2 :
                printf("enter the value to be deleted : ");
                scanf("%d", &data);
                root = delete(root, data);
                break;
            case 3 :
                display(root);
                break;
            case 4 : 
                return 0;
                break;
            default : printf("enter a valid choice.\n");
        }
    }
}