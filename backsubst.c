#include "backsubst.h"

/**
 * Zwraca 0 - wsteczne podstawienie zakonczone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 * Zwraca 2 - błąd nieprawidłowych rozmiarów macierzy
 */
int backsubst(Matrix* x, Matrix* mat, Matrix* b)
{
    // mat * x = b
    int correct_dims = mat->width == mat->height &&
            mat->width == x->height &&
            mat->width == b->height &&
            x->width == 1 &&
            b->width == 1;

    if (!correct_dims)
        return 2;

    int row;
    for (row = x->height - 1; row >= 0; row--)
    {
        double val = b->data[row][0];
        int col;
        for (col = row + 1; col < mat->width; col++)
        {
            val -= mat->data[row][col] * x->data[col][0];
        }

        if (mat->data[row][row] == 0)
            return 1;

        val /= mat->data[row][row];

        x->data[row][0] = val;
    }

    return 0;
}


