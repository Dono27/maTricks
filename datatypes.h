#ifndef DATATYPES_H_INCLUDED
#define DATATYPES_H_INCLUDED

/**A matrix.
*Ez az adatszerkezet egy matrix adatait tarolja el.
*/
typedef struct Matrix{
    int rows;           ///<sorok szama
    int columns;        ///<oszlopok szama
    double *numbers;    ///<a szamok
}Matrix;


#endif // DATATYPES_H_INCLUDED
