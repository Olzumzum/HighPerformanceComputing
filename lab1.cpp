#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <fstream>
#include <cstring>
#include <stdio.h>
using namespace std;

int searchMatrixDimension(int SIZE_MATRIZA)
{

    for (int i = 2; i < 10; i++)
    {
        if (SIZE_MATRIZA % i == 0)
        {
            SIZE_MATRIZA = i;
            break;
        }
    }

    return SIZE_MATRIZA;
}

/** чтение данных из файла */
int readerMatriz()
{
    setlocale(LC_ALL, "rus");

    //адрес файла
    string path = "data.txt";
    //пременная для файла
    ifstream fin;
    //переменная для чтения символа из файла
    char ch;
    //буфер данных
    vector<int> vectorBuffer(50);
    int indexBuffer = 0;
    //размерность массива
    int SIZE_MATRIZA = 0;
    //массив получаемых данных
    int matriza[SIZE_MATRIZA][SIZE_MATRIZA];
    const char minus = '-';
    //строка с цифрой матрицы
    string numberValue;

    fin.open(path);

    if (!fin.is_open())
        cout << "Ошибка открытия файла" << endl;
    else
    {
        cout << "Файл открыт" << endl;
        //записываем данные в буфер
        //пока не кончится файл
        while (fin.get(ch))
        {
            if (ch != ' ' && ch != ',')
            {
                //если число отрицательное - запомним минуc
                if (ch == minus)
                {
                    numberValue = minus;
                }
                else
                {
                    numberValue += ch;
                    vectorBuffer[indexBuffer] = atoi(numberValue.c_str());

                    //увеличиваем счетчик элементов
                    indexBuffer++;
                    //очищаем буфер
                    numberValue = "";
                }
            }
        }
        //получаем размерность матрицы
        SIZE_MATRIZA = searchMatrixDimension(indexBuffer);
        indexBuffer = 0;

        //закрываем файл с данными
        fin.close();

        //заполняем массив матрицы
        for (int i = 0; i < SIZE_MATRIZA; i++)
        {
            for (int j = 0; j < SIZE_MATRIZA; j++)
            {
                matriza[i][j] = vectorBuffer[indexBuffer++];
                cout << matriza[i][j];
            }
            cout << endl;
        }
    }

    return SIZE_MATRIZA;
}

/** поиск определителя матрицы */
int opredelitel(vector<int> minor)
{
    return minor[0] * minor[3] - minor[1] * minor[2];
}

/** подсчет определителя матрицы размерностью больше 2 */
int bigOpredelitel(int matriza[3][3], int MATRIZA_SIZE)
{
    //определитель матрицы
    int oprMatr = 0;
    //вектор значений для вычисления минора
    vector<int> vectorA(4);
    //индекс для вектора-минора
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
    else
    {
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

    readerMatriz();

    // cout << atoi(s);
    /** вычисление определителя */
    /* int oprMatr = bigOpredelitel(matriza, MATRIZA_SIZE);

    if (oprMatr == 0)
        cout << "Определитель равен нулю, обратная матрица не существует" << endl;
    else
        cout << "Определитель " << oprMatr << endl;
*/
    return 0;
}
