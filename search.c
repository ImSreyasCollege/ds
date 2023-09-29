#include <stdio.h>

// Function for linear search
int linearSearch(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key) {
            return i; // Element found, return its index
        }
    }
    return -1; // Element not found
}

// Function for binary search (assuming the array is sorted in ascending order)
int binarySearch(int arr[], int n, int key) {
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == key) {
            return mid; // Element found, return its index
        } else if (arr[mid] < key) {
            left = mid + 1; // Search the right half
        } else {
            right = mid - 1; // Search the left half
        }
    }

    return -1; // Element not found
}

int main() {
    int arr[100];
    int n, key;

    printf("Enter the size of the array: ");
    scanf("%d", &n);

    printf("Enter elements of the array in ascending order:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the element to search for: ");
    scanf("%d", &key);

    // Perform linear search
    int linearResult = linearSearch(arr, n, key);
    if (linearResult != -1) {
        printf("Linear Search: Element found at position %d.\n", linearResult+1);
    } else {
        printf("Linear Search: Element not found.\n");
    }

    // Perform binary search
    int binaryResult = binarySearch(arr, n, key);
    if (binaryResult != -1) {
        printf("Binary Search: Element found at position %d.\n", binaryResult+1);
    } else {
        printf("Binary Search: Element not found.\n");
    }

    return 0;
}
