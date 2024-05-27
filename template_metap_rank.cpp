#include <iostream>
#include <cstddef>

/*
Task: Write a templated class/struct which can figure out Rank/Dimension of an array
*/

template<typename T>
struct Rank
{
    static constexpr size_t value = 0;
};

template<typename T>
struct Rank<T[]>
{
    static constexpr size_t value = 1u + Rank<T>::value;
};

template<typename T, size_t N>
struct Rank<T[N]>
{
    static constexpr size_t value = 1u + Rank<T>::value;
};

class Employee{

};

int main(){

    static_assert(Rank<int>::value == 0);
    static_assert(Rank<int[2]>::value == 1);
    static_assert(Rank<int[2][3]>::value == 2);
    static_assert(Rank<int[][3]>::value == 2);
    static_assert(Rank<Employee[2][3][4][5]>::value == 4);

    return 0;
}