#ifndef S21_RELIZE_V
#define S21_RELIZE_V

#include "s21_vector.h"

namespace s21 {
template <typename T>
void Vector<T>::reserve(size_t n) {
    if (n <= cap_) return;
    pointer newarr = reinterpret_cast<pointer>(new int8_t[n*sizeof(T)]); // выделение байт
    size_t i = 0;
    try {
        for (; i < sz_; ++i) {
            new(newarr + i) T(arr_[i]);
        }
    } catch (...) {
        for(size_t j = 0; j < i; ++j) {
            (newarr + i)->~T();
        }
        delete[] reinterpret_cast<int8_t*>(arr_);
        throw;
    }

    for(size_t i = 0; i< sz_; i++) {
        new(newarr  + i) T(arr_[i]); // вызов конструктора по данному адресу
    }
    for(size_t i = 0; i < sz_; ++i){
        (arr_ + i)->~T();   // явный вызов конструктора
    }
    delete[] reinterpret_cast<int8_t*>(arr_); //очищаяем массив 
    arr_ = newarr;
}
}// s21

#endif  //S21_RELIZE_V