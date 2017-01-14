#ifndef MATRIX_BASICFUNC_PTYPES_H_INCLUDED
#define MATRIX_BASICFUNC_PTYPES_H_INCLUDED
#include <stdbool.h>
#include "matrix_dtype.h"

/**/
Matrix* MTX_Malloc(int r, int c);

/**/
void MTX_Free(Matrix* mtx);

/**/
void MTX_DeleteRow(Matrix* mtx, int rowNo);

/**/
void MTX_ChangeRow(Matrix* mtx, int rowA, int rowB);

/**/
void MTX_Copy(Matrix* mtxTo, Matrix* mtxFrom);

/**/
void MTX_AddRow(Matrix* mtx, int i, int t, double lambda);

/**/
void MTX_MultiplyRow(Matrix* mtx, int i, double lambda);

/*Ha a megadott mátrix invertálható, akkor igaz értéket ad vissza.*/
bool IsInvertable(Matrix* mtxA);

/*Ha a megadott mátrix négyzetes, akkor igaz értéket ad vissza.*/
bool IsQuadratic(Matrix* mtxQ);

/*Ha a megadott mátrix diagonális, akkor igaz értéket ad vissza.*/
bool IsDiagonal(Matrix* mtxD);

/*Ha a megadott mátrix egységmátrix, akkor igaz értéket ad vissza.*/
bool IsIdentity(Matrix* mtxI);

/*type: false = 0, true = 1
  Ha a megadott mátrix főátlója csak a megadott (0 vagy 1) elemeket tartalmaz, akkor igaz értéket ad vissza.*/
bool DiagonalType(Matrix* mtxI, bool type);

/*Ha a megadott mátrix szimmetrikus, akkor igaz értéket ad vissza.*/
//bool IsSymmetric(Matrix* mtxS);

/*Ha a megadott mátrix antiszimmetrikus (ferdén szimmetrikus), akkor igaz értéket ad vissza.*/
//bool IsAntiSymmetric(Matrix* mtxA);

/*Igaz értéket ad vissza, ha a megadott mátrix főátlója alatti elemek mind nullák.*/
bool IsUpperTriangle(Matrix* mtxT);

/*Igaz értéket ad vissza, ha a megadott mátrix főátlója feletti elemek mind nullák.*/
bool IsLowerTriangle(Matrix* mtxT);

/*Ha a megadott mátrix háromszögmátrix (alsó vagy felső), akkor igaz értéket ad vissza.*/
bool IsTriangular(Matrix* mtxT);

/*Ha a megadott mátrix háromszögmátrix, főátlója csak nullákat tartalmaz, a nem a háromszöget alkotó elemek pedig mind nullák, akkor igaz értket ad vissza.*/
bool IsStrictlyTriangular(Matrix* mtxT);

/*Ha a megadott mátrix háromszögmátrix, főátlója csak egyeseket tartalmaz, a nem háromszöget alkotó elemek pedig mind nullák, akkor igaz értéket ad vissza.*/
bool IsUnitriangular(Matrix* mtxT);

/*Ha a kapott mátrix zérómátrix (minden eleme nulla), akkor igaz értéket ad vissza.*/
bool IsZero(Matrix* mtxZ);

/*Ha a megadott mátrixok típusa megegyezik, akkor összeadhatóak és igaz értéket ad vissza.*/
bool SizeEqCheck(Matrix* mtxA, Matrix* mtxB);

/*Ha a megadott mátrixok összeszorozhatóak, akkor igaz értéket ad vissza.*/
bool MultiCheck(Matrix* mtxA, Matrix* mtxB);

#endif // MATRIX_BASICFUNC_PTYPES_H_INCLUDED
