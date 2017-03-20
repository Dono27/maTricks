#ifndef MATRIX_ALG_PTYPE_H_INCLUDED
#define MATRIX_ALG_PTYPE_H_INCLUDED
#include "matrix_dtype.h"

int FloatCmp(double a, double b,double precision);
Matrix* MTX_GaussElim(Matrix* mtxin, const int flag);

#endif // MATRIX_ALG_PTYPE_H_INCLUDED
