#include <stdio.h>
#include <string.h>

int searchSubstring(char *str, char *subStr) {
    char *p = strstr(str, subStr);
    return (p) ? p - str : -1;
}
void concatenateStrings(char *str1, char *str2, char *result) {
    strcpy(result, str1);
    strcat(result, str2);
}

void extractSubstring(char *str, int start, int length, char *result) {
    strncpy(result, str + start, length);
    result[length] = '\0';
}

int main() {
    char str1[100], str2[100], subStr[100], result[200];
    int start, length;

    printf("Enter the first string: ");
    scanf("%s", str1);

    printf("Enter the second string: ");
    scanf("%s", str2);

    printf("Enter the substring to check : ");
    scanf("%s", subStr);

    concatenateStrings(str1, str2, result);
    printf("Concatenated string: %s\n", result);

    int index = searchSubstring(result, subStr);
    if (index != -1) {
        printf("Substring found at position %d in the string.\n", index+1);
    } else {
        printf("Substring not found in the first string.\n");
    }

    concatenateStrings(str1, str2, result);
    printf("Concatenated string: %s\n", result);

    printf("Enter the starting index for substring extraction: ");
    scanf("%d", &start);
    printf("Enter the length of the substring to extract: ");
    scanf("%d", &length);

    extractSubstring(str1, start, length, result);
    printf("Extracted substring: %s\n", result);

    return 0;
}
