#include <stdio.h>
#include <stdlib.h>
int top=-1, stack[100], maxsize;
void caseCheck();
void push(){
	int element;
	printf("enter the element to read : ");
	scanf("%d", &element);
	
	if(top+1!=maxsize){
		top++;
		stack[top] = element;
	} else {
		printf("stack overflow\n");
	}
	caseCheck();
}
void pop(){
	if(top == -1){
		printf("stack is empty\n");
	} else {
		top--;
	}
	caseCheck();
}
void display(){
	for(int i=0; i<=top; i++){
		printf("%d \t", stack[i]);
	}
	caseCheck();
}
void peek(){
	if(top == -1){
		printf("stack is empty\n");
	} else {
		printf("last element is : %d\n", stack[top]);
	}
	caseCheck();
}
void isFull(){
	if(top == maxsize-1){
		printf("stack is full\n");
	} else {
		printf("stack is not full\n");
	}
	caseCheck();
}
void caseCheck(){
	int option;
	printf("\n1.push\n2.pop\n3.peek\n4.check if the stack is full\n5.display\n6.exit\nEnter the operation : ");
	scanf("%d", &option);
	switch(option){
		case 1 :  push();
			  break;
		case 2 :  pop();
			  break;
		case 3 :  peek();
			  break;
		case 4 :  isFull();
			  break;
		case 5 :  display();
			  break;
		case 6 :  exit(0);
			  break;
		default : printf("enter a valid input");  
	}
}
void main(){
	printf("enter the no.of elements : ");
	scanf("%d", &maxsize);
	caseCheck();
}
