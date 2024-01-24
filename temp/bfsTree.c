#include <stdio.h>
#include <stdlib.h>

struct node {
    int data; 
    struct node *left;
    struct node *right;
};

struct node *createNode(int val){
	struct node *root = (struct node *)malloc(sizeof(struct node));
	root->data = val;
	root->left = root->right = NULL;
	return root;
}
struct node *insert(struct node *root, int val){
	if(root == NULL) return createNode(val);
	else if(val < root->data) root->left = insert(root->left, val);
	else if(val > root->data) root->right = insert(root->right, val);
	else printf("\nValue already in tree.\n");
	return root;
}
int rear = -1, front = -1;
void bfs(struct node *root, struct node **q){
	if(root == NULL) return;	
	printf("%d ", root->data);
	if(front == -1 && rear == -1){
		q[++rear] = root;
		++front;
	}
	if(root->left != NULL) q[++rear] = root->left;
	if(root->right != NULL) q[++rear] = root->right;
	if(front < rear) bfs(q[++front], q);
}
void display(struct node *root){
	if(root != NULL){
		display(root->left);
		printf("%d ", root->data);
		display(root->right);
	}
}
void main(){
    int ch;
    struct node *root = NULL;
    while(1){
        printf("1. Insert \n2. BFS \n3. Exit\nEnter you choice : ");
        scanf("%d", &ch);
        switch(ch){
            case 1: {
                int val;
                printf("Enter the data to insert : ");
                scanf("%d", &val);
                root = insert(root, val);
		printf("\n");
		display(root);
		printf("\n");
		break;
            }
	    case 2: {
		printf("\nBFS : ");
		struct node *q[50];
		bfs(root, q);
		printf("\n");
		break;
	    }
	    case 3 : return;
		     break;
	    default : printf("\nInvalide choice\n");
        }
    }
    return;
}
