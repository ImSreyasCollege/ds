#include <stdio.h>
void main()
{
    int a[10][10], b[10][10], result[20][20];
    int m, n, x, y;
    // read first matrix
    printf("enter the order of first matrix (rows x columns) : \n");
    scanf("%d %d", &m, &n);
    printf("enter the array elements : \n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
    // read second matrix
    printf("enter the order of second matrix (rows x columns) : \n");
    scanf("%d %d", &x, &y);
    printf("enter the array elements : \n");
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            scanf("%d", &b[i][j]);
        }
    }
    // matrix multiplication
    if (n != x)
    {
        printf("\nmatrix multiplication is not possible.\n");
    }
    else
    {
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < y; j++)
            {
                result[i][j] = 0;
                for(int k=0; k< n; k++){
                    result[i][j]+=a[i][k]*b[k][j];
                }
            }
        }
        printf("matrix : \n");
        for(int i=0; i<m; i++ ){
            for(int j=0; j<y; j++){
                printf("%d  ", result[i][j]);
            }
            printf("\n");
        }
    }
}