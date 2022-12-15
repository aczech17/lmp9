#include "gauss.h"
#include "backsubst.h"
#include "mat_io.h"
#include <stdlib.h>
#include <stdio.h>

#define FREE_MAT freeMatrix(A); freeMatrix(B); freeMatrix(x);

int main(int argc, char ** argv)
{
    if (argc < 3)
    {
        fprintf(stderr, "Podaj argumenty.\n");
        return 1;
    }

	Matrix* A = readFromFile(argv[1]);
	Matrix* B = readFromFile(argv[2]);

	if (A == NULL)
    {
        fprintf(stderr, "Nie udało się wczytać A.\n");
        return -1;
    }
	if (B == NULL)
    {
        fprintf(stderr, "Nie udało się wczytać B.\n");
        freeMatrix(A);
        return -2;
    }

	//printToScreen(A);
	//printToScreen(B);

	int res = eliminate(A, B);
    printf("\n\nMacierz A po eliminacji:\n");
    printToScreen(A);

    printf("Macierz B po eliminacji:\n");
    printToScreen(B);

	Matrix* x = createMatrix(B->height, 1);
    if(x == NULL)
    {
        fprintf(stderr,"Błąd! Nie mogłem utworzyć wektora wynikowego x.\n");
        freeMatrix(A);
        freeMatrix(B);
        return 1;
    }

    res = backsubst(x, A, B);
    switch (res)
    {
        case 1:
        {
            fprintf(stderr, "Błąd dzielenia przez 0.\n");
            FREE_MAT
            return 21;
        }
        case 2:
        {
            fprintf(stderr, "Nieprawidłowe wymiary macierzy.\n");
            FREE_MAT
            return 37;
        }
        case 0:
        {
            printf("\n\nMacierz x: \n");
            printToScreen(x);
        }
        default:
            break;
    }

    FREE_MAT
	return 0;
}
