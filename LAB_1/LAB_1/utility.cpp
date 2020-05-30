#include "Header.h"
double* Gauss(double** matrix, int n, int m)
{
    //Метод Гаусса
    //Прямой ход, приведение к верхнетреугольному виду
    double  tmp;
    double* xx = new double[m];
    int k;

    for (int i = 0; i < n; i++)
    {
        tmp = matrix[i][i];
        for (int j = n; j >= i; j--)
            matrix[i][j] /= tmp;
        for (int j = i + 1; j < n; j++)
        {
            tmp = matrix[j][i];
            for (k = n; k >= i; k--)
                matrix[j][k] -= tmp * matrix[i][k];
        }
    }
    /*обратный ход*/
    xx[n - 1] = matrix[n - 1][n];
    for (int i = n - 2; i >= 0; i--)
    {
        xx[i] = matrix[i][n];
        for (int j = i + 1; j < n; j++)
        {
            xx[i] -= matrix[i][j] * xx[j];
        }
    }
    return xx;
}