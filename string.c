#include <stdio.h>
#include <string.h>

// Function to perform string searching
int searchSubstring(char *str, char *subStr) {
    char *found = strstr(str, subStr);
    if (found) {
        return found - str; // Return the index of the first occurrence
    } else {
        return -1; // Substring not found
    }
}

// Function to perform string concatenation
void concatenateStrings(char *str1, char *str2, char *result) {
    strcpy(result, str1);
    strcat(result, str2);
}

// Function to extract a substring from a string
void extractSubstring(char *str, int start, int length, char *result) {
    strncpy(result, str + start, length);
    result[length] = '\0'; // Null-terminate the result
}

int main() {
    char str1[100], str2[100], subStr[100], result[200];
    int start, length;

    // Input the first string
    printf("Enter the first string: ");
    scanf("%s", str1);

    // Input the second string
    printf("Enter the second string: ");
    scanf("%s", str2);

    // Input the substring to search
    printf("Enter the substring to search for: ");
    scanf("%s", subStr);

    // Search for the substring
    int index = searchSubstring(str1, subStr);
    if (index != -1) {
        printf("Substring found at index %d in the first string.\n", index);
    } else {
        printf("Substring not found in the first string.\n");
    }

    // Concatenate the two strings
    concatenateStrings(str1, str2, result);
    printf("Concatenated string: %s\n", result);

    // Input the start and length for substring extraction
    printf("Enter the starting index for substring extraction: ");
    scanf("%d", &start);
    printf("Enter the length of the substring to extract: ");
    scanf("%d", &length);

    // Extract the substring
    extractSubstring(str1, start, length, result);
    printf("Extracted substring: %s\n", result);

    return 0;
}
