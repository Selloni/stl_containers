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

    Vector(): arr_(nullptr), sz_(0u), cap_(0u)
    {}

    Vector(Vector &other) : sz_(other.sz_), cap_(other.cap_), arr_(other.arr_) {}

    Vector(Vector &&other) : sz_(other.sz_), cap_(other.cap_), arr_(other.arr_) {
        other.arr_= nullptr;
        other.sz_= 0;
    }

    ~Vector(){ delete[] arr_; }

    T* begin(){
        return arr_;
    }

    T* end() {
        return arr_+sz_;
    }

    Vector(std::initializer_list<value_type> const &items);

//    explicit Vector(size_type n)
//            : m_size_(n), m_capacity_(n), arr_(n ? new T[n] : nullptr) {}

    ref at(size_t i) {
        if(i >= sz_) throw std::out_of_range("s21::out_of_range");
        return arr_[i];
    }

    const_ref at(size_t i) const {
        if(i >= sz_) throw std::out_of_range("s21::out_of_range");
        return arr_[i];
    }

    void reserve(size_t n);

    size_type size() const {
        return sz_;
    }

    void push_back(const_ref value) {
        if (sz_ == cap_) reserve(2 * cap_);
        new (arr_ + sz_) T(value);
        ++sz_;
    }

    void pop_back() {
        (arr_+sz_-1)->~T();
        --sz_;
    }

    ref operator[](size_t i) { return arr_[i]; } // обращенеи к индексу

    const_ref operator[](size_t i) const { return arr_[i]; }
//
//    Vector& operator=(Vector &&other) : sz_(other.sz_), cap_(other.cap_), arr_(other.arr_) {
//        //удалить старый масви
//        // отнять масив в свой
//        // обнулисть other.arr_ = nullptr; sz_ = 0 ; cap_ = 0;
//        return *this;
//    }

};
} // namespase s21

// #include "s21_vector_relize.h"
#endif //  S21_VECTOR_H_