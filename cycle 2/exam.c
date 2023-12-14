#include <stdio.h>
typedef struct createNode{
    int data;
    struct node *link = NULL;
} node;
// insert at beginning
void insertAtBeg(){

}
// delete at beginning
void deleteAtBeg(){

}
void main(){
    int choice;
    struct node *head = NULL;
    do{
        printf("1. insert at beginning\2. insert at end\n3. insert at position\n4.delete at start\n5.delete at end\n6. delete at position\n7. display\n8. Exit");
        scanf("%d", &choice);
        switch(choice){
            case 1: insertAtBeg(head);
                    break;
            case 2: deleteAtBeg(head);
                    break;
        }
    } while(choice != 8);
}