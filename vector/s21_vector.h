#ifndef S21_VECTOR_H_
#define S21_VECTOR_H_

#include <initializer_list>

namespace s21 {
template <typename T>
class Vector {
public:
///////////  attribute  //////////
    using value_type = T;
    using ref = T&;
    using const_ref = const T&;
    using size_type = std::size_t;
    using pointer = T*;
    using const_pointer = const T*;

private:
    T* arr_; // pointer array
    size_t sz_; // count size
    size_t cap_; // count element

public:

    Vector<T>(std::initializer_list<value_type> const &items) {
    arr_ = new value_type[items.size()];
    size_t i = 0;
    for (auto it = items.begin(); it != items.end(); it++) {
        arr_[i] = *it;
        i++;
    }
    sz_ = items.size();
    cap_ = items.size();
    }

    Vector(): arr_(nullptr), sz_(0u), cap_(0u)
    {}

    ~Vector(){ delete[] arr_; }

    T& operator[](size_t i) { return arr_[i]; } // обращенеи к индексу

    const T& operator[](size_t i) const { return arr_[i];}

    T& at(size_t i) {
        if(i >= sz_) throw std::out_of_range("s21::out_of_range");
        return arr_[i];
    }

    const T& at(size_t i) const {
        if(i >= sz_) throw std::out_of_range("s21::out_of_range");
        return arr_[i];
    }

    void reserve(size_t n);

    void push_back(const T& value) {
        if (sz_ == cap_) reserve(2 * cap_);
        new (arr_ + sz_) T(value);
        ++sz_;
    }

    void pop_back() {
        (arr_+sz_-1)->~T();
        --sz_;
    }

};
} // namespase s21

// #include "s21_vector_relize.h"
#endif //  S21_VECTOR_H_