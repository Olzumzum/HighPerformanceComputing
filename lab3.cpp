/**
 * Близнецами называются простые числа, разница между которыми равна двум 
 * (например: 29 и 31, 41 и 43, …). Найти две соседние пары близнецов, 
 * расстояние между серединами которых больше
 *  заданного N (соседними называются такие пары,
 *  между которыми нет других близнецов)
 * */

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <fstream>
#include <cstring>
#include <stdio.h>
using namespace std;

/**
 * расширяем вектор данных
 */
vector<int> expandingVectorDate(vector<int> v)
{
    int sizeV = v.size();
    vector<int> newV(sizeV * sizeV);
    for(int i = 0; i < v.size(); i++)
    {
        newV[i] = v[i];
    }

    return newV;
} 

/** 
 * чтение данных из файла 
 * возвращает вектор значений
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
    vector<int> vectorBuffer(100);
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

                    if(vectorBuffer.size() <= indexBuffer)
                    vectorBuffer = expandingVectorDate(vectorBuffer);
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
 * поиск простых чисел решетом Эратосфена
 */
vector<int> findPrimes(int startN, int endN)
{
    //вектор для поиска простых чисел
    vector<bool> is_composite(endN + 1);
    //подсчет простых чисел
    int counterPrimes = 0;

    //исключаем числа, кратные 2
    for (int i = 4; i <= endN; i += 2)
    {
        is_composite[i] = true;
    }

    int nextPrime = 3;
    int stopAt = (int)sqrt(endN);
    while (nextPrime <= stopAt)
    {
        //исключаем числа, кратные данному простому числу
        for (int i = nextPrime * 2; i <= endN; i += nextPrime)
        {
            is_composite[i] = true;
        }

        nextPrime += 2;
        while ((nextPrime <= endN) && (is_composite[nextPrime]))
        {
            nextPrime += 2;
        }
    }

    //подсчет простых чисел
    for (int i = startN; i <= endN; i++)
    {
        if (!is_composite[i])
            counterPrimes++;
    }

    //вектор для возврата функцией простых чисел
    vector<int> primes(counterPrimes);
    //индекс для вектора простых чисел
    int indexVector = -1;

    for (int i = startN; i <= endN; i++)
    {

        if (!is_composite[i])
        {
            indexVector++;
            primes[indexVector] = i;
        }
    }

    return primes;
}

int main()
{
    //начало диапазона простых чисел
    int startN = 1;
    //конец диапазона простых чисел
    int endN = 1;
    //расстояние между близнецами
    int N = 0;
    //вектор простых чисел в диапазоне
    vector<int> primes;

    cout << "Введите конец диапазона: " << endl;
    cin >> endN;

    if (startN >= endN){
        cout << "Вы ввели неверный диапазон";
        return 0;
    }
    
    cout << "Введите расстрояне между близнецами " << endl;
    cin >> N;

    if(N < 0){
        cout << "Расстояние введено неверно";
        return 0;
    }

    primes = findPrimes(startN, endN);
     for (int i = 0; i < primes.size(); i++)
        cout << primes[i] << " ,";
    cout << endl;
    return 0;
}