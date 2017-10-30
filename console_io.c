#include "console_io_ptypes.h"
#include "matrix_basicfunc_ptypes.h"
#include <stdio.h>

/**Matrix input function
*Ezzel a fgvnyel a konzolrol tudunk beolvasni egy matrixot, amelynek dinamikusan foglal memoriat es
*a pointerrel ter vissza.
*@return A beolvasott matrix pointere
*/
Matrix* matricks_input() {
    printf("Adja meg hany sora illetve oszlopa legyen a matrixnak ebben a sorrendben!");
    int row, col;
    scanf(" %d %d", &row, &col);
    Matrix* new_matrix = matrix_Malloc(row, col);

    int i, j;

    printf("\n    ");
    for (j = 0; j < col; j++){
        printf("%5d.", j + 1);
    }
    printf("\n");
    for(i = 0; i < row; i++){
        printf("%3d.",i + 1);
        for(j = 0; j < col; j++){
            scanf(" %lf", &new_matrix->numbers[i][j]);
        }
    }

    return new_matrix;
}

/**Matrixot print function
Prints the matrix given as parameter into console
*@param matrix A kiirando pointer of matrix
*/
void matricks_print(Matrix* matrix) {
    int i, j;

    printf("\n    ");
    for (j = 0; j < matrix->columns; j++){
        printf("%5d.",j + 1);
    }
    printf("\n");
    for(i = 0; i < matrix->rows; i++){
        printf("%3d.", i + 1);
        for(j = 0; j < matrix->columns; j++){
            printf("%6.2f", matrix->numbers[i][j]);
        }
        printf("\n");
    }
}
