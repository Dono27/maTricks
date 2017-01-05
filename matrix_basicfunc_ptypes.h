#ifndef MATRIX_BASICFUNC_PTYPES_H_INCLUDED
#define MATRIX_BASICFUNC_PTYPES_H_INCLUDED
#include <stdbool.h>
#include "matrix_dtype.h"

Matrix* MTX_Malloc(int r, int c);
void MTX_DeleteRow(Matrix* mtx, int rowNo);
void MTX_ChangeRow(Matrix* mtx, int rowA, int rowB);
void MTX_Copy(Matrix* mtxTo, Matrix* mtxFrom);

/*Ha a megadott mátrix invertálható, akkor igaz értéket ad vissza.*/
bool IsInvertable(Matrix* mtxA);

/*Ha a megadott mátrix négyzetes, akkor igaz értéket ad vissza.*/
bool IsQuadratic(Matrix* mtxQ);

/*Ha a megadott mátrix diagonális, akkor igaz értéket ad vissza.*/
bool IsDiagonal(Matrix* mtxD);

/*Ha a megadott mátrixok típusa megegyezik, akkor összeadhatóak és igaz értéket ad vissza.*/
bool SizeEqCheck(Matrix* mtxA, Matrix* mtxB);

/*Ha a megadott mátrixok összeszorozhatóak, akkor igaz értéket ad vissza.*/
bool MultiCheck(Matrix* mtxA, Matrix* mtxB);

#endif // MATRIX_BASICFUNC_PTYPES_H_INCLUDED
