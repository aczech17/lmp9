#include "mat_io.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Zwraca <> NULL - udalo sie wczytac
 * Zwraca == NULL - podczas wczytywania wystapil blad
 */

Matrix* readFromFile(char* filename)
{
    FILE* input = fopen(filename, "r");
    if (input == NULL)
    {
        return NULL;
    }

    int height, width;
    fscanf(input, "%d %d", &height, &width);
    Matrix* mat = createMatrix(height, width);
    if (mat == NULL)
    {
        fclose(input);
        return NULL;
    }

    int row, col;
    for (row = 0; row < height; row++)
        for (col = 0; col < width; col++)
            fscanf(input, "%lf", &(mat->data[row][col]));


    fclose(input);
    return mat;
}

void printToScreen(Matrix* mat)
{
	printf("[ \n");

    int row, col;
	for (row = 0; row < mat->height; row++)
    {
		printf("  ");
		for (col = 0; col < mat->width; col++)
        {
			printf("%f ", mat->data[row][col]);
		}
		printf("; \n");
	}
	printf("]\n");
}

Matrix* createMatrix(int height, int width)
{
    Matrix* mat = (Matrix*) malloc(sizeof(Matrix));
    if (mat == NULL)
    {
        return NULL;
    }

    mat->height = height;
    mat->width = width;
    mat->data = (double**) malloc(sizeof(double*) * height);

    int i;
    for (i=0; i < height; i++)
    {
        mat->data[i] = (double*) malloc(sizeof(double) * width);
    }

    return mat;
}

void freeMatrix(Matrix * mat)
{
    int i;
	for (i = 0; i < mat->height; i++)
		free(mat->data[i]);

	free(mat->data);
	free(mat);
}
