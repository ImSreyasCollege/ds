#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node{
    int data;
    struct node *prev;
    struct node *next;
};
struct node *head = NULL;
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
    struct node *newnode = (struct node*)malloc(sizeof(struct node*));
    newnode->data = getData();
    newnode->prev = NULL;
    newnode->next = NULL;
    return newnode;
}
void insertAtBeg(){
    struct node *newnode = createNode();   
    if(head == NULL) head = newnode;
    else {
        newnode->next = head;
        head->prev = newnode;
        head = newnode;
    }
}
void insertAtEnd(){
    if(head == NULL) insertAtBeg();
    else {
        struct node *newnode = createNode();
        struct node *temp = head;
        while(temp->next != NULL) temp = temp->next;
        temp->next = newnode;
        newnode->prev = temp;
    }
}
void insertAtPos(){
    int pos = getPosition();
    if(pos == 1) insertAtBeg();
    else if(pos < 1) printf("Invalid position.\n");
    else {
        if (head == NULL) printf("Invalid position.\n");
        else {
            int count = 1;
            struct node *temp = head;
            while (temp->next != NULL && count != pos - 1) {
                temp = temp->next;
                ++count;
            }
            if (temp->next == NULL) {
                if (count == pos - 1) insertAtEnd();
                else printf("Invalid position.\n");
            } else {
                struct node *newnode = createNode();
                newnode->next = temp->next;
                newnode->prev = temp;
                temp->next->prev = newnode;
                temp->next = newnode;
            }
        }
    }
}
void deleteAtBeg(){
    if(head == NULL) printf("List is empty.\n");
    else {
        head = head->next;
        if(head != NULL) head->prev = NULL;
    }
}
void deleteAtEnd(){
    if(head == NULL) printf("List is empty.\n");
    else {
        struct node *temp = head;
        struct node *pTemp = NULL;
        while(temp->next != NULL){
            pTemp = temp;
            temp = temp->next;
        }
        if(pTemp == NULL) head = NULL;
        else pTemp->next = NULL;
    }
}
void deleteAtPos(){
    int pos = getPosition();
    if(head == NULL){
        printf("List is empty. Deletion not possible.\n");
    } else {
        if(pos == 1) deleteAtBeg();
        else if(pos < 1) printf("Invalid position.\n");
        else {
            int count = 1;
            struct node *temp = head;
            while(temp->next != NULL && count != pos){
                temp = temp->next;
                ++count;
            }
            if(temp->next == NULL){
                if(count == pos) deleteAtEnd();
                else printf("Invalid position.\n");
            } else {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
        }
    }
}
void forwardDisplay(){
    if(head == NULL) printf("\nList is empty!\n");
    else {
        struct node *temp = head;
        while(temp != NULL){
            printf("%d <-> ", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}
void backwardDisplay(){
    if(head == NULL) printf("\nList is empty!\n");
    else {
        struct node *temp = head;
        while(temp->next != NULL) temp = temp->next;
        while(temp != NULL) {
            printf("%d <-> ", temp->data);
            temp = temp->prev;
        }
        printf("NULL\n");
    }
}
void search(){
    int data;
    printf("Enter the value to check : ");
    scanf("%d", &data);

    if(head == NULL) printf("\nList is empty!\n");
    else {
        struct node *temp = head;
        while(temp != NULL){
            if(temp->data == data) {
                printf("\n%d found in the list.\n", data);
                return;
            }
            temp = temp->next;
        }
        printf("\n%d not found in the list.\n", data);
    }
}
int main(){
    int choice;
    while(true){
        printf("\n1. Insert at Beginning\n2. Insert at End\n3. Insert at Position\n4. Delete at Beginning\n5. Delete at End\n6. Delete at Position\n7. Forward Display\n8. Backward Display\n9. Search\n10. Exit\n");
        printf("Enter the operation : ");
        scanf("%d", &choice);
        switch(choice){
            case 1: insertAtBeg();
                break;
            case 2: insertAtEnd();
                break;
            case 3: insertAtPos();
                break;
            case 4: deleteAtBeg();
                break;
            case 5: deleteAtEnd();
                break;
            case 6: deleteAtPos();
                break;
            case 7: forwardDisplay(); 
                break;
            case 8: backwardDisplay();
                break;
            case 9: search();
                break;
            case 10: return 0;
            default: printf("Invalid choice.\n");
        }
    }
    return 0;
}

