#include "matrix_alg_ptypes.h"
#include "matrix_basicfunc_ptypes.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>


/**Gauss-eliminalo fuggveny.
*A parameterkent atadott mtx-ot atmasolja egy dinamikusan foglalt mtx-ba(nem az eredetit modositja),
*es azon Gauss-eliminaciot vegez majd visszater vele. Az algoritmus futasat lehet modositani a flag parameterrel.
*Ezek ertekei lehetnek a matrix_dtype.h-ban megtalalho makrok. Ha SOLVE_LINEAR_SYSTEM a flag akkor az eredeti
*mtx elvesz, hiszen a megoldas a visszateresi matrixrol olvashato le. Elotte masolatot kell csinalni!
*@param mtx Az eliminalando mtx
*@param flag Az alg. futasat befolyasolo flag
*@return A kiszamolt matrix
*/
Matrix* MTX_GaussElim(Matrix* mtx, const int flag){
    Matrix* mtxCopy = MTX_Malloc(mtx->rows, mtx->columns);
    MTX_Copy(mtxCopy, mtx);

    int maxCol, maxRow;
    double D, lambda;
    
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
            break;
        default:
            maxCol = mtx->columns;
            maxRow = mtx->rows;
            break;
    }

    //3 fazisu Gauss-eliminacio, gyakorlatilag egy allapotgep
    enum State{LOOP, CHANGEROW, FINISHED};
    enum State state = LOOP;
    
    //i,j a "kulso" valtozok(eszerint haladunk vegig a mtxon a gauss eliminacio algoritmusa szerint)
    //rowVar, colVar a muveletekhez szuksegesek
    bool finished = false;
    int i = 0,j = 0;
    int rowVar,colVar;
    Matrix* returnValue;
    while(!finished){
        switch(state){
            //Elso fazis
            case LOOP:
                //ha szam == 0, ugrunk a masodik fazisra
                if( !FloatCmp(mtxCopy->numbers[i][j], 0, 1.e-9) ){
                    state = CHANGEROW;
                    break;
                }
                //egyebkent beszorozzuk a sort az aktualis elem reciprokaval, es harmadik fazisba lepunk ha ez volt az utolso sor
                else{
                    //determinans szamolasanal amikor egy sort leosztunk akkor a determinans ertek is megvaltozik
                    //ezt kovetjuk vegig a D valtozoval
                    if(flag == CALCULATE_DET){
                        D *= mtxCopy->numbers[i][j];
                    }
                    lambda = 1 / mtxCopy->numbers[i][j];
                    MTX_MultiplyRow(mtxCopy, i, lambda);
                    if(i == mtxCopy->rows - 1){
                        state = FINISHED;
                        break;
                    }
                }
                //kinullazzuk az alatta levo sorokat
                for(rowVar = i + 1; rowVar < mtxCopy->rows; rowVar++){
                    //ha az oszlop alatt 0 all, nem is kell kinullazni
                    if( FloatCmp(mtxCopy->numbers[rowVar][j],0,1.e-9) ){
                        lambda = -mtxCopy->numbers[rowVar][j];
                        MTX_AddRow(mtxCopy, i, rowVar, lambda);
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
                if(i < mtxCopy->rows - 1){
                    rowVar = i + 1;
                    bool notzero = false;
                    while(!notzero && rowVar < mtxCopy->rows){
                        if( FloatCmp(mtxCopy->numbers[rowVar][j], 0, 1.e-9) ){
                            notzero = true;
                        }
                        else rowVar++;
                    }
                    if(notzero){
                        if(flag == CALCULATE_DET){
                            D = -D;
                        }
                        MTX_ChangeRow(mtxCopy,i,rowVar);
                        state = LOOP;
                        break;
                    }
                    else if(flag == CALCULATE_DET){
                        D = 0;
                        state = FINISHED;
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
                if(i < mtxCopy->rows - 1){
                    for(rowVar = i + 1; rowVar < mtxCopy->rows; rowVar++){
                        if(flag == SOLVE_LINEAR_SYSTEM){
                            if(FloatCmp(mtxCopy->numbers[rowVar][mtx->columns-1], 0, 1.e-9)){
                                break;
                            }
                        }
                        MTX_DeleteRow(mtxCopy,rowVar);
                    }
                }
                switch(flag){
                    case SOLVE_LINEAR_SYSTEM:
                        //Redukalt lepcsos alak
                        for(i = mtxCopy->rows - 1; i > 0; i--){
                           for(colVar = 0; colVar < maxCol; colVar++){
                                if(mtxCopy->numbers[i][colVar] != 0){
                                    j = colVar;
                                    break;
                                }
                            }
                            for(rowVar = i - 1 ; rowVar >= 0; rowVar--){
                                lambda = -mtxCopy->numbers[rowVar][j];
                                MTX_AddRow(mtxCopy, i, rowVar, lambda);
                            }
                        }
                        returnValue = mtxCopy;
                        break;
                    case CALCULATE_DET:
                        mtx->determinant = D;
                        MTX_Free(mtxCopy);
                        returnValue = mtx;
                        break;

                }
                finished = true;
                //printf("A matrix lepcsos alaku!");
                break;
        }
    }
    return returnValue;
}

int FloatCmp(double a, double b,double precision){
    if(fabs(a - b) < precision) return 0;
    else if(a > b)              return 1;
    else                        return -1;
}
