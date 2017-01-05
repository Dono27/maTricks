#include "matrix_alg_ptypes.h"
#include "matrix_basicfunc_ptypes.h"
#include <math.h>
#include <stdbool.h>

Matrix* MTX_GaussElim(Matrix* mtxin,const int flag){
    Matrix* mtxresult = MTX_Malloc(mtxin->rows, mtxin->columns);
    MTX_Copy(mtxresult, mtxin);

    int maxCol,maxRow;
    switch(flag){
        case SOLVE_LINEAR_SYSTEM:
            maxCol = mtxresult->columns - 1;
            maxRow = mtxresult->rows;
            break;
        default:
            maxCol = mtxresult->columns;
            maxRow = mtxresult->rows;
            break;
    }
    //3 fazisu Gauss-eliminacio, gyakorlatilag egy allapotgep
    enum State{LOOP,CHANGEROW,FINISHED};

    double temp,div;

    enum State state = LOOP;
    bool finished = false;
    int i = 0,j = 0;
    int rowVar,colVar;
    while(!finished){
        switch(state){
            //Elso fazis
            case LOOP:
                //ha szam == 0, ugrunk a masodik fazisra
                if( !FloatCmp(mtxresult->numbers[i][j], 0, 1.e-9) ){
                    state = CHANGEROW;
                    break;
                }
                //egyebkent beszorozzuk a sort az aktualis elem reciprokaval, es harmadik fazisba lepunk ha ez volt az utolso sor
                else{
                    temp = mtxresult->numbers[i][j];
                    for(colVar = j; colVar < mtxresult->columns; colVar++){
                        mtxresult->numbers[i][colVar] /= temp;
                    }
                    if(i == mtxresult->rows - 1){
                        state = FINISHED;
                        break;
                    }
                }
                //kinullazzuk az alatta levo sorokat
                for(rowVar = i + 1; rowVar < mtxresult->rows; rowVar++){
                    //ha az oszlop alatt 0 all, nem is kell kinullazni
                    if( FloatCmp(mtxresult->numbers[rowVar][j],0,1.e-9) ){
                        temp = mtxresult->numbers[rowVar][j];
                        for(colVar = j; colVar < mtxresult->columns; colVar++){
                            mtxresult->numbers[rowVar][colVar] = mtxresult->numbers[rowVar][colVar] - temp * mtxresult->numbers[i][colVar];
                        }
                    }
                }
                //ha mar nincs tobb oszlop, 3. fazisra ugras
                if(j == maxCol - 1){
                    state = FINISHED;
                    break;
                }
                i++,j++;
                break;
            //2. fazis: sorcsere
            case CHANGEROW:
                //Ha van meg sor amelyre az adott oszlopban levo elem nem 0, akkor csere
                if(i < mtxresult->rows - 1){
                    rowVar = i + 1;
                    bool notzero = false;
                    while(!notzero && rowVar < mtxresult->rows){
                        if( FloatCmp(mtxresult->numbers[rowVar][j], 0, 1.e-9) ){
                            notzero = true;
                        }
                        else rowVar++;
                    }
                    if(notzero){
                        MTX_ChangeRow(mtxresult,i,rowVar);
                        state = LOOP;
                        break;
                    }
                }
                //elertuk az utolso oszlopot -> vegeztunk
                if(j == maxCol - 1){
                    i--;
                    state = FINISHED;
                    break;
                }
                //egyebkent folytatodjon a ciklus
                j++;
                state = LOOP;
                break;
            case FINISHED:
                //a maradek csupa nulla sorok torlese
                if(i < mtxresult->rows - 1){
                    for(rowVar = i + 1; rowVar < mtxresult->rows; rowVar++){
                        MTX_DeleteRow(mtxresult,rowVar);
                    }
                }
                finished = true;
                //printf("A matrix lepcsos alaku!");
                break;
        }
    }
    //RLA
    if(flag == SOLVE_LINEAR_SYSTEM){
        for(i = mtxresult->rows - 1; i > 0; i--){
           for(colVar = 0; colVar < maxCol; colVar++){
                if(mtxresult->numbers[i][colVar] != 0){
                    j = colVar;
                    break;
                }
            }
            for(rowVar = i - 1 ; rowVar >= 0; rowVar--){
                temp = mtxresult->numbers[rowVar][j];
                for(colVar = j; colVar < mtxresult->columns; colVar++){
                    mtxresult->numbers[rowVar][colVar] -= temp * mtxresult->numbers[i][colVar];
                }
            }
        }

    }
    return mtxresult;
}

int FloatCmp(double a, double b,double precision){
    if(fabs(a - b) < precision) return 0;
    else if(a > b)              return 1;
    else                        return -1;
}
