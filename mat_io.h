#ifndef MAT_IO_H
#define MAT_IO_H

typedef struct Matrix
{
    int height, width;
    double** data;
}Matrix;

/**
 * Zwraca 0 - udalo sie wczytac
 * Zwraca 1 - podczas wczytywania wystapil blad
 */

Matrix* readFromFile(char* filename);
void printToScreen(Matrix* mat);

Matrix* createMatrix(int height, int width);
void freeMatrix(Matrix* mat);

#endif // MAT_IO_H
