#include <stdio.h>
int main()
{
    int a[10], b[10], c[20], i, n1, n2, n3, x, j, temp;
    printf("Enter the first array:\n");
    printf("Enter the size of array:");
    scanf("%d", &n1);
    printf("Enter the elements:");
    for (i = 0; i < n1; i++)
    {
        scanf("%d", &a[i]);
    }
    for (i = 0; i < n1; i++)
    {
        printf("%d  ", a[i]);
    }
    printf("\nEnter the second array:\n");
    printf("Enter the size of array:");
    scanf("%d", &n2);
    printf("Enter the elements:");
    for (i = 0; i < n2; i++)
    {
        scanf("%d", &b[i]);
    }
    for (i = 0; i < n2; i++)
    {
        printf("%d  ", b[i]);
    }

    n3 = n1 + n2;
    for (i = 0; i < n1; i++)
    {
        c[i] = a[i];
    }
    for (i = 0; i < n2; i++)
    {
        c[i + n1] = b[i];
    }
    n1 = n3;
    for (i = 0; i < n1; i++)
    {
        a[i] = c[i];
    }
    printf("\nMerged array:\n");
    for (i = 0; i < n1 - 1; i++)
    {
        for (j = 0; j < n1 - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    for (i = 0; i < n1; i++)
    {
        printf("%d ", a[i]);
    }

    return 0;
}