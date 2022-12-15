#include "backsubst.h"
#include <stdio.h>
/**
 * Zwraca 0 - wsteczne podstawienie zakonczone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 * Zwraca 2 - błąd nieprawidłowych rozmiarów macierzy
 */

int backsubst(Matrix* x, Matrix* mat, Matrix* b)
{
    int i,j;
    int current_row;
    int current_column;
    double sum;
    int check;

    check = check_if_good(mat, x, b);

    if( check == 0 )
        return 2;


    current_row = mat->height - 1;
    current_column = current_row + 1;


    for( current_row = mat->height - 1; current_row >= 0; current_row-- )
    {
        sum = 0;

        if( mat->data[current_row][current_row] == 0 ) // Sprawdzamy czy na diagonali jest 0
            return 1;
        
        for( current_column = current_row + 1; current_column < mat->width; current_column++ )
        {
            sum += mat->data[current_row][current_column] * x->data[current_column][0];

        }

        x->data[current_row][0] = ( b->data[current_row][0] - sum ) / mat->data[current_row][current_row];
    }


    return 0;

}

int check_if_good( Matrix *mat, Matrix *x, Matrix *b )
{
    if( mat->height != mat->width )
        return 0;
    if( mat->height != x->height )
        return 0;
    if( mat->height != b->height )
        return 0;
    if( mat->height != mat->width )
        return 0;
    if ( b->width != 1 )
        return 0;
    if( x->width != 1 )
        return 0;
    return 1;
}

