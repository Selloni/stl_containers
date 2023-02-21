
#include <iostream>

namespace s21 {

template <typename T>
class Vector {
    T* arr; // pointer array
    size_t sz; // count size
    size_t cap; // count element

public:
    // Vector(size_t n, const T& value = T()); // создать вектор от параметров

    T& operator[](size_t i) {  // обращенеи к индексу без проверки
        return arr[i];
    }

    const T& operator[](size_t i) const {  // обращенеи к индексу без проверки
        return arr[i];
    }

    T& at(size_t i) {
        if(i >= sz) throw std::out_of_range("проверка на диапозон");
        return arr[i];
    }

    const T& at(size_t i) const {
        if(i >= sz) throw std::out_of_range("проверка на диапозон");
        return arr[i];
    }

    // void resize(size_t n , const T& value = T()) {//  
    //     if (n < cap) reserve(cap);
    //     for (size_t i = sz; i < n; ++i) {
    //         if (n > sz) {
    //             // доложить value
    //         } else {
    //             // удалить элементы 
    //         }
    //     }
    // }

    // size_t capacity() const {
    //     return cap;
    // }

    void reserve(size_t n) { //
        if (n <= cap) return;

        T* newarr = reinterpret_cast<T*>(new int8_t[n*sizeof(T)]); // выделение байт

        size_t i = 0;
        try {
            for (; i < sz; ++i) {
                new(newarr + i) T(arr[i]);
            }
        } catch (...) {
            for(size_t j = 0; j < i; ++j) {
                (newarr + i)->~T();
            }
            delete[] reinterpret_cast<int8_t*>(arr);
            throw;
        }

        for(size_t i = 0; i< sz; i++) {
            new(newarr  + i) T(arr[i]); // вызов конструктора по данному адресу
        }
        for(size_t i = 0; i < sz; ++i){
            (arr+i)->~T();   // явный вызов конструктора
        }
        delete[] reinterpret_cast<int8_t*>(arr); //очищаяем массив 
        arr = newarr;
    }

    void push_back(const T& value) {
        if (sz == cap) reserve(2 * cap);
        new (arr + sz) T(value);
        ++sz;
    }

    void pop_back() {
        (arr+sz-1)->~T();
        --sz;
    }
// privat:
};
} // namespase s21
