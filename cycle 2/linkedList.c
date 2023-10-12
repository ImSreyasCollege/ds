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
node *createNewNode(int data){
    node * newnode = (node *)malloc((sizeof(node *)));
    newnode -> data = data;
    newnode -> link = NULL;
    return newnode;
}
//insertion

//beginning
void insertAtBeginning(int data){
    node *newnode = createNewNode(data);
    newnode->data = data;
    newnode->link = NULL;
    if(head==NULL){
        head = newnode;
    } else {
        (newnode)->link = head;
        head = newnode;
    }
}
//end
void insertAtEnd(int data){
    node *newnode = createNewNode(data);
    if(head==NULL) insertAtBeginning(data);
    else {
               
    }
}
//position
void insertAtPosition(int data){
    
}
//deletion 

//beginning
void deleteAtBeginning(){

}
void deleteAtEnd(){

}
void deleteAtPosition(){

}
void display(){
    if(head == NULL){
        printf("linked list is empty.");
    } else {
        node *temp = head;
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
    while(true){
        printf("1.insert at beginning\n2.insert at end\n3.insert at position\n4.delete at beginning\n5.delete at end\n6.delete at position\n7.display\nEnter the operation you want : ");
        scanf("%d", &choice);

        switch (choice){
            case 1: printf("enter the data to be inserted : ");
            scanf("%d", &data);
            insertAtBeginning(data);
            break;
            case 2: insertAtEnd(data);
            break;
            case 3: insertAtPosition(data);
            break;
            case 4: deleteAtBeginning();
            break;
            case 5: deleteAtEnd();
            break;
            case 6: deleteAtPosition();
            break;
            case 7: display();
            break;
            case 8: return 0;
            default: printf("invalid input, please enter a valid input\n\n");
        }
    }
}