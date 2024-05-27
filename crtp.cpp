#include <iostream>

template<typename T>
class Employee{

    public:
    T& getDerieved(){  return static_cast<T&>(*this);}

    void printSalary(){
        getDerieved().printSalary();
    }
};


class Fulltime: public Employee<Fulltime>{
    public:
    void printSalary(){
        std::cout << "Salary of Fulltime employee is 1000 bucks per day\n";
    }

};

class Contractectual: public Employee<Contractectual>{
    public:
    void printSalary(){
        std::cout << "Salary of Contractectual employee is 800 bucks per day\n";
    }
};

template<typename T>
void printSalary(Employee<T>& e){
    e.printSalary();
}

/*
One pitfall which devs can make is instead of deriving from Base<Der1> they can inherit from Base<Der2>
To prevent this we can make Base constructor private and make T a friend of Base, this will prevent the above problem

template<typename T>
class Base{
    private:
    Base();
    friend T;
};

class Der1: public Base<Der1>{

}
class Der2: public Base<Der1>{
    Der2() -> calls Base Constructor -> But Der2 can't call Base constructor as Der2 is not a friend of Base, Der1 is
}

This neat trick can prevent such errors at compile time

*/


int main(){

    Fulltime emp1;
    printSalary(emp1); 

    Contractectual emp2;
    printSalary(emp2); 

}