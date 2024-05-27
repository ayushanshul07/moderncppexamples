#include <iostream>
#include <cstddef>

/*
Task: Compile time gcd
*/

template<int a, int b>
struct gcd
{
    inline static constexpr int value = gcd<b,a%b>::value;
};

template<int a>
struct gcd<a,0>
{
    inline static constexpr int value = a;
};

int main(){

    static_assert(gcd<10,5>::value == 5);
    static_assert(gcd<21,31>::value == 1);
    static_assert(gcd<21,7>::value == 7);
    static_assert(gcd<6,9>::value == 3);
    return 0;
}