#include "gauss.h"
#include <math.h>

static void swap_rows(Matrix* mat, Matrix* B, int r1, int r2)
{
    if (r1 == r2)
        return;

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
    int row, col;

    int chosen_row = chosen_col;

    // find main element
    int main_elem_row = chosen_row;
    double max_abs = fabs(mat->data[chosen_row][chosen_col]);
    for (row = chosen_row + 1; row < mat->height; row++)
    {
        double potential_max = fabs(mat->data[row][chosen_col]);
        if (potential_max > max_abs)
        {
            max_abs = potential_max;
            main_elem_row = row;
        }
    }

    swap_rows(mat, B, chosen_row, main_elem_row);

    if (mat->data[chosen_row][chosen_col] == 0) // cannot divide by 0
    {
        return 1;
    }

    for (row = chosen_row + 1; row < mat->height; row++)
    {
        double multiplier = mat->data[row][chosen_col] / mat->data[chosen_row][chosen_col];

        for (col = 0; col < mat->width; col++)
        {
            mat->data[row][col] -= multiplier * mat->data[chosen_row][col];
        }

        B->data[row][0] -= multiplier * B->data[chosen_row][0];
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
        int fail = eliminate_col(mat, B, col);
        if (fail)
            return 1;
    }

    return 0;
}

