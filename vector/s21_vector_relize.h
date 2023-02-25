#ifndef S21_RELIZE_V
#define S21_RELIZE_V

#include "s21_vector.h"

namespace s21 {
template <typename T>
Vector<T>::Vector(std::initializer_list<value_type> const &items) {
    arr_ = new value_type[items.size()];
    size_t i = 0;
    for (auto it = items.begin(); it != items.end(); it++) {
    arr_[i] = *it;
    i++;
}
sz_ = items.size();
cap_ = items.size();
}

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

template <typename T>
T& Vector<T>::at(size_t i) {
    if(i >= sz_) throw std::out_of_range("s21::out_of_range");
    return arr_[i];
}

template <typename T>
const T& Vector<T>::at(size_t i) const {
    if(i >= sz_) throw std::out_of_range("s21::out_of_range");
    return arr_[i];
}

template <typename T>
void Vector<T>::push_back(const_ref value) {
    if (sz_ == cap_) reserve(2 * cap_);
    new (arr_ + sz_) T(value);
    ++sz_;
}

template <typename T>
void Vector<T>::pop_back() {
    (arr_+sz_-1)->~T();
    --sz_;
}


}// s21

#endif  //S21_RELIZE_V