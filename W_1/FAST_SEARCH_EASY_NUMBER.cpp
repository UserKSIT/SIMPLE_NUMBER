//
//  main.cpp
//  W_1
//
//  Created by Артём on 16/03/2019.
//  Copyright © 2019 Ерошев Артём. All rights reserved.
//

#include <iostream>
#include <chrono>
#include <cmath>
#include "numbers.dat"

class Timer
{
    using clock_t = std::chrono::high_resolution_clock;
    using milliseconds = std::chrono::milliseconds;
public:
    Timer()
    : start_(clock_t::now())
    {
    }

    ~Timer()
    {
        const auto finish = clock_t::now();
        const auto us =
        std::chrono::duration_cast<milliseconds>
        (finish - start_).count();
        std::cout << us << " ms" << std::endl;
    }

private:
    const clock_t::time_point start_;
};


int is_prime(int a)
{
    if (a == 0 || a == 1)
        return 0;
    if (a == 2 || a == 3 || a == 5 || a == 7 || a == 11 || a == 13 || a == 17 || a == 19 || a == 23 || a == 29)
        return 1;
    if (!(a%2) || !(a%3) || !(a%5) || !(a%7) || !(a%11) || !(a%13) || !(a%17) || !(a%19) || !(a%23) || !(a%29))
        return 0;
    int i1, i2, i3, i4, i5, i6, i7, i8, root;
    root = sqrt(a);
    i1 = 31; i2 = 37; i3 = 41; i4 = 43; i5 = 47; i6 = 49; i7 = 53; i8 = 59;
    while (i8 <= root && a%i1 && a%i2 && a%i3 && a%i4 && a%i5 && a%i6 && a%i7 && a%i8){
        i1 += 30; i2 += 30; i3 += 30; i4 += 30; i5 += 30; i6 += 30; i7 += 30; i8 += 30;
    }
    if (i8 <= root || (i1 <= root && !(a % i1)) || (i2 <= root && !(a % i2)) ||
        (i3 <= root && !(a % i3)) || (i4 <= root && !(a % i4)) ||
        (i5 <= root && !(a % i5)) || (i6 <= root && !(a % i6)) ||
        (i7 <= root && !(a % i7)))
        return 0;
    return 1;
}

void init(bool (&primes)[Size]){
    for(int i = 0; i<Size; i++){
        if(is_prime(Data[i]))
            primes[i] = true;
    }
}

int binary_search(int key){
    int left = 0; // задаем левую и правую границы поиска
    int right = Size - 1;
    int search = -1; // найденный индекс элемента равен -1 (элемент не найден)
    while (left <= right) // пока левая граница не "перескочит" правую
    {
        int mid = (left + right) / 2; // ищем середину отрезка
        if (key == Data[mid]) {  // если ключевое поле равно искомому
            search = mid;     // мы нашли требуемый элемент,
            break;            // выходим из цикла
        }
        if (key < Data[mid])     // если искомое ключевое поле меньше найденной середины
            right = mid - 1;  // смещаем правую границу, продолжим поиск в левой части
        else                  // иначе
            left = mid + 1;   // смещаем левую границу, продолжим поиск в правой части
    }
    return search;
}

int main(int argc, const char * argv[]) {
    Timer time;
    //если у нас нечётное число аргументов - error
    if (argc == 1 || !(argc % 2))
        return -1;
    
    unsigned int res = 0;
    unsigned int i = 0;
    unsigned int count = 1;
    bool flag;
    
    bool primes[Size] = {false};
    init(primes);
    
    while(count + 1 < argc){
        res = 0;
        //проверка корректности диапазона

        int from = std::atoi(argv[count]);
        int to = std::atoi(argv[count + 1]);
        
        if (to <= from){
            //std::cout << "Incorrect input" << std::endl;
            std::cout << "0" << std::endl;
            return 0;
        }
        //поиск начала диапазона
        i = binary_search(from);
        if (i == -1){
            return 0;
        }
        
        while (Data[i] <= to){
            if(primes[i])
                res++;
            i++;
        }
        /*while (Data[i] == 1)
            i++;
        //проход по диапазону
        while (Data[i] <= to){
            flag = true;
                //перебор делитель до sqrt(Data[i])
                for (unsigned int j = 2; (j * j) - 1 < Data[i]; j++){
                    if (Data[i] % j == 0){
                        flag = false;
                        break;
                    }
                }
            if (flag){
                std::cout << Data[i] << std::endl;
                res++;
            }
            i++;
        }*/
        count += 2;
        std::cout << res << std::endl;
    }

    return 0;
}
