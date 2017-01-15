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
  } else {
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
    } else {
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

Matrix MTX_Sum(Matrix* mtxA, Matrix* mtxB){
  if(SizeEqCheck(mtxA, mtxB)){
    if(IsDiagonal(mtxA)){
      int i,j;
      Matrix mtxC = MTX_Malloc(mtxA->rows, mtxA->columns);
      for(i = 0; i < mtxC->rows, i++){
        for(j = 0; i < mtxC->columns; j++){
          mtxC->numbers[i][j] = mtxA->numbers[i][j] + mtxB->numbers[i][j];
        }
      }
      return mtxC;
    }
  }
}

bool MultiCheck(Matrix* mtxA, Matrix* mtxB){
  if(mtxA->columns == mtxB->rows){
    return true;
  } else {
    return false;
  }
}

Matrix MTX_Multiply(Matrix* mtxA, Matrix* mtxB){
  if(MultiCheck(mtxA, mtxB)){
    int sum;
    Matrix mtxC = MTX_Malloc(mtxA->rows, mtxb->columns);
    for(int i = 0; i < mtxC->rows; i++){
      sum = 0;
      for(int j = 0; j < mtxC->columns; j++){
        for(int l; l < mtxA->columns; l++){
          for(int k; k < mtxB->rows; k++){
            sum += mtxA->numbers[i][k] * mtxB->numbers[l][j];
          }
        }
        mtxC->numbers[i][j] = sum;
      }
    }
    return mtxC;
  }
}

void MTX_ScalarMultiply(Matrix* mtxA, double lambda){
  for(int i = 0; i < mtxA->rows; i++){
    for(int j = 0; j < mtxA->columns; j++){
      mtxA->numbers[i][j]*=lambda;
    }
  }
}

Matrix MTX_Transposition(Matrix* mtxA){
  if(IsDiagonal(mtxA)){
    Matrix mtxT = MTX_Malloc(mtxA->rows, mtxA->columns);
    for(int i = 0; i < mtxT->rows; i++){
      for(int j = 0; j < mtxT->columns; j++){
        mtxT->numbers[i][j] = mtxA->numbers[j][i];
      }
    }
    return mtxT;
  }
}

bool IsInvertable(Matrix* mtxA){
  if(IsQuadratic(mtxA){
    if(mtxA->determinant == 0){
      return false;
    } else {
      return true;
    }
  } else {
    return false;
  }
}

bool IsQuadratic(Matrix* mtxQ){
  if(mtxQ->rows == mtxQ->columns){
    return true;
  } else {
    return false;
  }
}

bool IsDiagonal(Matrix* mtxD){
  if(IsQuadratic(mtxD)){
    bool mainDiagonal = true;
    bool zeroElements = true;
    int i,j = 0;
    while(i < mtxD->rows && mainDiagonal){
      if(mtxD->numbers[i][i] == 0){
        mainDiagonal = false;
      }
      i++;
    }
    i = 0;
    if(!mainDiagonal){
      return false;
    } else {
      while(i < mtxD->rows && zeroElements){
        while(j < mtxD->columns){
          if(mtxD->numbers[i][j] != 0){
            zeroElements = false;
          }
          j++;
        }
        i++;
      }
    }
    if(!zeroElements){
      return false;
    } else {
      return true;
    }
  } else {
    return false;
  }
}

bool IsIdentity(Matrix* mtxI){
  if(IsDiagonal(mtxI)){
    if(DiagonalType(mtxI, true)){
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

bool DiagonalType(Matrix* mtxI, double type){
  int i = 0;
  bool idential = true;
  while(i < mtxI->rows && idential){
    if(mtxI->nums[0][0] != type){
      idential = false;
    }
    i++;
  }
  if(idential){
    return true;
  } else {
    return false;
}


bool IsSymmetric(Matrix* mtxS){
  if(mtxS == MTX_Transposition(mtxS)){
    return true;
  } else {
    return false;
  }
}

bool IsAntiSymmetric(Matrix* mtxA)}{
  if(mtxA == MTX_ScalarMultiply(MTX_Transposition(mtxA), (0 - 1))){
    return true;
  } else {
    return false;
  }
}

bool IsUpperTriangle(Matrix* mtxT){
  if(IsQuadratic(mtxT)){
    bool zeroElements = true;
    while(int i = 0; i < mtxT->rows && zeroElements){
      while(int j = 0; j < (i-1){
        if(mtxT->numbers[i][j] != 0){
          zeroElements = false;
        }
        j++;
      }
      i++;
    }
    if(zeroElements){
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

bool IsLowerTriangle(Matrix* mtxT){
  if(IsQuadratic(mtxT)){
    bool zeroElements = true;
    while(int i = 0; i < mtxT->rows && zeroElements){
      while(int j = (i + 1); j < mtxT->columns){
        if(mtxT->numbers[i][j] != 0){
          zeroElements = false;
        }
        j++;
      }
      i++;
    }
    if(zeroElements){
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}


bool IsTriangular(Matrix* mtxT){
  if(IsUpperTriangual(mtxT) || IsLowerTriangual(mtxT)){
    return true;
  } else {
    return false;
  }
}

bool IsStrictlyTriangular(Matrix* mtxT){
  if(DiagonalType(mtxT, false) && IsLowerTriangual(mtxT) || IsUpperTriangual(mtxT)){
    return true;
  } else {
    return false;
  }
}

bool IsUnitriangular(Matrix* mtxT)}
  if(DiagonalType(mtxT, true) && IsLowerTriangual(mtxT) || IsUpperTriangual(mtxT)){
    return true;
  } else {
    return false;
  }
}

bool IsZero(Matrix* mtxZ){
  int i,j = 0;
  bool allZero = true;
  while(i < mtxZ->rows && isZero == true){
    while(j < mtxZ->columns){
      j++;
      if(mtxZ->numbers[i][j] != 0){
        allZero = false;
      }
    }
    i++;
  }
  if(allZero){
    return true;
  } else {
    return false;
  }
}
