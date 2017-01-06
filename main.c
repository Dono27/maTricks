#include "MTX.h"
#include <stdio.h>

int main(void){
    Matrix* mtx = MTX_ConsoleInp();

    MTX_ConsolePrintMtx(mtx);

    mtx = MTX_GaussElim(mtx, CALCULATE_DET);

    MTX_ConsolePrintMtx(mtx);
    printf("\nDeterminans : %f", mtx->determinant);

    return 0;
}
