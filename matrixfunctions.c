#include "datatypes.h"
#include <stdlib.h>

Matrix* MTX_Malloc(int r, int c){
    Matrix* newmtx = malloc(sizeof(Matrix));
    newmtx->columns = c;
    newmtx->rows = r;
    newmtx->numbers = (double**)malloc(r * sizeof(double*));
    newmtx[0] = (double*) malloc(r * c * sizeof(double));
    int rowIter;
    for (rowIter = 1; rowIter < r; rowIter++){
        newmtx[rowIter] = newmtx[0] + rowIter * c;
    }
    return newmtx;
}

void MTX_Copy(Matrix* cpy, Matrix* src){
    
}
