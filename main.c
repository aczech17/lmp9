#include "gauss.h"
#include "backsubst.h"
#include "mat_io.h"
#include <stdlib.h>
#include <stdio.h>


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
        return -1;
	if (B == NULL)
        return -2;

	printToScreen(A);
	printToScreen(B);

	int res = eliminate(A, B);
	Matrix* x = createMatrix(B->height, 1);
    if(x == NULL)
    {
        fprintf(stderr,"Błąd! Nie mogłem utworzyć wektora wynikowego x.\n");
        freeMatrix(A);
        freeMatrix(B);
        return 1;
    }

    res = backsubst(x, A, B);
    printToScreen(x);


    freeMatrix(x);
	freeMatrix(A);
	freeMatrix(B);

	return 0;
}
