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
node *createNewNode(){
    int data;
    printf("enter the data to be inserted : ");
    scanf("%d", &data);
    node * newnode = (node *)malloc((sizeof(node *)));
    newnode -> data = data;
    newnode -> link = NULL;
    return newnode;
}
void insertAtBeginning(){
    node *newnode = createNewNode();
    newnode->link = NULL;
    if(head==NULL) head = newnode;
    else {
        (newnode)->link = head;
        head = newnode;
    }
}
void insertAtEnd(){
    if(head==NULL) insertAtBeginning();
    else {
    node *newnode = createNewNode();
          node * temp = head;     
          while(temp->link !=NULL) temp = temp -> link;
          temp->link = newnode;
    }
}
void insertAtPosition(){
    int pos;
    printf("enter the position to insert : ");
    scanf("%d", &pos);
    if(pos<=1 || head==NULL) insertAtBeginning();
    else {
        node * newnode = createNewNode();
        node * temp = head;
        int count = 2;
        while(temp->link != NULL && count!=pos){
            temp = temp->link;
            count++;
        }
        newnode->link = temp->link;
        temp->link = newnode;
    }
}
void deleteAtBeginning(){
    if(head==NULL) printf("linked list is empty.\n");
    else head = head->link;
}
void deleteAtEnd(){
    if(head==NULL) printf("linked list is empty.\n");
    else {
        node * temp = head;
        node * dup = temp;
        if(temp->link == NULL) head = NULL;
        else {
            while(temp->link!=NULL) {
                dup = temp;
                temp = temp-> link;
            } dup-> link = NULL;
        }
    }
}
void deleteAtPosition(){
    int pos;
    if(head==NULL) printf("linked list is empty\n");
    else {
        printf("enter the position to insert : ");
        scanf("%d", &pos);

        if(pos<=1) deleteAtBeginning();
        else {
            node * temp = head;
            node * dup = temp;
            int count = 2;
            while(temp->link != NULL && count!=pos){
                dup = temp;
                temp = temp->link;
                count++;
            } 
            if(temp->link == NULL) dup->link = NULL;
            else dup->link = dup->link->link;
        }
    }
}
void display(){
    if(head == NULL) printf("linked list is empty.\n");
    else {
        node *temp = head;
        while(temp != NULL){
            printf("%d -> ", temp-> data);
            temp = temp->link;
        } printf("\n");
    }
}
void search(){
    int key, flag=0;
    printf("enter the element to search : ");
    scanf("%d", &key);

    node * temp = head;
    while(temp != NULL){
        if(temp->data == key){
            printf("element found.\n");
            return;
        } flag = 1;
        temp=temp->link;
    }
    printf("element not found.\n");
}
int main(){
    int choice;
    int data;
    while(true){
        printf("\n1.insert at beginning\n2.insert at end\n3.insert at position\n4.delete at beginning\n5.delete at end\n6.delete at position\n7.display\n8.search\n9.exit\nEnter the operation you want : ");
        scanf("%d", &choice);
        switch (choice){
            case 1: insertAtBeginning();break;
            case 2: insertAtEnd();break;
            case 3: insertAtPosition();break;
            case 4: deleteAtBeginning();break;
            case 5: deleteAtEnd();break;
            case 6: deleteAtPosition();break;
            case 7: display();break;
            case 8: search();break;
            case 9: return 0;
            default: printf("invalid input, please enter a valid input\n\n");
        }
    }
}