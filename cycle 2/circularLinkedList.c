#include <stdio.h>
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
    struct node *newnode = createNewNode();
}
void insertAtPosition(){

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
    while(temp != head){
        temp = temp->next;
        printf("%d->", temp->data);
    }
}
void main(){
    int opt;
    while(1){
        printf("enter the operation (1.insert at beginning 2.insert at end 3.insert at position 4.delete at beginning 5.delete at end 6.delete at position 7.search 8.display 9.exit) : ");
        scanf("%d", &opt);
        switch(opt){
            case 1:insertAtBeginning();break;
            case 2:insertAtEnd();break;
            case 3:insertAtPosition();break;
            case 4:deleteAtBeginning();break;
            case 5:deleteAtEnd();break;
            case 6:deleteAtPosition();break;
            case 7:deleteAtPosition();break;
            case 8:deleteAtPosition();break;
            case 9:return 0;
            default: printf("invalid option.\n");
        }
    }
}