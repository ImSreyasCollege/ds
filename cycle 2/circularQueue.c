#include <stdio.h>
int front = -1;
int rear = -1;
int max = 5;
int q[5];

void enqueue();
void dequeue();
void displayRear();
void displayFront();
void display();
int main(){
    int c;
    while(1){
        printf("1.enqueue\n2.delte\n3.display rear\n4.display front\n5.display\n6.Exit\nEnter the operation : ");
        scanf("%d", &c);
        switch(c){
            case 1: enqueue();
            break;
            case 2: dequeue();
            break;
            case 3: displayRear();
            break;
            case 4: displayFront();
            break;
            case 5: display();
            break;
            case 6: return 0;
            default: "invalid option! Please enter a valid option : ";
        }
    }
}
void enqueue(){
    int data;
    if(rear-front < max){
        printf("queue is full.\n");
    } else {
        printf("enter the data to insert : ");
        scanf("%d", &data);   
        rear++;
        q[rear%max] = data;
        printf("data inserted to position %d\n", rear%max+1);
    }
}
void dequeue(){
    if(rear <= front){
        printf("stack is empty.\n");
    } else {
        front++;
        front%=max;
        printf("data successfully deleted from the position %d\n", front%max+1);
    }
}
void display(){
    printf("\narray elements are : ");
    for(int i=front%max+1; i<=rear%max; i++){
        printf("%d ", q[i]);
    }
    printf("\n");
}
void displayFront(){
    printf("first element is : %d\n", q[front+1]);
}
void displayRear(){
    printf("last element is : %d\n", q[rear]);
}
