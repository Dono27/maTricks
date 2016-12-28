#include "datatypes.h"
#include <math.h>

Matrix* MTX_GaussElim(Matrix* mtxin){
    Matrix* mtxresult = MTX_Alloc(mtxin->rows, mtxin->columns);
    MTX_Copy(mtxresult,mtxin);

    //3 fazisu Gauss-eliminacio
    enum States{LOOP,CHANGEROW,FINISHED};

    enum States state = LOOP;
    bool finished = false;
    int i = 0,j = 0;
    int row,col;
    while(finished){
        switch(state){
            //Elso fazis
            case LOOP:
                //ha szam == 0, ugrunk a masodik fazisra
                if(fabs(0.f - mtxresult->numbers[i][j]) < 1.e-9){
                    state = CHANGEROW;
                    break;
                }
                //egyebkent beszorozzuk a sort az aktualis elem reciprokaval, es harmadik fazisba lepunk ha ez volt az utolso sor
                else{
                    for(col = j; col < mtx->columns; col++){
                        mtxresult->numbers[i][col] = mtxresult->numbers[i][col] * (1.f / mtxresult->numbers[i][j]);
                    }
                    if(i == mtxresult->rows - 1){
                        state = FINISHED;
                        break;
                    }
                }
                //kinullazzuk az alatta levo sorokat
                for(row = i + 1; row < mtxresult->rows; row++){
                    if(!(fabs(0.f - mtxresult->numbers[row][j]) < 1.e-9)){
                        for(col = j; col < mtxresult->columns; col++){
                            mtxresult->numbers[row][col] = mtxresult->numbers[row][col] - mtxresult->numbers[row][j]*mtxresult->numbers[i][col];
                        }
                    }
                }
                //ha mar nincs tobb oszlop, 3. fazisra ugras
                if(j == mtxresult->columns - 1){
                    state = FINISHED;
                    break;
                }
                i++,j++;
                break;
            case CHANGEROW:
                if(i < mtxresult->rows-1){
                    row = i + 1;
                    bool notzero = false;
                    while(!notzero && row < mtxresult->rows){
                        if(!(fabs(0.f - mtxresult->numbers[row][j]) < 1.e-9)){
                            notzero = true;
                        }
                        else row++;
                    }
                    if(notzero){
                        MTX_ChangeRow(&mtxresult,i,row);
                        state = LOOP;
                        break;
                    }
                }
                else if(j == mtxresult->columns - 1){
                    i--;
                    state = FINISHED;
                    break;
                }
                j++;
                state = LOOP;
                break;
            case FINISHED:
                break;
        }
    }
    
    return mtxresult;
}
