#include <stdio.h>

void displayMatrix(int mat[][100], int rows, int cols) {
    printf("Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }
}

void addMatrices(int mat1[][100], int mat2[][100], int result[][100], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
}

void multiplyMatrices(int mat1[][100], int rows1, int cols1, int mat2[][100], int cols2, int result[][100]) {
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < cols1; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

void transposeMatrix(int mat[][100], int rows, int cols, int result[][100]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j][i] = mat[i][j];
        }
    }
}

int main() {
    int mat1[100][100], mat2[100][100], result[100][100];
    int rows1, cols1, rows2, cols2;

    printf("Enter the number of rows for the first matrix: ");
    scanf("%d", &rows1);
    printf("Enter the number of columns for the first matrix: ");
    scanf("%d", &cols1);

    printf("Enter elements for the first matrix:\n");
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols1; j++) {
            scanf("%d", &mat1[i][j]);
        }
    }

    printf("Enter the number of rows for the second matrix: ");
    scanf("%d", &rows2);
    printf("Enter the number of columns for the second matrix: ");
    scanf("%d", &cols2);

    printf("Enter elements for the second matrix:\n");
    for (int i = 0; i < rows2; i++) {
        for (int j = 0; j < cols2; j++) {
            scanf("%d", &mat2[i][j]);
        }
    }

    if (cols1 != rows2) {
        printf("Matrix multiplication is not possible. Number of columns in the first matrix must be equal to the number of rows in the second matrix.\n");
        return 1;
    }

    if (rows1 == rows2 && cols1 == cols2) {
        addMatrices(mat1, mat2, result, rows1, cols1);
        printf("Matrix Addition Result:\n");
        displayMatrix(result, rows1, cols1);
    } else {
        printf("Matrix addition is not possible. Matrices must have the same dimensions for addition.\n");
    }

    multiplyMatrices(mat1, rows1, cols1, mat2, cols2, result);
    printf("Matrix Multiplication Result:\n");
    displayMatrix(result, rows1, cols2);

    transposeMatrix(mat1, rows1, cols1, result);
    printf("Transpose of the First Matrix:\n");
    displayMatrix(result, cols1, rows1);

    transposeMatrix(mat2, rows2, cols2, result);
    printf("Transpose of the Second Matrix:\n");
    displayMatrix(result, cols2, rows2);

    return 0;
}
