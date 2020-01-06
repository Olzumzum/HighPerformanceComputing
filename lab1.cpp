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

/** подсчет определителя матрицы размерностью больше 2 */
int bigOpredelitel(int matriza[3][3], int MATRIZA_SIZE)
{
    int oprMatr = 0;
    vector<int> vectorA(4);
    int indexVector = 0;

    if (MATRIZA_SIZE == 2)
    {
        vectorA = {matriza[0][0], matriza[0][1], matriza[1][0], matriza[1][1]};
        return opredelitel(vectorA);
    }
    else if (MATRIZA_SIZE > 2)
    {
        for (int i = 0; i < MATRIZA_SIZE; i++)
        {

            for (int j = 1; j < MATRIZA_SIZE; j++)
            {

                for (int z = 0; z < MATRIZA_SIZE; z++)
                {
                    if (z != i)
                    {
                        //получаем значения для вычисления определителя
                        vectorA[indexVector++] = matriza[j][z];
                    }
                }
            }
            //считаем определитель
            oprMatr += pow(-1, i) * matriza[0][i] * opredelitel(vectorA);
            indexVector = 0;
        }

        return oprMatr;
    }
    else {
        //ОБРАБОТАТЬ
        cout << "Неккоректно задана матрица" << endl;

    }
}

int main()
{
    /** размерность матрицы */
    int MATRIZA_SIZE = 3;
    /** исходный вектор */
    int matriza[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};

    /** вычисление оператора */
    int oprMatr = bigOpredelitel(matriza, MATRIZA_SIZE);
   

    if (oprMatr == 0)
        cout << "Определитель равен нулю, обратная матрица не существует" << endl;
    else
        cout << "Определитель " << oprMatr << endl;

    return 0;
}
