#ifndef MATRIX_BASICFUNC_PTYPES_H_INCLUDED
#define MATRIX_BASICFUNC_PTYPES_H_INCLUDED
#include <stdbool.h>
#include "matrix_dtype.h"

/*Store a matrix in memory*/
Matrix* matricks_malloc(int rows, int columns);

/*Egy tárolt mátri által foglalt memóriaterület felszabadítása*/
void matricks_free(Matrix* matrix);

Matrix* matricks_zeroes(int rows, int columns);

Matrix* matricks_ones(int rows, int columns);

Matrix* matricks_random(int rows, int columns);

/*Matrix* matricks_identiy(int rows, int columns);

Matrix* matricks_permutation(int rows, int columns);*/

/*Megadott sor törlése egy megadott mátrixból.*/
void matricks_delete_row(Matrix* matrix, int number_row);

/*Két megadott sor cseréje egy megadott mátrixban.*/
void matricks_change_row(Matrix* matrix, int row_A, int row_B);

/*Mátrix másolása egy másik, azonos méretű mátrixba.*/
void matricks_copy(Matrix* matrix_To, Matrix* matrix_From);

/*Sor skalárszorosának hozzáadása mátrixhoz.*/
void matricks_add_row(Matrix* matrix, int i, int t, double lambda);

/*Megadott sor szorzása skalárral egy mátrixban.*/
void matricks_multiply_row(Matrix* matrix, int i, double lambda);

/*Ha a megadott mátrixok típusa megegyezik, akkor összeadhatóak és igaz értéket ad vissza.*/
bool matricks_is_size_equal(Matrix* matrix_A, Matrix* matrix_B);

/*Ha a két megadott mátrix összeadható, akkor az összegmátrixot adja eredményül.*/
Matrix* matricks_sum(Matrix* matrix_A, Matrix* matrix_B);

/*Ha a megadott két mátrix összeszorozhatóak, akkor igaz értéket ad vissza.*/
bool matricks_multiply_check(Matrix* matrix_A, Matrix* matrix_B);

/*Ha a megadott két mátrix összeszorozható, akkor a szorzat eredménymátrixát adja eredményül. Címet ad vissza.*/
Matrix* matricks_multiply(Matrix* matrix_A, Matrix* matrix_B);

/*Megszorozza a megadott mátrixot egy skalárral. A mátrixot cím szerint szorozza meg.*/
void matricks_scalar_multiply(Matrix* matrix_A, double lambda);

/*Megszorozza a megadott mátrixot egy skalárral. A skalárral megszorzott mátrixot adja vissza, érték szerint.*/
Matrix* matricks_scalar_multiply_copy(Matrix* matrix_A, double lambda);

/*Két mátrix diadikus szorzatát adja vissza.*/
Matrix* matricks_diadic_multiply(Matrix* matrix_A, Matrix* matrix_B);

/*Két mátrix Knoecker-szorzatát adja vissza.*/
//Matrix* matricks_knoecker_multiply(Matrix* matrix_A, Matrix* matrix_B);

/*Két mátrix Hadamard-szorzatát adja vissza, amennyiben össze lehet szorozni őket (egyforma típusúak.)*/
Matrix* matricks_hadamard_multiply(Matrix* matrix_A, Matrix* matrix_B);

/*A megadott mátrix transzponáltját adja vissza.*/
Matrix* matricks_transposition(Matrix* matrix-A);

/*Ha a megadott két mátrix minden eleme egyenlő, akkor igaz értéket ad vissza.*/
bool matricks_is_equal(Matrix* matrix_A, Matrix* matrix_B);

/*Ha a megadott mátrix invertálható, akkor igaz értéket ad vissza.*/
bool matricks_is_invertable(Matrix* matrix_A);

/*Ha a megadott mátrix négyzetes, akkor igaz értéket ad vissza.*/
bool matricks_is_quadratic(Matrix* matrix_Q);

/*Ha a megadott mátrix diagonális, akkor igaz értéket ad vissza.*/
bool matricks_is_diagonal(Matrix* matrix_D);

/*Ha a megadott mátrix egységmátrix, akkor igaz értéket ad vissza.*/
bool matricks_is_idential(Matrix* matrix_I);

/*type: 0 or 1
  Ha a megadott mátrix főátlója csak a megadott (0 vagy 1) elemeket tartalmaz, akkor igaz értéket ad vissza.*/
bool matricks_diagonal_type(Matrix* matrix_I, double type);

/*Ha a megadott mátrix szimmetrikus, akkor igaz értéket ad vissza.*/
bool matricks_is_symmetric(Matrix* matrix_S);

/*Ha a megadott mátrix antiszimmetrikus (ferdén szimmetrikus), akkor igaz értéket ad vissza.*/
bool matricks_is_anti_symmetric(Matrix* matrix_A);

/*Igaz értéket ad vissza, ha a megadott mátrix főátlója alatti elemek mind nullák.*/
bool matricks_is_upper_triangular(Matrix* matrix_U);

/*Igaz értéket ad vissza, ha a megadott mátrix főátlója feletti elemek mind nullák.*/
bool matricks_is_lower_triangular(Matrix* matrix_L);

/*Ha a megadott mátrix háromszögmátrix (alsó vagy felső), akkor igaz értéket ad vissza.*/
bool matricks_is_triangular(Matrix* matrix_T);

/*Ha a megadott mátrix háromszögmátrix, főátlója csak nullákat tartalmaz, a nem a háromszöget alkotó elemek pedig mind nullák, akkor igaz értket ad vissza.*/
bool matricks_is_strictly_triangular(Matrix* matrix_T);

/*Ha a megadott mátrix háromszögmátrix, főátlója csak egyeseket tartalmaz, a nem háromszöget alkotó elemek pedig mind nullák, akkor igaz értéket ad vissza.*/
bool matricks_is_unitriangular(Matrix* matrix_T);

/*Ha a kapott mátrix nullmátrix (minden eleme nulla), akkor igaz értéket ad vissza.*/
bool matricks_is_zero(Matrix* matrix_Z);

bool matricks_is_diagonally_dominant(Matrix* matrix);

#endif // MATRIX_BASICFUNC_PTYPES_H_INCLUDED
