#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <time.h>
#include <omp.h>
using namespace std;

//загрузка данных

/** 
 * чтение данных из файла 
 * возвращает вектор значений матрицы
 */
vector<int> loadFile()
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
                    numberValue = minus;
                else
                {
                    numberValue += ch;
                    vectorBuffer[indexBuffer++] = atoi(numberValue.c_str());

                    //очищаем буфер
                    numberValue = "";
                }
            }
        }
        //закрываем файл с данными
        fin.close();

        vector<int> vectorValue(indexBuffer);
        for (int i = 0; i < indexBuffer; i++)
        {
            vectorValue[i] = vectorBuffer[i];
        }

        return vectorValue;
    }
}

/**
 * возвращает размерность матрицы
 */
int getSizeMatrix(vector<int> vectorValue)
{
    int sizeMatrix = vectorValue.size();

    for (int i = 2; i < 10; i++)
    {
        if (sizeMatrix % i == 0)
        {
            sizeMatrix = i;
            break;
        }
    }
    return sizeMatrix;
}

/** 
 * заполняем матрицу значениями 
 */
void fillMatrix(int **matrix, int sizeMatrix, vector<int> vectorValue)
{
    int indexVerctorValue = 0;
    //заполняем массив матрицы
    for (int i = 0; i < sizeMatrix; i++)
    {
        matrix[i] = new int[sizeMatrix];

        for (int j = 0; j < sizeMatrix; j++)
        {
            matrix[i][j] = vectorValue[indexVerctorValue++];
        }
        cout << endl;
    }
}
//--------------------------------------------------------------------------------------------
//подсчет определителей

/** 
 * поиск минора
 * */
int opredelitel(vector<int> minor)
{
    return minor[0] * minor[3] - minor[1] * minor[2];
}

/**  
 * подсчет определителя матрицы
 */
int bigOpredelitel(int **matriza, int MATRIZA_SIZE)
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

//-------------------------------------------------------------------------------------------
//поиск матрицы миноров
void searchMatrixMinor(int **minorMatrix, int **matrix, int sizeMatrix)
{
    vector<int> vectorMinor(4);

    for (int iRow = 0; iRow < sizeMatrix; iRow++) //строчка
    {
         minorMatrix[iRow] = new int[sizeMatrix];

        for (int iColm = 0; iColm < sizeMatrix; iColm++) //столбец
        {
            int indexVector = 0;
            for (int i = 0; i < sizeMatrix; i++) //строчка
            {
                if (iRow != i)
                {
                    for (int j = 0; j < sizeMatrix; j++) //столбец
                    {
                        if (iColm != j)
                        {
                            //заполнение вектора для получения минора
                            vectorMinor[indexVector++] = matrix[i][j];
                        }
                    }
                }
            }
           
            //подсчет определителя
            minorMatrix[iRow][iColm] = opredelitel(vectorMinor);
        } 
    }
}
//-------------------------------------------------------------------------------
//матрица алгебраических дополнений
void counterAlgebraicComplement(int **minorMatrix, int sizeMatrix)
{
    for (int i = 0; i < sizeMatrix; i++)
    {
        for (int j = 0; j < sizeMatrix; j++)
        {
            if ((i + j) % 2 != 0)
                minorMatrix[i][j] *= -1;
        }
    }
}

//------------------------------------------------------------------------------------
//транспонированная матрица алгебраического дополнения
void transposedMatrixAlgebraicComplement(int **minorMatrix, int sizeMatrix)
{
    int **transposedMatrix = new int*[sizeMatrix];
    for(int i = 0; i < sizeMatrix; i++)
    {
        transposedMatrix[i] = new int[sizeMatrix];
        for(int j = 0; j < sizeMatrix; j++)
        {
            transposedMatrix[i][j] = minorMatrix[j][i];
        }
    }
    for(int i = 0; i < sizeMatrix; i++)
    {
        for(int j = 0; j < sizeMatrix; j++)
        {
            minorMatrix[i][j] = transposedMatrix[i][j];
            cout << minorMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

//------------------------------------------------------------------------------------
int main()
{
    
    //const time_t startTime = time(NULL);
    // чтение матрицы из файла
    vector<int> vectorValue = loadFile();
    int sizeMatrix = getSizeMatrix(vectorValue);
    int **matrix = new int *[sizeMatrix];
    fillMatrix(matrix, sizeMatrix, vectorValue);

    // вычисление определителя
    int oprMatr = bigOpredelitel(matrix, sizeMatrix);

    if (oprMatr == 0)
        cout << "Определитель равен нулю, обратная матрица не существует" << endl;
    else
    {
        //матрица миноров
        int **minorMatrix = new int *[sizeMatrix];

        //заполнение матрицы миноров
        searchMatrixMinor(minorMatrix, matrix, sizeMatrix);

        //рассчет алгебраических дополнений
        counterAlgebraicComplement(minorMatrix, sizeMatrix);

        //поиск транспонированной матрицы алгебраических дополнений
        transposedMatrixAlgebraicComplement(minorMatrix, sizeMatrix);
       
       // const time_t finishTime = time(NULL);
        clock_t cl = clock();
        cout<< "Время выполнения программы : " << cl << " тактов" << endl;
    }
    return 0;
}
