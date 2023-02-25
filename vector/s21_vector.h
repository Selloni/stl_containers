#ifndef SRC_VECTOR_S21_VECTOR_H_
#define SRC_VECTOR_S21_VECTOR_H_

#include <initializer_list>
#include <utility>
#include <iostream>

template <class T>
namespace s21 {
//template <typename T>
class Vector {
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using pointer = T*;
    using iterator = T*;
    using const_pointer = const T*;
    using const_iteartor = const T*;

private:
    T* arr_; // pointer array
    size_t sz_; // count size
    size_t cap_; // count element

public:
    // Vector(size_t n, const T& value = T()); // создать вектор от параметров
    Vector() : sz_(0U), cap_(0U), arr_(nullptr) {}

    explicit Vector(size_type n) : sz_(n), cap_(n), arr_(n ? new T[n] : nullptr) {}

    Vector(const Vector &v) : sz_(v.sz_), cap_(v.cap_), arr_(v.arr_) {}

    Vector(Vector &&v) : sz_(v.sz_), cap_(v.cap_), arr_(v.arr_)
    {
        v.arr = nullptr;
        v.sz_ = 0;
    }

    ~Vector() { delete[] arr_; }

    T& operator[](size_t i) { return arr_[i]; } // обращенеи к индексу

    const T& operator[](size_t i) const { return arr_[i];}

    Vector<T>(std::initializer_list<value_type> const &items);

//    const T& operator[](size_t i);

    T& at(size_t i);

    // void resize(size_t n , const T& value = T()) {//  
    //     if (n < cap_) reserve(cap_);
    //     for (size_t i = sz_; i < n; ++i) {
    //         if (n > sz_) {
    //             // доложить value
    //         } else {
    //             // удалить элементы 
    //         }
    //     }
    // }

    // size_t cap_acity() const {
    //     return cap_;
    // }

    void reserve(size_t n);

    void push_back(const T& value);
};
} // namespase s21

#endif //  SRC_VECTOR_S21_VECTOR_H_