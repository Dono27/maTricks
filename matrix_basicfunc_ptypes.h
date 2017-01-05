#ifndef MATRIX_BASICFUNC_PTYPES_H_INCLUDED
#define MATRIX_BASICFUNC_PTYPES_H_INCLUDED
#include <stdbool.h>
#include "matrix_dtype.h"

Matrix* MTX_Malloc(int r, int c);
void MTX_DeleteRow(Matrix* mtx, int rowNo);
void MTX_ChangeRow(Matrix* mtx, int rowA, int rowB);
void MTX_Copy(Matrix* mtxTo, Matrix* mtxFrom);

/*Ha a megadott m�trix invert�lhat�, akkor igaz �rt�ket ad vissza.*/
bool IsInvertable(Matrix* mtxA);

/*Ha a megadott m�trix n�gyzetes, akkor igaz �rt�ket ad vissza.*/
bool IsQuadratic(Matrix* mtxQ);

/*Ha a megadott m�trix diagon�lis, akkor igaz �rt�ket ad vissza.*/
bool IsDiagonal(Matrix* mtxD);

/*Ha a megadott m�trixok t�pusa megegyezik, akkor �sszeadhat�ak �s igaz �rt�ket ad vissza.*/
bool SizeEqCheck(Matrix* mtxA, Matrix* mtxB);

/*Ha a megadott m�trixok �sszeszorozhat�ak, akkor igaz �rt�ket ad vissza.*/
bool MultiCheck(Matrix* mtxA, Matrix* mtxB);

#endif // MATRIX_BASICFUNC_PTYPES_H_INCLUDED
