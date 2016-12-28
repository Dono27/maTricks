#include "datatypes.h"
#include <math.h>

Matrix* GaussElimination(Matrix* mtxin){
    Matrix* mtxresult = AllocateNewMtx(mtxin->rows, mtxin->columns);
    CopyMtx(mtxresult,mtxin);

    //3 fazisu Gauss-eliminacio
    enum States{FIRST,SECOND,THIRD};

    enum States state = FIRST;
    bool finished = false;
    int i = 0,j = 0;
    int row,col;
    while(finished){
        switch(state){
            //Elso fazis
            case FIRST:
                //ha szam == 0, ugrunk a masodik fazisra
                if(fabs(0.f - mtxresult->numbers[i][j]) < 1.e-9){
                    state = SECOND;
                    break;
                }
                //egyebkent beszorozzuk a sort a reciprokaval, es harmadik fazisba lepunk ha ez volt az utolso sor
                else{
                    for(col = 0; col < mtx->columns; col++){
                        mtxresult->numbers[i][col] = mtxresult->numbers[i][col] * (1.f / mtxresult->numbers[i][j]);
                    }
                    if(i == mtxresult->rows - 1){
                        state = THIRD;
                        break;
                    }
                }
                //kinullazzuk az alatta levo sorokat
                for(row = i + 1; row < mtxresult->rows; row++){
                    for(col = j; col < mtxresult->columns; col++){
                        if(!(fabs(0.f - mtxresult->numbers[row][j]) < 1.e-9)){
                            mtxresult->numbers[row][col] = mtxresult->numbers[row][col] - mtxresult->numbers[row][j]*mtxresult->numbers[i][col];
                        }
                    }
                }
                //ha mar nincs tobb oszlop, 3. fazisra ugras
                if(j == mtxresult->columns - 1){
                    state = THIRD;
                    break;
                }
                i++,j++;
                break;
            case SECOND:
                break;
            case THIRD:
                break;
        }
    }
}
