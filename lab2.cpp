/**
 * Число называется циркулярно простым, если любая круговая 
 * перестановка его цифр есть простое число (например – 197 или 31 или 17).
 *  Найти количество циркулярно простых чисел в диапазоне от N до M
 */

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <fstream>
#include <cstring>
#include <stdio.h>
using namespace std;

/**
 * поиск простых чисел решетом Эратосфена
 */
vector<int> findPrimes(int startN, int endN)
{
    //вектор для поиска простых чисел
    vector<bool> is_composite(endN);
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
    for (int i = startN; i < endN; i++)
    {
        if (!is_composite[i])
            counterPrimes++;
    }

    //вектор для возврата функцией простых чисел
    vector<int> primes(counterPrimes);
    //индекс для вектора простых чисел
    int indexVector = 0;

    for (int i = startN; i <= endN; i++)
    {
        if (!is_composite[i])
            primes[indexVector++] = i;
    }

    cout << "Всего простых чисел: " << counterPrimes << endl;
    ;

    return primes;
}

/**
 * поиск циркулярно простых чисел
 */
void findCircularPrime(vector<int> prime)
{
    int circularNumber;
    for (int i = 0; i <= prime.size(); i++)
    {
        //получение обратного числа
        int p = prime[i];
        //счетчик количества цифер в числе
        int count = -1;
        //считаем сколько цифер в числе
        while(p != 0)
        {
            count++;
            p /=10;
        }

        p = prime[i];
        //обратное число
        int cirlularNumber = 0;
        //получаем обратное число
        while (p!=0)
        {
           cirlularNumber += p % 10 * pow(10, count--);
           p /= 10;
        }
        
        
        
    }
}

int main()
{
    //начало диапазона
    int startN = 0;
    //конец диапазона
    int endN = 0;
    //вектор простых чисел
    vector<int> primes;

    cout << "Введите начало диапазона: " << endl;
    cin >> startN;
    cout << "Введите конец диапазона: " << endl;
    cin >> endN;

    //поиск простых чисел
    primes = findPrimes(startN, endN);

    //вывод всех чиселis_composite[i]
    for (int i = 0; i <= primes.size(); i++)
        cout << primes[i] << " ,";
    cout << endl;

    //поиск циркулярно простых чисел
    findCircularPrime(primes);

    return 0;
}