#include <stdio.h>

struct Distance {
    int feet;
    int inches;
}d1, d2, result;

void addDistances() {
    result.inches = d1.inches + d2.inches;
    result.feet = result.inches >= 12 ? d1.feet + d2.feet + result.inches/12 : d1.feet + d2.feet;
    result.inches %= 12;
}

void main() {

    printf("Enter the first distance:\n");
    printf("Feet: ");
    scanf("%d", &d1.feet);
    printf("Inches: ");
    scanf("%d", &d1.inches);

    printf("Enter the second distance:\n");
    printf("Feet: ");
    scanf("%d", &d2.feet);
    printf("Inches: ");
    scanf("%d", &d2.inches);

    addDistances();

    printf("Sum of the distances: %d feet %d inches\n", result.feet, result.inches);
}
