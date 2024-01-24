#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
    int data;
    struct node *next;
    struct node *prev;
};
struct node *head = NULL;
int count=0;
int getData(){
    int data;
    printf("Enter the data to insert : ");
    scanf("%d", &data);
    return data;
}
int getPosition(){
    int pos;
    printf("Enter the position : ");
    scanf("%d", &pos);
    return pos;
}
struct node *createNode(){
    int data = getData();
    struct node *newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->prev = newnode->next = NULL;
    return newnode;
}
void insertAtHead(){
    struct node *newnode = createNode();
    if(head == NULL) {
        head = newnode;
        newnode->next = newnode;
        newnode->prev = newnode;
    } else {
        newnode->next = head;
        newnode->prev = head->prev;
        head->prev->next = newnode;
        head->prev = newnode;
        head = newnode;
    }
    count++;
    printf("\nData inserted.\n");
}
void insertAtTail(){
    if(head == NULL) insertAtHead();
    else {
        struct node *newnode = createNode();
        struct node *temp = head;
        while(temp->next != head) temp = temp->next;
        newnode->next = head;
        newnode->prev = temp;
        head->prev = newnode;
        temp->next = newnode;
        count++;
        printf("\nData inserted.\n");
    }
}
void insertAtPosition(){
    int pos = getPosition();
    int mark = 1;
    if(pos < 1) printf("\nInvalid position.\n");
    else if(pos == 1) insertAtHead();
    else if(count + 1 < pos) printf("\nInvalid position.\n");
    else if(count + 1 == pos) insertAtTail();
    else {
        struct node *newnode = createNode();
        struct node *temp = head;
        while(pos - 1 != mark){
            mark++;
            temp = temp->next;
        }
        newnode->next = temp->next;
        newnode->prev = temp;
        temp->next->prev = newnode;
        temp->next = newnode;
        count++;
        printf("\nData inserted.\n");
    }
}
void deleteAtHead(){
    if(head == NULL) printf("\nList is empty!\n");
    if(count == 1){
        head = NULL;
        count--;
        printf("\nData deleted.\n");
    } else {
        head->next->prev = head->prev;
        head->prev->next = head->next;
        head = head->next;
        count--;
        printf("\nData deleted.\n");
    }
}
void deleteAtTail(){
    if(head == NULL) printf("\nList is empty!\n");
    else if(count == 1) {
        head = NULL;
        count--;
        printf("\nData deleted.\n");
    } else {
        struct node *lastnode = head->prev;
        head->prev = lastnode->prev;
        lastnode->prev->next = head;
        count--;
        printf("\nData deleted.\n");
    }
}
void deleteAtPosition(){
    if(head == NULL) printf("\nList is empty!\n");
    else {
        int mark = 1;
        int pos = getPosition();
        if(pos < 1) printf("\nInvalid position.\n");
        else if(pos == 1) deleteAtHead();
        else if(count < pos) printf("\nInvalid position.\n");
        else if(count == pos) deleteAtTail(); 
        else {
            struct node *temp = head;
            while(mark != pos){
                mark++;
                temp = temp->next;
            }
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            count--;
            printf("\nData deleted.\n");
        }
    }
}
void forwardDisplay(){
    if(head == NULL) printf("\nList is empty!\n");
    else {
        struct node *temp = head;
        printf("\nList : ");
        while(temp->next != head){
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("%d \n", temp->data);
    }
}
void backwardDisplay(){
    if(head == NULL) printf("\nList is empty!\n");
    else {
        struct node* temp = head->prev;
        printf("\nList : ");
        while(temp->prev != head) {
            printf("%d ", temp->data);
            temp = temp->prev;
        }
        if(count < 1) printf("%d ", temp->data);
        printf("%d ", head->data);
        printf("\n");
    }
}
void main(){
    int choice;
    while(true){
        printf("\n1. insert at head\n2. insert at tail\n3. insert at position\n4. delete at head\n5. delete at tail\n6. delete at position\n7. forward display\n8. backward display\n9. exit\nEnter the operation : ");
        scanf("%d", &choice);
        switch(choice){
            case 1: insertAtHead();
                    break;
            case 2: insertAtTail();
                    break;
            case 3: insertAtPosition();
                    break;
            case 4: deleteAtHead();
                    break;
            case 5: deleteAtTail();
                    break;
            case 6: deleteAtPosition();
                    break;
            case 7: forwardDisplay();
                    break;
            case 8: backwardDisplay();
                    break;
            case 9: printf("\n Exiting the program. \n");
                    return;
            default: printf("\nInvalid selection.\n");
        }
    }
    return;
}