#include "matrix_dtype.h"
#include "matrix_basicfunc_ptypes.h"
#include <stdlib.h>

Matrix* MTX_Malloc(int r, int c){
    Matrix* newmtx = malloc(sizeof(Matrix));
    newmtx->columns = c;
    newmtx->rows = r;
    newmtx->numbers = (double**)malloc(r * sizeof(double*));
    newmtx->numbers[0] = (double*)malloc(r * c * sizeof(double));
    int rowIter;
    for (rowIter = 1; rowIter < r; rowIter++){
        newmtx->numbers[rowIter] = newmtx->numbers[0] + rowIter*c;
    }
    return newmtx;
}

void MTX_Free(Matrix* mtx){
    free(mtx->numbers[0]);
    free(mtx->numbers);
    free(mtx);
}

void MTX_DeleteRow(Matrix* mtx, int rowNo){
    double* toDelete = mtx->numbers[rowNo];
    int i;
    for(i = rowNo; i < mtx->rows - 1; i++){
        mtx->numbers[i] = mtx->numbers[i + 1];
    }
    free(toDelete);
    mtx->rows--;
}

void MTX_ChangeRow(Matrix* mtx, int rowA, int rowB){
    double* temp = mtx->numbers[rowA];
    mtx->numbers[rowA] = mtx->numbers[rowB];
    mtx->numbers[rowB] = temp;
}

bool SizeEqCheck(Matrix* mtxA, Matrix* mtxB){
  if(mtxA->rows != mtxB->rows || mtxA->columns != mtxB->columns){
    return false;
  }else{
    return true;
  }
}

void MTX_Copy(Matrix* mtxTo, Matrix* mtxFrom){
    if(SizeEqCheck(mtxTo, mtxFrom)){
        int i,j;
        for(i = 0; i < mtxFrom->rows; i++){
            for(j = 0; j < mtxFrom->columns; j++){
                mtxTo->numbers[i][j] = mtxFrom->numbers[i][j];
            }
        }
    }
    else{

    }
}

void MTX_AddRow(Matrix* mtx, int i, int t, double lambda){
    int j;
    for(j = 0; j < mtx->columns; j++){
        mtx->numbers[t][j] += lambda * mtx->numbers[i][j];
    }
}

void MTX_MultiplyRow(Matrix* mtx, int i, double lambda){
    int j;
    for(j = 0; j < mtx->columns; j++){
        mtx->numbers[i][j] *= lambda;
    }
}



