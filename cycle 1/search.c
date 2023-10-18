#include <stdio.h>
// This function is used for getting the search key
int getKey(){
    int key;
    printf("enter the key to search : ");
    scanf("%d", &key);
    return key;
}
// function to perform linear search
void linearSearch(int n) {
    int arr[50], flag=0; 
    printf("Enter elements of the array :\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    int key = getKey();
    int i=0;
    for (i = 0; i < n; i++) {
        if (arr[i] == key) {
            flag = 1;
            break;
        }
    }
    if(flag==1){
        printf("element found at location %d.\n", i+1);
    } else {
        printf("element not found.\n");
    }
}
// function to perform binary search
void binarySearch(int n) {
    int left = 0, arr[50];
    int right = n - 1;

    printf("Enter elements of the array in ascending order:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    int key = getKey();
    int flag = 0;
    int mid = 0;
    while (left <= right) {
        mid = left + (right - left) / 2;

        if (arr[mid] == key) {
            flag = 1;
            break;
        } else if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    if(flag==1){
        printf("element found at location %d.\n", mid+1);
    } else {
        printf("element not found.\n");
    }
}

int main() {
    int arr[100];
    int n;

    printf("Enter the size of the array: ");
    scanf("%d", &n);

    int opt;
    while(1){
        printf("1.binary search\n2.linear search\n3.exit\nEnter the operation : ");
        scanf("%d", &opt);
        switch(opt){
            case 1: binarySearch(n);
            break;
            case 2: linearSearch(n);
            break;
            case 3: return 1;
            default: printf("invalid input.\n");
        }
    }
    return 1;
}
