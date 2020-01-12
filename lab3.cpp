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
    for (int i = 0; i < v.size(); i++)
    {
        newV[i] = v[i];
    }

    return newV;
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

/**
 * поиск близнецов на заданном расстоянии
 */
int findTwinsWithGivenDistance(int **massTwDistance, int **massTwins, int N, int indexS)
{
    int indexTwDist = 0;

    for (int i = 1; i < indexS; i++)
    {
        if ((massTwins[i][0] - massTwins[i - 1][1]) == N)
        {
            massTwDistance[indexTwDist] = new int[4];
            for (int j = i - 1, col = 0; j <= i; j++)
            {
                massTwDistance[indexTwDist][col++] = massTwins[j][0];
                massTwDistance[indexTwDist][col++] = massTwins[j][1];
            }
            indexTwDist++;
        }
    }

    if (indexTwDist > 0)
        massTwins = massTwDistance;
        else cout << "Таких пар не существует" << endl;

    return indexTwDist;
}

/** 
 * поиск близнецов
 */
int findTwins(vector<int> primes, int **massTwins, int N)
{
    //индекс массива близнецов
    int indexS = 0;

    //поиск близнецов
    for (int i = 1; i < primes.size(); i++)
    {
        if ((primes[i] - primes[i - 1]) == 2)
        {
            massTwins[indexS] = new int[2];
            massTwins[indexS][0] = primes[i - 1];
            massTwins[indexS++][1] = primes[i];
        }
    }

    //уменьшаем размер массива
    int **massResize = new int *[indexS];
    for (int i = 0; i < indexS; i++)
    {
        massResize[i] = new int[2];
        massResize[i][0] = massTwins[i][0];
        massResize[i][1] = massTwins[i][1];
    }
    massTwins = massResize;

    return indexS;
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

    if (startN >= endN)
    {
        cout << "Вы ввели неверный диапазон";
        return 0;
    }

    cout << "Введите расстрояне между близнецами " << endl;
    cin >> N;

    if (N < 0)
    {
        cout << "Расстояние введено неверно";
        return 0;
    }

    //получение простых чисел в заданном диапазоне
    primes = findPrimes(startN, endN);
    //массив близнецов
    int **massTwins = new int *[primes.size()];
    //поиск близнецов
    int indexTwins = findTwins(primes, massTwins, N);

//поиск близнецов на дистанции
    int **massTwDistance = new int *[indexTwins];
    int indexTwDist = findTwinsWithGivenDistance(massTwDistance, massTwins, N, indexTwins);
    
    for (int i = 0; i < indexTwDist; i++)
    {
        cout << "Пара близнецов ";
        for (int j = 0; j < 4; j++)
        {
            cout << massTwDistance[i][j] << ", ";
        }
        cout << endl;
    }
    cout << endl;

    return 0;
}