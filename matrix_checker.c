#include <stdlib.h>
#include <stdbool.h>
#include "datatypes.h"

/*Ha az mtxA mátrix determinánsa 0 (nem invertálható), akkor hamis értéket ad vissza, ha nem nulla, akkor igazat.*/
bool IsInvertable(Matrix* mtxA){
  if(!IsQuadratic(mtxA)){
    return false; //Ha az mtxA mátrix nem kvadratikus, akkor nem is inverálható.
  }else{

  }
}

/*Ha az mtxQ mátrix sorainak és oszlopainak száma megegyezik, akkor kvadratikus.*/
bool IsQuadratic(Matrix* mtxQ){
  if(mtxD.rows==mtxD.columns){
    return true;
  }else{
    return false;
  }
}

/*Ha az mtxD mátrix nem kvadratikus, akkor nem lehet diagonális. Egyébként akkor az, hogyha csak a főátlójában tartalmaz nem nulla elemeket*/
bool IsDiagonal(Matrix* mtxD){
  if(!IsQuadratic(mtxD)){
    return false;
  }else{

  }
}

/*mtxA és mtxB mátrixok akkor és csakis akkor adhatóak össze, ha azonos típusúak (soraik és oszlopaik száma megegyezik).*/
bool AddCheck(Matrix* mtxA, Matrix* mtxB){
  if(mtxA.rows != mtxB.rows || mtxA.columns != mtxB.columns){
    return false;
  }else{
    return true;
  }
}

/*mtxA és mtxB mátrix akkor és csakis szorozhatóak össze (Knoecker-szorzat), ha mtxA mátrix oszlopainak száma megegyezik mtxB mátrix sorainak számával.*/
bool MultiCheck(Matrix* mtxA, Matrix* mtxB){
  if(mtxA.columns != mtxB.rows){
    return false;
  }else{
    return true;
  }
}
