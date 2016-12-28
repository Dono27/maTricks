#ifndef MATRIX_CHECKER_H_INCLUDED
#define MATRIX_CHECKER_H_INCLUDED

/*Ha a megadott mátrix invertálható, akkor igaz értéket ad vissza.*/
bool IsInvertable(Matrix* mtxA);

/*Ha a megadott mátrix négyzetes, akkor igaz értéket ad vissza.*/
bool IsQuadratic(Matrix* mtxQ);

/*Ha a megadott mátrix diagonális, akkor igaz értéket ad vissza.*/
bool IsDiagonal(Matrix* mtxD);

/*Ha a megadott mátrixok típusa megegyezik, akkor összeadhatóak és igaz értéket ad vissza.*/
bool AddCheck(Matrix* mtxA, Matrix* mtxB);

/*Ha a megadott mátrixok összeszorozhatóak, akkor igaz értéket ad vissza.*/
bool MultiCheck(Matrix* mtxA, Matrix* mtxB);

#endif // MATRIX_CHECKER_H_INCLUDED
