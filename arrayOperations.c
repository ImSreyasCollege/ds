#include <stdio.h>

void display(int arr[], int n) {
    printf("Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void insert(int arr[], int *n, int element, int position) {
    if (*n >= 100) {
        printf("Array is full. Cannot insert.\n");
        return;
    }

    if (position < 0 || position > *n) {
        printf("Invalid position for insertion.\n");
        return;
    }

    for (int i = *n; i > position; i--) {
        arr[i] = arr[i - 1];
    }

    arr[position] = element;
    (*n)++;
}

void deleteElement(int arr[], int *n, int position) {
    if (*n <= 0) {
        printf("Array is empty. Cannot delete.\n");
        return;
    }

    if (position < 0 || position >= *n) {
        printf("Invalid position for deletion.\n");
        return;
    }

    for (int i = position; i < *n - 1; i++) {
        arr[i] = arr[i + 1];
    }

    (*n)--;
}

void merge(int arr1[], int n1, int arr2[], int n2, int result[]) {
    int i = 0, j = 0, k = 0;

    while (i < n1 && j < n2) {
        if (arr1[i] < arr2[j]) {
            result[k++] = arr1[i++];
        } else {
            result[k++] = arr2[j++];
        }
    }

    while (i < n1) {
        result[k++] = arr1[i++];
    }

    while (j < n2) {
        result[k++] = arr2[j++];
    }
}

int main() {
    int arr1[100], arr2[100], merged[200];
    int n1, n2;

    printf("Enter the size of the first array: ");
    scanf("%d", &n1);

    printf("Enter elements for the first array:\n");
    for (int i = 0; i < n1; i++) {
        scanf("%d", &arr1[i]);
    }

    printf("Enter the size of the second array: ");
    scanf("%d", &n2);

    printf("Enter elements for the second array:\n");
    for (int i = 0; i < n2; i++) {
        scanf("%d", &arr2[i]);
    }

    merge(arr1, n1, arr2, n2, merged);

    int mergedSize = n1 + n2;
    for (int i = 0; i < mergedSize - 1; i++) {
        for (int j = 0; j < mergedSize - i - 1; j++) {
            if (merged[j] > merged[j + 1]) {
                int temp = merged[j];
                merged[j] = merged[j + 1];
                merged[j + 1] = temp;
            }
        }
    }

    printf("Merged and Sorted Array:\n");
    display(merged, mergedSize);

    int choice;
    while (1) {
        printf("\nArray Operations:\n");
        printf("1. Insertion\n");
        printf("2. Deletion\n");
        printf("3. Display Merged Array\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                int element, position;
                printf("Enter the element to insert: ");
                scanf("%d", &element);
                printf("Enter the position for insertion: ");
                scanf("%d", &position);
                insert(merged, &mergedSize, element, position);
                printf("Element inserted successfully.\n");
                break;

            case 2:
                scanf("%d", &position);
                deleteElement(merged, &mergedSize, position);
                printf("Element deleted successfully.\n");
                break;

            case 3:
                display(merged, mergedSize);
                break;

            case 4:
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
