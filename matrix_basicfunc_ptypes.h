#ifndef MATRIX_BASICFUNC_PTYPES_H_INCLUDED
#define MATRIX_BASICFUNC_PTYPES_H_INCLUDED
#include <stdbool.h>
#include "matrix_dtype.h"

/*Mátrix tárolása a memóriában*/
Matrix* MTX_Malloc(int r, int c);

/*Egy tárolt mátri által foglalt memóriaterület felszabadítása*/
void MTX_Free(Matrix* mtx);

/*Megadott sor törlése egy megadott mátrixból.*/
void MTX_DeleteRow(Matrix* mtx, int rowNo);

/*Két megadott sor cseréje egy megadott mátrixban.*/
void MTX_ChangeRow(Matrix* mtx, int rowA, int rowB);

/*Mátrix másolása egy másik, azonos méretű mátrixba.*/
void MTX_Copy(Matrix* mtxTo, Matrix* mtxFrom);

/*Sor skalárszorosának hozzáadása mátrixhoz.*/
void MTX_AddRow(Matrix* mtx, int i, int t, double lambda);

/*Megadott sor szorzása skalárral egy mátrixban.*/
void MTX_MultiplyRow(Matrix* mtx, int i, double lambda);

/*Ha a megadott mátrixok típusa megegyezik, akkor összeadhatóak és igaz értéket ad vissza.*/
bool SizeEqCheck(Matrix* mtxA, Matrix* mtxB);

/*Ha a két megadott mátrix összeadható, akkor az összegmátrixot adja eredményül.*/
Matrix* MTX_Sum(Matrix* mtxA, Matrix* mtxB);

/*Ha a megadott két mátrix összeszorozhatóak, akkor igaz értéket ad vissza.*/
bool MultiCheck(Matrix* mtxA, Matrix* mtxB);

/*Ha a megadott két mátrix összeszorozható, akkor a szorzat eredménymátrixát adja eredményül. Címet ad vissza.*/
Matrix* MTX_Multiply(Matrix* mtxA, Matrix* mtxB);

/*Megszorozza a megadott mátrixot egy skalárral. A mátrixot cím szerint szorozza meg.*/
void MTX_ScalarMultiply(Matrix* mtxA, double lambda);

/*Megszorozza a megadott mátrixot egy skalárral. A skalárral megszorzott mátrixot adja vissza, érték szerint.*/
Matrix* MTX_ScalarMultiplyCopy(Matrix* mtxA, double lambda);

/*Két mátrix diadikus szorzatát adja vissza.*/
Matrix* MTX_DiadicMultiply(Matrix* mtxA, Matrix* mtxB);

/*Két mátrix Knoecker-szorzatát adja vissza.*/
//Matrix* MTX_KnoeckerMultiply(Matrix* mtxA, Matrix* mtxB);

/*Két mátrix Hadamard-szorzatát adja vissza, amennyiben össze lehet szorozni őket (egyforma típusúak.)*/
Matrix* MTX_HadamardMultiply(Matrix* mtxA, Matrix* mtxB);

/*A megadott mátrix transzponáltját adja vissza.*/
Matrix* MTX_Transposition(Matrix* mtxA);

/*Ha a megadott két mátrix minden eleme egyenlő, akkor igaz értéket ad vissza.*/
bool IsEqual(Matrix* mtxA, Matrix* mtxB);

/*Ha a megadott mátrix invertálható, akkor igaz értéket ad vissza.*/
bool IsInvertable(Matrix* mtxA);

/*Ha a megadott mátrix négyzetes, akkor igaz értéket ad vissza.*/
bool IsQuadratic(Matrix* mtxQ);

/*Ha a megadott mátrix diagonális, akkor igaz értéket ad vissza.*/
bool IsDiagonal(Matrix* mtxD);

/*Ha a megadott mátrix egységmátrix, akkor igaz értéket ad vissza.*/
bool IsIdentity(Matrix* mtxI);

/*type: 0 vagy 1
  Ha a megadott mátrix főátlója csak a megadott (0 vagy 1) elemeket tartalmaz, akkor igaz értéket ad vissza.*/
bool DiagonalType(Matrix* mtxI, double type);

/*Ha a megadott mátrix szimmetrikus, akkor igaz értéket ad vissza.*/
bool IsSymmetric(Matrix* mtxS);

/*Ha a megadott mátrix antiszimmetrikus (ferdén szimmetrikus), akkor igaz értéket ad vissza.*/
bool IsAntiSymmetric(Matrix* mtxA);

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

/*Ha a kapott mátrix nullmátrix (minden eleme nulla), akkor igaz értéket ad vissza.*/
bool IsZero(Matrix* mtxZ);

#endif // MATRIX_BASICFUNC_PTYPES_H_INCLUDED
