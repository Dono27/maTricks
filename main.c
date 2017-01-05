#include "MTX.h"

int main(void){
    Matrix* mtx = MTX_ConsoleInp();

    MTX_ConsolePrintMtx(mtx);

    mtx = MTX_GaussElim(mtx, SOLVE_LINEAR_SYSTEM);

    MTX_ConsolePrintMtx(mtx);





    return 0;
}
