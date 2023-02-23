#include "s21_vector.h"

using namespace s21;

Vector(): arr_(nullptr), sz_(0u), cap_(0u)
{}


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
void reserve(size_t n) { //
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