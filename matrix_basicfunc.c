#include "matrix_dtype.h"
#include "matrix_basicfunc_ptypes.h"
#include <stdlib.h>

/**Dinamikusan teruletet foglal egy Matrix-nak.
*@param r sorok szama
*@param c oszlopok szama
*@return a lefoglalt teruletre mutato Matrix tipusu pointer
*/
Matrix* MTX_Malloc(int r, int c) {
    Matrix* newmtx = malloc(sizeof(Matrix));
    newmtx->columns = c;
    newmtx->rows = r;
    newmtx->numbers = (double**)malloc(r * sizeof(double*));
    newmtx->numbers[0] = (double*)malloc(r * c * sizeof(double));
    int rowIter;
    for (rowIter = 1; rowIter < r; rowIter++) {
        newmtx->numbers[rowIter] = newmtx->numbers[0] + rowIter*c;
    }
    return newmtx;
}

/**Felszabaditja a parameterkent atadott matrixot.
*@param mtx a felszabaditando matrix
*/
void MTX_Free(Matrix* mtx) {
    free(mtx->numbers[0]);
    free(mtx->numbers);
    free(mtx);
}

/**Torli a megadott sort a matrixbol.
*@param mtx a celmatrix
*@param rowNo a torlendo sor indexe
*/
void MTX_DeleteRow(Matrix* mtx, int rowNo) {
    double* toDelete = mtx->numbers[rowNo];
    int i;
    for (i = rowNo; i < mtx->rows - 1; i++) {
        mtx->numbers[i] = mtx->numbers[i + 1];
    }
    free(toDelete);
    mtx->rows--;
}

/**Megcsereli a megadott sorokat a matrixban.
*@param mtx a celmatrix
*@param rowA az egyik cserelendo sor
*@param rowB a masik cserelndo sor
*/
void MTX_ChangeRow(Matrix* mtx, int rowA, int rowB){
    double* temp = mtx->numbers[rowA];
    mtx->numbers[rowA] = mtx->numbers[rowB];
    mtx->numbers[rowB] = temp;
}

/**Megnezi hogy ket matrix ugyanolyan meretu e.
*@param mtxA az egyik matrix
*@param mtxB a masik matrix
*@return ugyanakkorak e
*/
bool SizeEqCheck(Matrix* mtxA, Matrix* mtxB) {
  if ((mtxA->rows == mtxB->rows) && (mtxA->columns == mtxB->columns)) {
    return true;
  } else {
    return false;
  }
}

/**Atmasolja az egyik matrixot a masikba.
 *@param mtxTo ahova masolunk
 *@param mtxFrom ahonnan masolunk
 */
void MTX_Copy(Matrix* mtxTo, Matrix* mtxFrom) {
    if (SizeEqCheck(mtxTo, mtxFrom)) {
        int i,j;
        for (i = 0; i < mtxFrom->rows; i++) {
            for (j = 0; j < mtxFrom->columns; j++) {
                mtxTo->numbers[i][j] = mtxFrom->numbers[i][j];
            }
        }
    }
}

/**Az i-edik sor lambdaszorosanak hozzaadasa a t-edik sorhoz.
 * @param mtx a celmatrix
 * @param i hozzaadando sor indexe
 * @param t a sor amihez hozzaadunk
 * @param lambda lambda*i. sor
 */
void MTX_AddRow(Matrix* mtx, int i, int t, double lambda) {
    int j;
    for (j = 0; j < mtx->columns; j++) {
        mtx->numbers[t][j] += lambda * mtx->numbers[i][j];
    }
}

/**A matrix egyik soranak megszorzasa lambdaval.
 * @param mtx a celmatrix
 * @param lambda -
 */
void MTX_MultiplyRow(Matrix* mtx, int i, double lambda) {
    int j;
    for (j = 0; j < mtx->columns; j++) {
        mtx->numbers[i][j] *= lambda;
    }
}

/**Ket matrix osszeadasa.
 * Ha a ket matrix merete nem egyezett meg NULL-t ad vissza.
 *@param mtxA
 *@param mtxB
 */
Matrix* MTX_Sum(Matrix* mtxA, Matrix* mtxB) {
  if (SizeEqCheck(mtxA, mtxB)) {
    int i,j;
    Matrix* mtxC = MTX_Malloc(mtxA->rows, mtxA->columns);
    for ((i = 0); i < mtxC->rows; i++) {
      for ((j = 0); j < mtxC->columns; j++) {
        mtxC->numbers[i][j] = (mtxA->numbers[i][j] + mtxB->numbers[i][j]);
      }
    }
    return mtxC;
  } else {
    return NULL;
  }
}

/**Megnezi hogy osszeszorozhato e a ket parameterkent megadott matrix.
 */
bool MTX_MultiCheck(Matrix* mtxA, Matrix* mtxB) {
  if (mtxA->columns == mtxB->rows) {
    return true;
  } else {
    return false;
  }
}

/**Osszeszorozza a parameterkent atadott matrixokat es ezt egy uj matrixban tarolja el.
 * Ha nem osszeszorozhatoak NULL-t ad vissza.
 * @return az eredmeny
 */
Matrix* MTX_Multiply(Matrix* mtxA, Matrix* mtxB) {
  if (MTX_MultiCheck(mtxA, mtxB)) {
    double sum;
    int i,j,k;
    Matrix* mtxC = MTX_Malloc(mtxA->rows, mtxB->columns);
    for (i = 0; i < mtxA->rows; i++) {
      for (j = 0; j < mtxB->columns; j++) {
        for (k = 0; k < mtxA->columns; k++) {
            sum += mtxA->numbers[i][k] * mtxB->numbers[k][j];
          }
        mtxC->numbers[i][j] = sum;
        sum = 0;
        }
      }
    return mtxC;
  } else {
    return NULL;
  }
}

/**Megszorozza a matrixot egy skalarral.
 */
void MTX_ScalarMultiply(Matrix* mtxA, double lambda) {
  int i,j;
  for (i = 0; i < mtxA->rows; i++) {
    for (j = 0; j < mtxA->columns; j++) {
      mtxA->numbers[i][j]*=lambda;
    }
  }
}

/**Megszoroz egy matrixot egy skalarral, de abbol egy uj peldanyt csinal.
 *
 */
Matrix* MTX_ScalarMultiplyCopy(Matrix* mtxA, double lambda) {
  int i,j;
  Matrix* mtxS = MTX_Malloc(mtxA->rows, mtxA->columns);
  MTX_Copy(mtxS, mtxA);
  for (i = 0; i < mtxA->rows; i++) {
    for (j = 0; j < mtxA->columns; j++) {
      mtxS->numbers[i][j] *= lambda;
    }
  }
  return mtxS;
}

/**Ket matrix diadikus szorzata.
 *
 */
Matrix* MTX_DiadicMultiply(Matrix* mtxA, Matrix* mtxB) {
    if (mtxA->rows == 1 && mtxB->columns == 1) {
      Matrix* mtxC = MTX_Malloc(mtxB->rows, mtxA->columns);
      int i,j;
      for (i = 0; i < mtxA->columns; i ++) {
        for (j = 0; j < mtxB->rows; j++) {
          mtxC->numbers[i][j] = (mtxA->numbers[0][i] * mtxB->numbers[j][0]);
        }
      }
      return mtxC;
    } else if (mtxA->columns == 1 && mtxB->rows == 1) {
        Matrix* mtxC = MTX_Malloc(mtxA->rows, mtxB->columns);
        int i,j;
        for (i = 0; i < mtxA->rows; i++) {
          for (j = 0; j < mtxB->columns; j++) {
            mtxC->numbers[i][j] = (mtxA->numbers[i][0] * mtxB->numbers[0][j]);
          }
        }
        return mtxC;
    } else {
      return NULL;
    }
}


/*Matrix* MTX_KnoeckerMultiply(Matrix* mtxA, Matrix* mtxB) {
  Matrix* mtxTemp[mtxB->rows][mtxB->columns];
  int i,j,k,l;
  for (i = 0; i < mtxB->rows; i++) {
    for (j = 0; j < mtxB->columns; j++) {
      mtxTemp[i][j] = MTX_ScalarMultiplyCopy(mtxB, mtxA->numbers[i][j]);
    }
  }
  Matrix* mtxK = MTX_Malloc((mtxA->rows * mtxB->rows), (mtxA->columns * mtxB->columns));
  for (i = 0; i < mtxK->rows; i++) {
    for (j = 0; j < mtxK->columns; j++) {
      for (k = 0; k < mtxB->rows; k++) {
        for (l = 0; l < mtxB->columns; l++) {
          mtxK->numbers[i][j] = mtxTemp[i][j]->numbers[k][l];
        }
      }
    }
  }
  return(mtxK);
}*/


Matrix* MTX_HadamardMultiply(Matrix* mtxA, Matrix* mtxB) {
  if (SizeEqCheck(mtxA, mtxB)) {
    Matrix* mtxC = MTX_Malloc(mtxB->rows, mtxA->columns);
    int i,j;
    for (i = 0; i < mtxC->rows; i++) {
      for (j = 0; j < mtxC->columns; j++) {
        mtxC->numbers[i][j] = (mtxA->numbers[i][j] * mtxB->numbers[i][j]);
      }
    }
    return mtxC;
  } else {
    return NULL;
  }
}


Matrix* MTX_Transposition(Matrix* mtxA) {
  if (IsQuadratic(mtxA)) {
    int i,j;
    Matrix* mtxT = MTX_Malloc(mtxA->rows, mtxA->columns);
    for (i = 0; i < mtxT->rows; i++) {
      for (j = 0; j < mtxT->columns; j++) {
        mtxT->numbers[i][j] = mtxA->numbers[j][i];
      }
    }
    return mtxT;
  } else {
    return NULL;
  }
}

bool IsEqual(Matrix* mtxA, Matrix* mtxB){
    if (SizeEqCheck(mtxA, mtxB)) {
        int i,j = 0;
        bool equal = true;
        while (i < mtxA->rows && equal) {
            while (j > mtxA->columns && equal) {
                if (mtxA->numbers[i][j] == mtxB->numbers[i][j]) {
                    equal = false;
                }
                j++;
            }
            i++;
        }
        if (equal) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool IsInvertable(Matrix* mtxA) {
  if (IsQuadratic(mtxA)) {
    if (mtxA->determinant == 0) {
      return false;
    } else {
      return true;
    }
  } else {
    return false;
  }
}

bool IsQuadratic(Matrix* mtxQ) {
  if (mtxQ->rows == mtxQ->columns) {
    return true;
  } else {
    return false;
  }
}

bool IsDiagonal(Matrix* mtxD) {
  if (IsQuadratic(mtxD)) {
    bool mainDiagonal = true;
    bool zeroElements = true;
    int i,j = 0;
    while (i < mtxD->rows && mainDiagonal) {
      if (mtxD->numbers[i][i] == 0) {
        mainDiagonal = false;
      }
      i++;
    }
    i = 0;
    if(!mainDiagonal) {
      return false;
    } else {
      while (i < mtxD->rows && zeroElements) {
        while (j < mtxD->columns) {
          if (mtxD->numbers[i][j] != 0) {
            zeroElements = false;
          }
          j++;
        }
        i++;
      }
    }
    if (!zeroElements) {
      return false;
    } else {
      return true;
    }
  } else {
    return false;
  }
}

bool IsIdentity(Matrix* mtxI){
  if (IsDiagonal(mtxI)) {
    if (DiagonalType(mtxI, true)) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

bool DiagonalType(Matrix* mtxI, double type) {
  int i = 0;
  bool idential = true;
  while (i < mtxI->rows && idential) {
    if (mtxI->numbers[i][i] != type) {
      idential = false;
    }
    i++;
  }
  if (idential) {
    return true;
  } else {
    return false;
    }
}


bool IsSymmetric(Matrix* mtxS){
  if (mtxS == MTX_Transposition(mtxS)) {
    return true;
  } else {
    return false;
  }
}

bool IsAntiSymmetric(Matrix* mtxA) {
  if (IsEqual(mtxA, MTX_ScalarMultiplyCopy(MTX_Transposition(mtxA), -1))) {
    return true;
  } else {
    return false;
  }
}

bool IsUpperTriangular(Matrix* mtxT) {
  if (IsQuadratic(mtxT)) {
    bool zeroElements = true;
    int i,j = 0;
    while (i < mtxT->rows && zeroElements) {
      while (j < (i-1)) {
        if (mtxT->numbers[i][j] != 0) {
          zeroElements = false;
        }
        j++;
      }
      i++;
    }
    if (zeroElements) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

bool IsLowerTriangular(Matrix* mtxT){
  if(IsQuadratic(mtxT)){
    bool zeroElements = true;
    int i = 0;
    int j = (i - 1);
    while (i < mtxT->rows && zeroElements) {
      while (j < mtxT->columns) {
        if (mtxT->numbers[i][j] != 0) {
          zeroElements = false;
        }
        j++;
      }
      i++;
    }
    if (zeroElements) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}


bool IsTriangular(Matrix* mtxT) {
  if (IsUpperTriangular(mtxT) || IsLowerTriangular(mtxT)) {
    return true;
  } else {
    return false;
  }
}


bool IsStrictlyTriangular(Matrix* mtxT) {
  if (DiagonalType(mtxT, false) && (IsLowerTriangular(mtxT) || IsUpperTriangular(mtxT))) {
    return true;
  } else {
    return false;
  }
}


bool IsUnitriangular(Matrix* mtxT) {
  if (DiagonalType(mtxT, true) && (IsLowerTriangular(mtxT) || IsUpperTriangular(mtxT))) {
    return true;
  } else {
    return false;
  }
}

bool isZero(Matrix* mtxZ) {
    int i,j = 0;
    bool allZero = true;
    while ((i < mtxZ->rows) && allZero) {
        while (j < mtxZ->columns) {
            if (mtxZ->numbers[i][j] != 0) {
                allZero = false;
            }
            j++;
        }
        i++;
    }
    if (allZero) {
        return true;
    } else {
        return false;
    }
}
