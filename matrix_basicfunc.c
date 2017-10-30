#include "matrix_dtype.h"
#include "matrix_basicfunc_ptypes.h"
#include <stdlib.h>
#include <time.h>

/**Dinamikusan teruletet foglal egy Matrix-nak.
*@param rows - number of rows
*@param columns - number of coluns
*@return a lefoglalt teruletre mutato Matrix tipusu pointer
*/
Matrix* matricks_malloc(int rows, int columns) {
    Matrix* new_matrix = malloc(sizeof(Matrix));
    new_matrix->columns = columns;
    new_matrix->rows = rows;
    new_matrix->numbers = (double**)malloc(rows * sizeof(double*) );
    new_matrix->numbers[0] = (double*)malloc(rows * columns * sizeof(double) );
    int iterator_row;
    for (iterator_row = 1; iterator_row < rows; iterator_row++) {
        new_matrix->numbers[iterator_row] = new_matrix->numbers[0] + iterator_row * columns;
    }
    return new_matrix;
}

/**Felszabaditja a parameterkent atadott matrixot.
*@param matrix a felszabaditando matrix
*/
void matricks_free(Matrix* matrix) {
    free(matrix->numbers[0]);
    free(matrix->numbers);
    free(matrix);
}

Matrix* matricks_zeroes(int rows, int columns) {
    Matrix* matrix = matricks_malloc(rows, columns);
    int iterator_row, iterator_column;
    for (iterator_row = 0; iterator_row < matrix->rows; iterator_row++) {
        for (iterator_column = 0; iterator_column < matrix->columns; iterator_column++) {
            matrix[iterator_row][iterator_column] = 0;
        }
    }
}

Matrix* matricks_ones(int rows, int columns) {
    Matrix* matrix = matricks_malloc(rows, columns);
    int iterator_row, iterator_column;
    for (iterator_row = 0; iterator_row < matrix->rows; iterator_row++) {
        for (iterator_column = 0; iterator_column < matrix->columns; iterator_column++) {
            matrix[iterator_row][iterator_column] = 1;
        }
    }
}

Matrix* matricks_random(int rows, int columns) {
    Matrix* matrix = matricks_malloc(rows, columns);
    int iterator_row, iterator_column;

    srand(time(NULL));

    for (iterator_row = 0; iterator_row < matrix->rows; iterator_row++) {
        for (iterator_column = 0; iterator_column < matrix->columns; iterator_column++) {
            matrix[iterator_row][iterator_column] = rand() % 100;
        }
    }
}

/*Matrix* matricks_identiy(int rows, int columns) {
}

Matrix* matricks_permutation(int rows, int columns) {
    Matrix* matrix = matricks_malloc(rows, columns);
}*/

/**Torli a megadott sort a matrixbol.
*@param matrix a celmatrix
*@param number_row a torlendo sor indexe
*/
void matricks_delete_row(Matrix* matrix, int row_number) {
    double* toDelete = matrix->numbers[row_number];
    int i;
    for (i = row_number; i < matrix->rows - 1; i++) {
        matrix->numbers[i] = matrix->numbers[i + 1];
    }
    free(toDelete);
    matrix->rows--;
}

/**Megcsereli a megadott sorokat a matrixban.
*@param matrix a celmatrix
*@param row_a az egyik cserelendo sor
*@param row_b a masik cserelndo sor
*/
void matricks_change_row(Matrix* matrix, int row_a, int row_b) {
    double* row_temp = matrix->numbers[row_a];
    matrix->numbers[rowA] = matrix->numbers[row_b];
    matrix->numbers[rowB] = row_temp;
}

/**Returns true if the size of matrix_A and matrix_B are the same.
*@param matrix_A is a matrix.
*@param matrix_B is another matrix.
*/
bool matricks_is_size_equal(Matrix* matrix_B, Matrix* matrix_B) {
  if ((matrix_A->rows == matrix_B->rows) && (matrix_A->columns == matrix_B->columns)) {
    return true;
  } else {
    return false;
  }
}

/**Copies a matrix to another.
 *@param matrix_To is a matrix, the destination matrix.
 *@param matrix_From is a matrix, the source matrix.
 */
void matricks_copy(Matrix* matrix_To, Matrix* matrix_From) {
    if (matricks_is_size_equal(matrix_To, matrix_From)) {
        int iterator_row, iterator_column;
        for (iterator_row = 0; iterator_row < matrix_From->rows; iterator_row++) {
            for (iterator_column = 0; iterator_column < matrix_From->columns; iterator_column++) {
                matrix_To->numbers[iterator_row][iterator_column] = matrix_From->numbers[iterator_row][iterator_column];
            }
        }
    }
}

/**Az i-edik sor lambdaszorosanak hozzaadasa a t-edik sorhoz.
 * @param matrix a celmatrix
 * @param i hozzaadando sor indexe
 * @param t a sor amihez hozzaadunk
 * @param lambda lambda * i. sor
 */
void matricks_add_row(Matrix* matrix, int i, int t, double lambda) {
    int iterator_column;
    for (iterator_column = 0; iterator_column < mtx->columns; iterator_column++) {
        matrix->numbers[t][iterator_column] += lambda * matrix->numbers[i][iterator_column];
    }
}

/**A matrix egyik soranak megszorzasa lambdaval.
 * @param matrix a celmatrix
 * @param lambda -
 */
void matricks_multiply_row(Matrix* matrix, int i, double lambda) {
    int iterator_column;
    for (iterator_column = 0; iterator_column < matrix->columns; iterator_column++) {
        matrix->numbers[i][iterator_column] *= lambda;
    }
}

/**Returns the sum of two matrices.
 * Ha a ket matrix merete nem egyezett meg NULL-t ad vissza.
 *@param matrix_A is a matrix.
 *@param matrix_B is another matrix.
 */
Matrix* matricks_sum(Matrix* matrix_A, Matrix* matrix_B) {
  if (matricks_is_size_equal(matrix_A, matrix_B) ) {
    int iterator_row, iterator_column;
    Matrix* matrix_C = matricks_malloc(matrix_A->rows, matrix_B->columns);
    for (iterator_row = 0; iterator_row < matrix_C->rows; iterator_row++) {
      for (iterator_column = 0; iterator_column < matrix_C->columns; iterator_column++) {
        matrix_C->numbers[iterator_row][iterator_column] = (matrix_A->numbers[iterator_row][iterator_column] + matrix_B->numbers[iterator_row][iterator_column] );
      }
    }
    return matrix_C;
  } else {
    return NULL;
  }
}

/**Megnezi hogy osszeszorozhato e a ket parameterkent megadott matrix.
 * @param matrix_A is a matrix.
 * @param matrix_B is another matrix.
 */
bool MTX_MultiCheck(Matrix* matrix_A, Matrix* matrix_B) {
  if (matrix_A->columns == matrix_B->rows) {
    return true;
  } else {
    return false;
  }
}

/**Osszeszorozza a parameterkent atadott matrixokat es ezt egy uj matrixban tarolja el.
 * Ha nem osszeszorozhatoak NULL-t ad vissza.
 * @return az eredmeny
 */
Matrix* matricks_multiply(Matrix* matrix_A, Matrix* matrix_B) {
  if (matricks_multiply_check(matrix_A, matrix_B) ) {
    double sum;
    int i, j, k;
    Matrix* matrix_C = matricks_malloc(matrix_A->rows, matrix_B->columns);
    for (i = 0; i < matrix_A->rows; i++) {
      for (j = 0; j < matrix_B->columns; j++) {
        for (k = 0; k < matrix_A->columns; k++) {
            sum += matrix_A->numbers[i][k] * matrix_B->numbers[k][j];
          }
        matrix_C->numbers[i][j] = sum;
        sum = 0;
        }
      }
    return matrix_C;
  } else {
    return NULL;
  }
}

/**Megszorozza a matrixot egy skalarral.
 * @param matrix_A is a matrix.
 * @param lambda a skalar.
 */
void matricks_scalar_multiply(Matrix* matrix_A, double lambda) {
  int iterator_row, iterator_column;
  for (iterator_row = 0; iterator_row < matrix_A->rows; iterator_row++) {
    for (iterator_column = 0;iterator_column < matrix_A->columns; iterator_column++) {
      matrix_A->numbers[iterator_row][iterator_column] *= lambda;
    }
  }
}

/**Megszoroz egy matrixot egy skalarral, de abbol egy uj peldanyt csinal.
 *
 */
Matrix* matricks_scalar_multiplyCopy(Matrix* matrix_A, double lambda) {
  int iterator_row, iterator_column;
  Matrix* matrix_S = matricks_malloc(matrix_A->rows, matrix_A->columns);
  matricks_copy(matrix_S, matrix_A);
  for (iterator_row = 0; iterator_row < matrix_A->rows; iterator_row++) {
    for (iterator_column = 0; iterator_column < matrix_A->columns; iterator_column++) {
      matrix_S->numbers[iterator_row][iterator_column] *= lambda;
    }
  }
  return matrix_S;
}

/**Ket matrix diadikus szorzata.
 * @param matrix_A is a matrix.
 * @param matrix_B is another matrix.
 * @return the result matrix.
 */
Matrix* matricks_diadic_multiply(Matrix* matrix_A, Matrix* matrix_B) {
    if (matrix_A->rows == 1 && matrix_B->columns == 1) {
      Matrix* matrix_C = matricks_malloc(matrix_B->rows, matrix_A->columns);
      int i,j;
      for (i = 0; i < matrix_A->columns; i ++) {
        for (j = 0; j < matrix_B->rows; j++) {
          matrix_C->numbers[i][j] = (matrix_A->numbers[0][i] * matrix_B->numbers[j][0]);
        }
      }
      return matrix_C;
    } else if (matrix_A->columns == 1 && matrix_B->rows == 1) {
        Matrix* matrix_C = matricks_malloc(matrix_A->rows, matrix_B->columns);
        int i,j;
        for (i = 0; i < matrix_A->rows; i++) {
          for (j = 0; j < matrix_B->columns; j++) {
            matrix_C->numbers[i][j] = (matrix_A->numbers[i][0] * matrix_B->numbers[0][j]);
          }
        }
        return matrix_C;
    } else {
      return NULL;
    }
}

/**Két mátrix Knoecker-szorzata
 * @param matrix_A is a matrix.
 * @param matrix_B is another matrix.
 * @return az eredmenymatrix.
*/
Matrix* matricks_knoecker_multiply(Matrix* matrix_A, Matrix* matrix_B) {
  int rowK = matrix_A->rows * matrix_B->rows;
  int colK = matrix_A->columns * matrix_B->columns;
  Matrix* mtxK = matricks_malloc(rowK, colK);
  Matrix* mtxTemp = matricks_malloc(matrix_B->rows, matrix_B->columns);
  int rowA, rowB, colA, colB;
  int rowAdd = 0;
  int colAdd = 0;
  for (colA = 0; colA < matrix_A->columns; colA++) {
    for (rowA = 0; rowA < matrix_A->rows; rowA++) {
        mtxTemp = matricks_scalar_multiplyCopy(matrix_B, matrix_A->numbers[rowA][colA]);
        for (colB = 0; colB < matrix_B->columns; colB++) {
            for (rowB = 0; rowB < matrix_B->rows; rowB++) {
                mtxK->numbers[rowB + rowAdd][colB+colAdd] = mtxTemp->numbers[rowB][colB];
            }
        }
        //free(mtxTemp);
        colAdd += matrix_B->columns;
        rowA = 0;
        colA = 0;
    }
    rowAdd += matrix_B->rows;
    colAdd = 0;
  }
  return(mtxK);
}

/**Ket matrix Hadamard-szorzata.
 * @param matrix_A is a matrix
 * @param matrix_B is another matrix
 * @return the result, if there is no result then returns NULL
*/
Matrix* matricks_hadamard_multiply(Matrix* matrix_A, Matrix* matrix_B) {
  if (matricks_is_size_equal(matrix_A, matrix_B)) {
    Matrix* matrix_C = matricks_malloc(matrix_B->rows, matrix_A->columns);
    int i, j;
    for (i = 0; i < matrix_C->rows; i++) {
      for (j = 0; j < matrix_C->columns; j++) {
        matrix_C->numbers[i][j] = (matrix_A->numbers[i][j] * matrix_B->numbers[i][j] );
      }
    }
    return matrix_C;
  } else {
    return NULL;
  }
}

/**A parameterkent atadott matrix transzponaltjat adja vissza
 * @param matrix_A is a matrix.
 * @return matrix_A transzponaltja, if matrix_A is not quadratic, then returns NULL.
*/
Matrix* matricks_transposition(Matrix* matrix_A) {
  if (matricks_is_quadratic(matrix_A) ) {
    int i, j;
    Matrix* matrix_T = matricks_malloc(matrix_A->rows, matrix_A->columns);
    for (i = 0; i < matrix_T->rows; i++) {
      for (j = 0; j < matrix_T->columns; j++) {
        matrix_T->numbers[i][j] = matrix_A->numbers[j][i];
      }
    }
    return matrix_T;
  } else {
    return NULL;
  }
}

bool matricks_is_equal(Matrix* matrix_A, Matrix* matrix_B) {
    if (matricks_is_size_equal(matrix_A, matrix_B)) {
        int iterator_row, iterator_column = 0;
        bool is_equal = true;
        while (iterator_row < matrix_A->rows && equal) {
            while (iterator_column > matrix_A->columns && equal) {
                if (matrix_A->numbers[iterator_row][iterator_column] == matrix_B->numbers[iterator_row][iterator_column]) {
                    is_equal = false;
                }
                iterator_column++;
            }
            iterator_row++;
        }
        if (is_equal) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

/**A parameterkent atadott matrixrol eldonti, hogy invertalhato-e.
 * @param matrix_A is a matrix
*/
bool MTX_IsInvertable(Matrix* matrix_A) {
  if (matricks_is_quadratic(matrix_A) ) {
    if (matrix_A->determinant == 0) {
      return false;
    } else {
      return true;
    }
  } else {
    return false;
  }
}

/** A parameterkent atadott matrixrol eldonti, hogy negyzetes-e.
 * @param matrix_Q is a matrix.
*/
bool matricks_is_quadratic(Matrix* matrix_Q) {
  if (matrix_Q->rows == matrix_Q->columns) {
    return true;
  } else {
    return false;
  }
}

/**A parameterkent atadott maitrixrol eldonti, hogy atlos-e.
 * @param matrix_D is a matrix.
*/
bool matricks_is_diagonal(Matrix* matrix_D) {
  if (matricks_is_quadratic(matrix_D)) {
    bool mainDiagonal = true;
    bool zeroElements = true;
    int iterator_row, iterator_column = 0;
    while (iterator_row < matrix_D->rows && mainDiagonal) {
      if (matrix_D->numbers[iterator_row][iterator_row] == 0) {
        mainDiagonal = false;
      }
      iterator_row++;
    }
    iterator_row = 0;
    if (!mainDiagonal) {
      return false;
    } else {
      while (iterator_row < matrix_D->rows && zeroElements) {
        while (iterator_column < matrix_D->columns) {
          if (matrix_D->numbers[iterator_row][iterator_column] != 0) {
            zeroElements = false;
          }
          iterator_column++;
        }
        iterator_row++;
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

/**A parameterkent atadott matrixrol eldonti, hogy egysegmatrix-e.
 * @param matrix_I is a matrix.
*/
bool MTX_IsIdentity(Matrix* matrix_I) {
  if (matricks_is_diagonal(matrix_I) ) {
    if (MTX_DiagonalType(matrix_I, 1) ) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

/**A parameterkent atadott matrixr foatlojarol allapitja meg, hogy csak egyesek vagy nullak alkotjak-e.
 * @param mtxI is a matrix.
 * @param type if true then checks for ones, if false then checks for zeroes.
*/
bool MTX_DiagonalType(Matrix* matrix_I, double type) {
  int iterator = 0;
  bool idential = true;
  while (iterator < matrix_I->rows && idential) {
    if (matrix_I->numbers[iterator][iterator] != type) {
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

/**A parameterkent atadott matrixrol megallapitja, hogy szimmetrikus-e.
 * @param matrix_S is a matrix.
*/
bool MTX_IsSymmetric(Matrix* matrix_S){
  if (matricks_is_equal(matrix_S, matricks_transposition(matrix_S) ) {
    return true;
  } else {
    return false;
  }
}

/**A parameterkent atadott matrixrol megallapitja, hogy antiszimmetrikus-e.
 * @param matrix_A is a matrix.
*/
bool MTX_IsAntiSymmetric(Matrix* matrix_A) {
  if (matricks_is_equal(matrix_A, matricks_scalar_multiplyCopy(matricks_transposition(matrix_A), -1) ) ) {
    return true;
  } else {
    return false;
  }
}

/**A parameterkent atadott matrixrol megallapitja, hogy felso haromszogmatrix-e.
 * @param matrix_U is a matrix.
*/
bool MTX_IsUpperTriangular(Matrix* matrix_U) {
  if (matricks_is_quadratic(matrix_U) ) {
    bool zeroElements = true;
    int iterator_row, iterator_column = 0;
    while (iterator_row < matrix_U->rows && zeroElements) {
      while (iterator_column < (iterator_row-1) ) {
        if (matrix_U->numbers[iterator_row][iterator_column] != 0) {
          zeroElements = false;
        }
        iterator_column++;
      }
      iterator_row++;
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

/**A parameterkent atadott matrixrol megallapitja, hogy also haromszogmatrix-e.
 * @param matrix_L is matrix.
*/
bool matricks_is_lower_triangular(Matrix* matrix_L) {
  if (matricks_is_quadratic(matrix_L) ) {
    bool zero_elements = true;
    int iterator_row = 0;
    int iterator_column = (iterator_row - 1);
    while (iterator_row < matrix_L->rows && zeroElements) {
      while (iterator_column < matrix_L->columns) {
        if (matrix_L->numbers[iterator_row][iterator_column] != 0) {
          zero-elements = false;
        }
        iterator_column++;
      }
      iterator_row++;
    }
    if (zero_elements) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

/**A parameterkent atadott matrixrol megallapitja, hogy haromszogmatrix-e.
 * @param matrix_T is a matrix.
*/
bool matricks_is_triangular(Matrix* mtxT) {
  if (MTX_IsUpperTriangular(matrix_T) || matricks_is_lower_triangular(matrix_T) ) {
    return true;
  } else {
    return false;
  }
}

/**A parameterkent atadott matrixrol megallapitja, hogy foatlojaban csak nullak vannak-e es haromszogmatrix-e.
 * @param matrix_T is a matrix.
*/
bool matricks_is_strictly_triangular(Matrix* matrix_T) {
  if (MTX_DiagonalType(matrix_T, 0) && matricks_is_triangular(matrix_T) ) {
    return true;
  } else {
    return false;
  }
}

/**A parameterkent atadott matrixrol megallapitja, hogy unitriangularis matrix-e (felso- vagy also haromszogmatrix es csak foatlojaban vannak nem 0 elemei, illetve azok mind 1-esek.
 * @param matrix_T is a matrix.
*/
bool matricks_is_unitriangular(Matrix* matrix_T) {
  if (MTX_DiagonalType(matrix_T, 1) && matricks_is_triangular(matrix_T) ) {
    return true;
  } else {
    return false;
  }
}

/**A parameterkent atadott matrixrol megallapitja, hogy zerusmatrix-e.
 * @param matrix_Z is a matrix.
*/
bool matricks_is_zero(Matrix* matrix_Z) {
    int iterator_row, iterator_column = 0;
    bool is_all_zero = true;
    while ( (iterator_row < matrix_Z->rows) && is_all_zero) {
        while ( (iterator_column < matrix_Z->columns) && allZero) {
            if (matrix_Z->numbers[iterator_row][iterator_column] != 0) {
                is_all_zero = false;
            }
            iterator_column++;
        }
        iterator_row++;
    }
    if (is_all_zero) {
        return true;
    } else {
        return false;
    }
}

bool matricks_is_diagonally_dominant(Matrix* matrix) {
    bool is_diagonal_dominant = true;
    int iterator_row, iterator_column = 0;

    double temp_diagonal_element;
    double temp_sum_row = 0;

    while (iterator_row < matrix->rows && is_diagonal_dominant) {
        temp_diagonal_element = matrix[iterator_row][iterator_row];
        while (iterator_column < matrix->columns) {
            temp_sum_row += matrix[iterator_row][iterator_column];
            iterator_column++;
        }
        if (temp_diagonal_element < temp_sum_row) {
            is_diagonal_dominant = false;
        }
        temp_sum_row = 0;
        iterator_row++;
    }
}
