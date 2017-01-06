#ifndef MATRIX_DTYPE_H_INCLUDED
#define  MATRIX_DTYPE_H_INCLUDED

//FLAG-ek a MTX_GaussElim()-hez
#define SOLVE_LINEAR_SYSTEM 0x01
#define CALCULATE_DET 0x02

/**A matrix.
*Ez az adatszerkezet egy matrix adatait tarolja el.
*/
typedef struct Matrix{
    int rows;           ///<sorok szama
    int columns;        ///<oszlopok szama
    double **numbers;   ///<a szamok
}Matrix;

#endif
