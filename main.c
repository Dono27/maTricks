#include "matrix.h"
#include <stdio.h>

int main(void) {
    printf("[maTricks] by Nrehtron\n\n");

    Matrix* matrix = matricks_input();

    matricks_print(matrix);

    matrix = matricks_gaussian_elimination(matrix, CALCULATE_DET);

    matricks_print(matrix);
    printf("\nDeterminans : %f", matrix->determinant);

    return 0;
}
