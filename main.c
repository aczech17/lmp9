#include "gauss.h"
#include "backsubst.h"
#include "mat_io.h"
#include <stdlib.h>
#include <stdio.h>

#define FREE_MAT freeMatrix(A); freeMatrix(B); freeMatrix(X);

int main(int argc, char ** argv)
{
    if (argc < 3)
    {
        fprintf(stderr, "Podaj argumenty.\n");
        return 1;
    }

    Matrix* A = NULL;
    Matrix* B = NULL;
    Matrix* X = NULL;

	A = readFromFile(argv[1]);
	B = readFromFile(argv[2]);

	if (A == NULL)
    {
        fprintf(stderr, "Nie udało się wczytać A.\n");
        return -1;
    }

	if (B == NULL)
    {
        fprintf(stderr, "Nie udało się wczytać B.\n");
        FREE_MAT
        return -2;
    }

    printf("Macierz A:\n");
	printToScreen(A);

    printf("\nMacierz B:\n");
	printToScreen(B);

	int res = eliminate(A, B);
    if (res == 1)
    {
        fprintf(stderr, "Nie udało się dokonać eliminacji Gaussa.\n");
        FREE_MAT
        return 1;
    }


    printf("\nMacierz A po eliminacji:\n");
    printToScreen(A);

    printf("\nMacierz B po eliminacji:\n");
    printToScreen(B);


	X = createMatrix(B->height, 1);
    if(X == NULL)
    {
        fprintf(stderr,"Błąd! Nie mogłem utworzyć wektora wynikowego x.\n");
        FREE_MAT
        return 1;
    }

    res = backsubst(X, A, B);
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
            printf("\nMacierz X: \n");
            printToScreen(X);
        }
        default:
            break;
    }

    FREE_MAT
	return 0;
}
