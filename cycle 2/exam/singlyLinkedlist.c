#include <stdio.h>
#include <stdlib.h>

typedef struct nodeS{
    int data;
    struct nodeS* link;
}node;

int getData(){
    int data;
    printf("Enter the data to insert : ");
    scanf("%d", &data);
    return data;
}
node *createNode(int data){
    node *newnode = (node*) malloc(sizeof(node*));
    newnode->data = data;
    newnode->link = NULL;
    return newnode;
}
void insertAtBeg(node** head, node** tail){
    int data = getData();
    node* newnode = createNode(data);
    if(*head != NULL){
        newnode->link = *head;
    } else {
        *tail = newnode;
    }
    *head = newnode;
}
void insertAtEnd(node** head, node** tail){
    if(*head == NULL) insertAtBeg(head, tail);
    else {
        int data = getData();
        node* newnode = createNode(data);
        (*tail)->link = newnode;
        *tail = newnode;
    }
}
void insertAtPos(node** head, node** tail){
    int pos;
    printf("enter the position : ");
    scanf("%d", &pos);
    if(pos < 1) printf("invalid position.\n");
    else if(pos == 1) insertAtBeg(head, tail);
    else {
        int data = getData();
        node* newnode = createNode(data);
        int current = 1;
        node *temp = *head;
        while(temp != NULL && current != pos-1){
            current++;
            temp = temp->link;
        }
        if(temp->link == NULL) printf("invalid position.\n");
        else {
            newnode->link = temp->link;
            temp->link = newnode;
        }
    }
}
void display(node *head){
    node *temp = head;
    while(temp != NULL){
        printf("%d->", temp->data);
        temp = (temp)->link;
    }
}

void main(){
    int choice;
    node *head = NULL;
    node *tail = NULL;
    do{
        printf("\n1. insert at beginning\n2. insert at end\n3. insert at position.\nEnter your operation : ");
        scanf("%d", &choice);
        switch(choice){
            case 1: insertAtBeg(&head, &tail);
            break;
            case 2: insertAtEnd(&head, &tail);
            break;
            case 3: insertAtPos(&head, &tail);
            break;
            // case 4: deleteAtBeg(&head, &tail);
            // break;
            // case 5: deleteAtEnd(&head, &tail);
            // break;
            // case 6: deleteAtPos(&head, &tail);
            // break;
            case 7: display(head);
            break;
            case 8: printf("\nExiting the program.");
            break;
            default: printf("\nInvalid input.\n");
        }
    } while(choice != 8);
}