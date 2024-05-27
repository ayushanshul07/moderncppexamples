#include <iostream>

template<typename ...Args>
constexpr auto adder(Args... args){
    return (... + args); // or return (args + ...);
}

int main(){

    static_assert(adder(1,2,3,4,5) == 15);
    return 0;

}