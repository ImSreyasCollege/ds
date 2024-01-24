#include <stdio.h>

void main(){
    int n, arr[50];
    printf("Enter the no.of elements : ");   
    scanf("%d", &n);
    printf("Enter the elements : ");
    for(int i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }
    for(int i=1; i<n; i++){
        int j = i - 1;
        int val = arr[i];
        while(j >= 0 && arr[j] > val){
            arr[j+1] = arr[j];
            --j;
        }
        arr[j+1] = val;
    }
    printf("Final array : ");
    for(int i=0; i<n; i++) printf("%d ", arr[i]);
    return;
}