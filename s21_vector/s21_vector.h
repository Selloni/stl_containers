
#include <iostream>

template <typename T>



class Vector {
    T* arr; // pointer array
    sizr_t sz; // count size
    size_t cap; // count element

public:
    Vector(size_t n, const T& value = T()); // создать вектор от параметров

    // T& operaror[](size_t i) {  // обращенеи к индексу без проверки
    //     return arr[i];
    // }

    T& at(size_t i) {
        if(i >= sz) throw std::out_of_range("проверка на диапозон");
        return arr[i];
    }

    const T& at(size_t i) const {
        if(i >= sz) throw std::out_of_range("проверка на диапозон");
        return arr[i];
    }

    void resize(size_t n , const T& value = T()); //  

    size_t capacity() const {
        return cap;
    }

    void reseve(size_t n) { //
        if (n <= cap) return;

    }



privat:
};
