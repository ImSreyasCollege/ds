// name : sreyas
// roll.no : 53 
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *link;
} node;

node * head = NULL;

void insertAtBeginning(int data){
    node *newnode = (node *)(malloc(sizeof(node)));
    newnode->data = data;
    if(*head==NULL){
        *head = newnode;
    } else {
        (newnode)->link = *head;
        *head = newnode;
    }
}
void insertAtEnd(node * head, int data){
    node *newnode = (struct node *)(malloc(sizeof(node)));
}
void insertAtPosition(node * head, int data){
    node *newnode = (struct node *)(malloc(sizeof(node)));

}
void display(node **head){
    if(*head == NULL){
        printf("linked list is empty.");
    } else {
        node *temp = *head;
        while(temp != NULL){
            printf("%d -> ", temp-> data);
            temp = temp->link;
        }
        printf("\n");
    }
}
int main(){
    int choice;
    int data;
    node *head = NULL;
    while(true){
        printf("1.insert at beginning\n2.insert at end\n3.insert at position\n4.delete at beginning\n5.delete at end\n6.delete at position\n7.display\nEnter the operation you want : ");
        scanf("%d", &choice);

        switch (choice){
            case 1: printf("enter the data to be inserted : ");
            scanf("%d", &data);
            insertAtBeginning(head, data);
            break;
            // case 2: insertAtEnd();
            // break;
            // case 3: insertAtPosition();
            // break;
            // case 4: deleteAtBeginning();
            // break;
            // case 5: deleteAtEnd();
            // break;
            // case 6: deleteAtPosition();
            // break;
            case 7: display(head);
            break;
            case 8: return 0;
            default: printf("invalid input, please enter a valid input\n\n");
        }
    }
}