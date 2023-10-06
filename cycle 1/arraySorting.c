#include <stdio.h>

void displayArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selectionSort(int arr[], int size) {
    int min, temp;
    for (int i = 0; i < size - 1; i++) {
        min = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}

void insertionSort(int arr[], int size) {
    int key, j;
    for (int i = 1; i < size; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void main() {
    int arr[100], size;
    
    printf("Enter the number of elements in the array: ");
    scanf("%d", &size);

    printf("Enter the elements of the array:\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    //creating new array for storing sorted values in bubble sort.
    int bubbleSortedArr[100];
    for (int i = 0; i < size; i++) bubbleSortedArr[i] = arr[i];
    //calling bubble sort function.
    bubbleSort(bubbleSortedArr, size);
    //display bubble sort 
    printf("Bubble Sort Result: ");
    displayArray(bubbleSortedArr, size);

    //creating a new array for storing the sorted values in selection sort.
    int selectionSortedArr[100];
    for (int i = 0; i < size; i++) selectionSortedArr[i] = arr[i];
    //calling selection sort function
    selectionSort(selectionSortedArr, size);
    //display selection sort 
    printf("Selection Sort Result: ");
    displayArray(selectionSortedArr, size);

    //creating a new array for storing the sorted values in insertion sort.
    int insertionSortedArr[100];
    for (int i = 0; i < size; i++) insertionSortedArr[i] = arr[i];
    //calling insertion sort function
    insertionSort(insertionSortedArr, size);
    //display insertion sort 
    printf("Insertion Sort Result: ");
    displayArray(insertionSortedArr, size);
}
