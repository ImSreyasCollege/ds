#include <stdio.h>

// Function to print a set
void printSet(int set[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", set[i]);
    }
    printf("\n");
}

// Function to perform the union of two sets
void setUnion(int set1[], int size1, int set2[], int size2, int result[], int *resultSize) {
    int i = 0, j = 0, k = 0;
    while (i < size1 && j < size2) {
        if (set1[i] < set2[j]) {
            result[k++] = set1[i++];
        } else if (set1[i] > set2[j]) {
            result[k++] = set2[j++];
        } else {
            result[k++] = set1[i++];
            j++;
        }
    }

    while (i < size1) {
        result[k++] = set1[i++];
    }

    while (j < size2) {
        result[k++] = set2[j++];
    }

    *resultSize = k;
}

// Function to perform the intersection of two sets
void setIntersection(int set1[], int size1, int set2[], int size2, int result[], int *resultSize) {
    int i = 0, j = 0, k = 0;
    while (i < size1 && j < size2) {
        if (set1[i] < set2[j]) {
            i++;
        } else if (set1[i] > set2[j]) {
            j++;
        } else {
            result[k++] = set1[i++];
            j++;
        }
    }

    *resultSize = k;
}

// Function to perform the set difference (set1 - set2)
void setDifference(int set1[], int size1, int set2[], int size2, int result[], int *resultSize) {
    int i = 0, j = 0, k = 0;
    while (i < size1 && j < size2) {
        if (set1[i] < set2[j]) {
            result[k++] = set1[i++];
        } else if (set1[i] > set2[j]) {
            j++;
        } else {
            i++;
            j++;
        }
    }

    while (i < size1) {
        result[k++] = set1[i++];
    }

    *resultSize = k;
}

int main() {
    int size1, size2;

    printf("Enter the size of Set 1: ");
    scanf("%d", &size1);
    int set1[size1];

    printf("Enter %d elements for Set 1:\n", size1);
    for (int i = 0; i < size1; i++) {
        scanf("%d", &set1[i]);
    }

    printf("Enter the size of Set 2: ");
    scanf("%d", &size2);
    int set2[size2];

    printf("Enter %d elements for Set 2:\n", size2);
    for (int i = 0; i < size2; i++) {
        scanf("%d", &set2[i]);
    }

    int unionResult[size1 + size2];
    int unionSize = 0;

    int intersectionResult[size1 < size2 ? size1 : size2];
    int intersectionSize = 0;

    int differenceResult[size1];
    int differenceSize = 0;

    printf("Set 1: ");
    printSet(set1, size1);

    printf("Set 2: ");
    printSet(set2, size2);

    setUnion(set1, size1, set2, size2, unionResult, &unionSize);
    printf("Union: ");
    printSet(unionResult, unionSize);

    setIntersection(set1, size1, set2, size2, intersectionResult, &intersectionSize);
    printf("Intersection: ");
    printSet(intersectionResult, intersectionSize);

    setDifference(set1, size1, set2, size2, differenceResult, &differenceSize);
    printf("Set Difference (Set 1 - Set 2): ");
    printSet(differenceResult, differenceSize);

    return 0;
}
