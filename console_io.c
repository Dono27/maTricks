#include "datatypes.h"
#include "prototypes.h"
#include "includes.h"

Matrix* MTX_ConsoleInp(){
    printf("Adja meg hany sora illetve oszlopa legyen a matrixnak ebben a sorrendben!");
    int row,col;
    scanf(" %d %d",&row,&col);
    Matrix* newMtx = MTX_Malloc(row, col);

    int i,j;

    printf("\n    ");
    for (j = 0; j < col; j++){
        printf("%5d.",j + 1);
    }
    printf("\n");
    for(i = 0; i < row; i++){
        printf("%3d.",i + 1);
        for(j = 0; j < col; j++){
            scanf(" %lf",&newMtx->numbers[i][j]);
        }
    }

    return newMtx;
}

void MTX_ConsolePrintMtx(Matrix* mtx){
    int i,j;

    printf("\n    ");
    for (j = 0; j < mtx->columns; j++){
        printf("%5d.",j + 1);
    }
    printf("\n");
    for(i = 0; i < mtx->rows; i++){
        printf("%3d.",i + 1);
        for(j = 0; j < mtx->columns; j++){
            printf("%6.2f",mtx->numbers[i][j]);
        }
        printf("\n");
    }
}
