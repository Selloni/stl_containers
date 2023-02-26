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
    using iterator = T*;
    using pointer = T*;
    using const_iterator = const T*;

private:
    T* arr_; // pointer array
    size_t sz_; // count size
    size_t cap_; // count element

public:
    ////// конструктор /////
    Vector(): arr_(nullptr), sz_(0u), cap_(0u)
    {}

    Vector(Vector &other) : sz_(other.sz_), cap_(other.cap_), arr_(other.arr_) {}

    Vector(Vector &&other) : sz_(other.sz_), cap_(other.cap_), arr_(other.arr_) {
        other.arr_= nullptr;
        other.sz_= 0;
    }

    ~Vector(){ delete[] arr_; }

    iterator begin() {return arr_;}

    iterator end() {return arr_+sz_;}

    Vector(std::initializer_list<value_type> const &items);

    // parametrized constructor for fixed size vector (explicit was used in order to
    // avoid automatic type conversion)
    explicit Vector(size_type n)
            : sz_(n), cap_(n), arr_(n ? new T[n] : nullptr) {}

    ref at(size_t i);

    const_ref at(size_t i) const ;

    void reserve(size_t n);

    size_type size() const {return sz_;}

    void push_back(const_ref value);

    void pop_back();

    ref operator[](size_t i) { return arr_[i]; }

    const_ref operator[](size_t i) const { return arr_[i]; }

    bool empty(){return sz_;}

    void clear();

    iterator insert(const_iterator pos, const T& value);

//    Vector& operator=(Vector &&other) : sz_(other.sz_), cap_(other.cap_), arr_(arr_ = new T[sz_]) {
//        for(size_t i=0; i < sz_; ++i){
//            arr_[i] = other.arr_[i];
//        }
//    }

};
} // namespase s21

// #include "s21_vector_relize.h"
#endif //  S21_VECTOR_H_