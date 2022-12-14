#include "gauss.h"
#include <math.h>

static void swap_rows(Matrix* mat, Matrix* B, int r1, int r2)
{
    int col;
    for (col = 0; col < mat->width; col++)
    {
        double tmp = mat->data[r1][col];
        mat->data[r1][col] = mat->data[r2][col];
        mat->data[r2][col] = tmp;
    }

    double tmp = B->data[r1][0];
    B->data[r1][0] = B->data[r2][0];
    B->data[r2][0] = tmp;
}

static int eliminate_col(Matrix* mat, Matrix* B, int chosen_col)
{
    int chosen_row = chosen_col;

    // find main element
    int main_elem_row = chosen_row;
    double max_data_abs = mat->data[chosen_row][chosen_col];

    int row;
    for (row = chosen_row + 1; row < mat->height; row++)
    {
        double data_abs = fabs(mat->data[row][chosen_col]);
        if (data_abs > max_data_abs)
        {
            max_data_abs = data_abs;
            main_elem_row = row;
        }
    }
    swap_rows(mat, B, chosen_row, main_elem_row);


    if (mat->data[chosen_row][chosen_col] == 0)
    {
        return 1; // singular matrix
    }
    double multiplier = 1.0 / mat->data[chosen_row][chosen_col];
    for (row = chosen_row + 1; row < mat->height; row++)
    {
        int col;
        for (col = chosen_col; col < mat->width; col++)
        {
            mat->data[row][col] -= multiplier * mat->data[row - 1][col]; // rounding !!!
        }

        B->data[row][0] -= multiplier * B->data[row - 1][0];
    }

    return 0;
}

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem \n
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix* mat, Matrix* B)
{
    int col;
    for (col = 0; col <= mat->width - 2; col++)
    {
        if (eliminate_col(mat, B, col) == 1)
            return 1;
    }

    return 0;
}

