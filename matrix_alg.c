#include "matrix_alg_ptypes.h"
#include "matrix_basicfunc_ptypes.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>


/**Gauss-eliminalo fuggveny.
*A pm-kent atadott mtx-ot atmasolja egy dinamikusan foglalt mtx-ba(nem az eredetit modositja),
*es azon Gauss-eliminaciot vegez majd visszater vele. Az algoritmus futasat lehet modositani a flag parameterrel.
*Ezek ertekei lehetnek a matrix_dtype.h-ban megtalalho makrok
*@param mtx Az eliminalando mtx
*@param flag Az alg. futasat befolyasolo flag
*/
Matrix* MTX_GaussElim(Matrix* mtx, const int flag){
    Matrix* mtxCopy = MTX_Malloc(mtx->rows, mtx->columns);
    MTX_Copy(mtxCopy, mtx);

    int maxCol,maxRow;
    double D,lambda;
    switch(flag){
        case SOLVE_LINEAR_SYSTEM:
            //eggyel kevesebb oszlopig kell menni! (A|b) alak
            maxCol = mtx->columns - 1;
            maxRow = mtx->rows;
            break;
        case CALCULATE_DET:
            //ha nem negyzetes nincs ertelme det szamolni
            if(!IsQuadratic(mtx)){
                return NULL;
            }
            D = 1;
            maxCol = mtx->columns;
            maxRow = mtx->rows;
        default:
            maxCol = mtx->columns;
            maxRow = mtx->rows;
            break;
    }

    //3 fazisu Gauss-eliminacio, gyakorlatilag egy allapotgep
    enum State{LOOP,CHANGEROW,FINISHED};
    enum State state = LOOP;

    bool finished = false;
    //i,j a "kulso" valtozok(eszerint haladunk vegig a mtxon)
    //rowVar, colVar a muveletekhez szuksegesek
    int i = 0,j = 0;
    int rowVar,colVar;
    while(!finished){
        switch(state){
            //Elso fazis
            case LOOP:
                //ha szam == 0, ugrunk a masodik fazisra
                if( !FloatCmp(mtx->numbers[i][j], 0, 1.e-9) ){
                    state = CHANGEROW;
                    break;
                }
                //egyebkent beszorozzuk a sort az aktualis elem reciprokaval, es harmadik fazisba lepunk ha ez volt az utolso sor
                else{
                    //determinans szamolasanal amikor egy sort leosztunk akkor a determinans ertek is megvaltozik
                    //ezt kovetjuk vegig a D valtozoval
                    if(flag == CALCULATE_DET){
                        D *= mtx->numbers[i][j];
                    }
                    lambda = 1 / mtx->numbers[i][j];
                    MTX_MultiplyRow(mtx, i, lambda);
                    if(i == mtx->rows - 1){
                        state = FINISHED;
                        break;
                    }
                }
                //kinullazzuk az alatta levo sorokat
                for(rowVar = i + 1; rowVar < mtx->rows; rowVar++){
                    //ha az oszlop alatt 0 all, nem is kell kinullazni
                    if( FloatCmp(mtx->numbers[rowVar][j],0,1.e-9) ){
                        lambda = -mtx->numbers[rowVar][j];
                        MTX_AddRow(mtx, i, rowVar, lambda);
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
                if(i < mtx->rows - 1){
                    rowVar = i + 1;
                    bool notzero = false;
                    while(!notzero && rowVar < mtx->rows){
                        if( FloatCmp(mtx->numbers[rowVar][j], 0, 1.e-9) ){
                            notzero = true;
                        }
                        else rowVar++;
                    }
                    if(notzero){
                        if(flag == CALCULATE_DET){
                            D = -D;
                        }
                        MTX_ChangeRow(mtx,i,rowVar);
                        state = LOOP;
                        break;
                    }
                    else{
                        if(flag == CALCULATE_DET){
                            D = 0;
                            state = FINISHED;
                            break;
                        }
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
                if(i < mtx->rows - 1){
                    for(rowVar = i + 1; rowVar < mtx->rows; rowVar++){
                        if(flag == SOLVE_LINEAR_SYSTEM){
                            if(FloatCmp(mtx->numbers[rowVar][mtx->columns-1], 0, 1.e-9)){
                                break;
                            }
                        }
                        MTX_DeleteRow(mtx,rowVar);
                    }
                }

                switch(flag){
                    case SOLVE_LINEAR_SYSTEM:
                        //Redukalt lepcsos alak
                        for(i = mtx->rows - 1; i > 0; i--){
                           for(colVar = 0; colVar < maxCol; colVar++){
                                if(mtx->numbers[i][colVar] != 0){
                                    j = colVar;
                                    break;
                                }
                            }
                            for(rowVar = i - 1 ; rowVar >= 0; rowVar--){
                                lambda = -mtx->numbers[rowVar][j];
                                MTX_AddRow(mtx, i, rowVar, lambda);
                            }
                        }
                        MTX_Copy(mtxCopy, mtx);
                        break;
                    case CALCULATE_DET:
                        mtxCopy->determinant = D;
                        break;

                }
                MTX_Free(mtx);
                finished = true;
                //printf("A matrix lepcsos alaku!");
                break;
        }
    }
    return mtxCopy;
}

int FloatCmp(double a, double b,double precision){
    if(fabs(a - b) < precision) return 0;
    else if(a > b)              return 1;
    else                        return -1;
}
