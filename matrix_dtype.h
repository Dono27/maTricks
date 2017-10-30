#ifndef MATRIX_DTYPE_H_INCLUDED
#define  MATRIX_DTYPE_H_INCLUDED

//FLAGs for matricks_gaussian_elimination()
#define SOLVE_LINEAR_SYSTEM 0x01
#define CALCULATE_DET 0x02

/**Matrix
*Store matrix, its dimension and determinant if it is exist.
*/
typedef struct Matrix{
    int rows;           ///<number of rows
    int columns;        ///<number of columns
    double **numbers;   ///<matrix's items
    double determinant; ///<if it is exist
}Matrix;

#endif
