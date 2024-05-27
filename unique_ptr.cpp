#include <iostream>

template<typename T>
class Unique_Ptr{

    public:

    explicit Unique_Ptr( T* ptr = nullptr): _ptr(ptr){
        std::cout << "Default constructor called\n";
    }

    Unique_Ptr(const Unique_Ptr& other) = delete;
    Unique_Ptr& operator=(const Unique_Ptr& other) = delete;

    Unique_Ptr(Unique_Ptr&& dying): _ptr(dying.release()){
        std::cout << "Move constructor called\n";
    }

    template<typename U>
    Unique_Ptr(Unique_Ptr<U>&& dying): _ptr(dying.release()){
        std::cout << "Template move constructor called\n";
    }

    Unique_Ptr& operator=(Unique_Ptr&& dying) {
        std::cout << "Move assignment called\n";
        reset(dying.release());
        return *this;
    }

    template<typename U>
    Unique_Ptr& operator=(const Unique_Ptr<U>&& dying) {
        std::cout << "Template move assignment called\n";
        reset(dying.release());
        return *this;
    }

    T* release(){
        T* oldptr = _ptr;
        _ptr = nullptr;
        return oldptr;
    }

    void reset(T* newptr = nullptr){
        T* oldptr = release();
        _ptr = newptr;
        if(oldptr) delete oldptr;
    }

    T* get() const {
        return _ptr;
    }

    T* operator->() const {
        return get();
    }

    T& operator*() const {
        return *get();
    }

    void swap(Unique_Ptr& other){
        std::swap(this->_ptr, other._ptr);
    }

    explicit operator bool(){
        return get() != nullptr;
    }

    ~Unique_Ptr(){
        std::cout << "Destructor called\n";
        reset();
    }

    private:
    T* _ptr;

};

class Base{

};

class Der: public Base{

};

class Der1{

};

int main(){

    Unique_Ptr<int> uptr{new int};
    Unique_Ptr<int> uptr2 = std::move(uptr);
    Unique_Ptr<int> uptr3;
    uptr3 = std::move(uptr2);

    Unique_Ptr<Der> tuptr{new Der};
    Unique_Ptr<Der> tuptr2 = std::move(tuptr);
    Unique_Ptr<Base> tuptr3 = std::move(tuptr2);

    // Unique_Ptr<Der1> tuptr{new Der1};
    // Unique_Ptr<Base> tuptr2 = std::move(tuptr);
    
    return 0;
}