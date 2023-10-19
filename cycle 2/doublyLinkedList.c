#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
    struct node *prev;
};
struct node *head = NULL;
struct node *createNewNode(){
    struct node *newnode = (struct node *)(malloc(sizeof(struct node *)));
    newnode->next = NULL;
    newnode->prev = NULL;
    printf("enter the element : ");
    scanf("%d", &newnode->data);
    return newnode;
}
void insertAtBeginning(){
    struct node *newnode = createNewNode();
    if(head == NULL){
        head = newnode;
    } else {
        newnode->next = head;
        head->prev = newnode;
        head = newnode;
    }
}
void insertAtEnd(){
    if(head == NULL){
        insertAtBeginning();
    } else {
        struct node *newnode = createNewNode();
        struct node *temp = head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        newnode->prev = temp;
        temp->next = newnode;
    }
}
void insertAtPosition(){
    printf("enter the position to insert : ");
    
}
void deleteAtBeginning(){

}
void deleteAtEnd(){

}
void deleteAtPosition(){

}
void search(){

}
void display(){
    struct node *temp = head;
    while(temp != NULL){
        printf("%d->", temp->data);
        temp = temp->next;
    }
}
int main(){
    int opt;
    while(1){
        printf("\n1.insert at beginning\n2.insert at end\n3.insert at position\n4.delete at beginning\n5.delete at end\n6.delete at position\n7.display\n8.search\n9.exit\nEnter the operation you want : ");
        scanf("%d", &opt);
        switch(opt){
            case 1:insertAtBeginning();break;
            case 2:insertAtEnd();break;
            case 3:insertAtPosition();break;
            case 4:deleteAtBeginning();break;
            case 5:deleteAtEnd();break;
            case 6:deleteAtPosition();break;
            case 7:display();break;
            case 8:search();break;
            case 9:return 0;
            default: printf("invalid option.\n");
        }
    }
}