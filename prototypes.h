#ifndef PROTOTYPES_H_INCLUDED
#define PROTOTYPES_H_INCLUDED

Matrix* MTX_Malloc(int r, int c);
void MTX_DeleteRow(Matrix* mtx, int rowNo);
void MTX_ChangeRow(Matrix* mtx, int rowA, int rowB);
void MTX_Copy(Matrix* mtxTo, Matrix* mtxFrom);

int FloatCmp(double a, double b,double precision);


void MTX_ConsolePrintMtx(Matrix* mtx);
Matrix* MTX_ConsoleInp();
#endif // PROTOTYPES_H_INCLUDED
