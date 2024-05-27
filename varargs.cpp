#include <iostream>

using namespace std;

template <typename T>
constexpr T adder(T t){
    return t;
}

template<typename T, typename ...Args>
constexpr T adder(T t, Args... arg){
    return t + adder(arg...);
}


int main(){

    static_assert(adder(1,2,3,4,5) == 15);
    return 0;
}