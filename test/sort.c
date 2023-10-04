#include <stdio.h>
int n;
void display(int a[]){
    for(int i=0; i <n; i++){
        printf("%d ", a[i]);
    }
}
void main(){
    int a[50];
    printf("enter the no.of elements : ");
    scanf("%d", &n);

    printf("enter the array elements : \n");
    for(int i=0; i<n; i++){
        scanf("%d", &a[i]);
    }

    printf("\narray elements before sorting : ");
    display(a);

    //insertion sort 
    int b[50];
    for(int i=0; i<n; i++) b[i] = a[i];
    int key, j;
    for(int i=1; i<n;i++){
        key = b[i];
        j = i - 1;
        while(0<=j && key < b[j]){
            b[j + 1] = b[j];
            j--;
        }
        b[j + 1] = key;
    }
    //end of insertion sort 

    printf("\narray after insertion sort : ");
    display(b);

    //selection sort 
    int c[50];
    for(int i=0; i<n; i++) c[i] = a[i];

    int min, temp;
    for(int i=0; i< n-1; i++){
        min = i;
        for(int j=i+1; j<n; j++){
            if(c[min]>c[j]){
                min = j;
            }
        }
        temp = c[min];
        c[min] = c[i];
        c[i] = temp;
    }
    printf("\narray after selection sort : ");
    display(c);
    
    printf("\n");
}