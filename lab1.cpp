#include <iostream>
#include <cstdlib>
#include <vector>
#include <math.h>
using namespace std;

/** поиск определителя матрицы */
int opredelitel(vector<int> minor)
{
    return minor[0] * minor[3] - minor[1] * minor[2];
}

int main()
{
    /** размерность матрицы */
    int MATRIZA_SIZE = 3;
    /** исходный вектор */
    int matriza[MATRIZA_SIZE][MATRIZA_SIZE] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};

    int oprMatr = 0;
    vector<int> vectorA(4);
    int indexVector = 0;

    for (int i = 0; i < MATRIZA_SIZE; i++)
    {

        for (int j = 1; j < MATRIZA_SIZE; j++)
        {

            for (int z = 0; z < MATRIZA_SIZE; z++)
            {
                if (z != i)
                {
                    vectorA[indexVector++] = matriza[j][z];
                }
            }
        }
        oprMatr += pow(-1, i) * matriza[0][i] * opredelitel(vectorA);
        indexVector = 0;
    }

    if (oprMatr == 0)
        cout << "Определитель равен нулю, обратная матрица не существует" << endl;
    else
        cout << "Определитель " << oprMatr << endl;

    return 0;
}
