#include <stdio.h>

void main(){
    int n, min, arr[50];
    printf("Enter the no.of elements : ");
    scanf("%d", &n);
    printf("Enter the elements : ");
    for(int i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }
    for(int i=0; i<n-1; i++){
        min = i;
        for(int j=i+1; j<n; j++){
            if(arr[j] < arr[min]) min = j;
        }
        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
    printf("Final arra : ");
    for(int i=0; i<n; i++){
        printf("%d ", arr[i]);
    }
    return;
}