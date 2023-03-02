#ifndef S21_VECTOR_H_
#define S21_VECTOR_H_

#include <initializer_list>
#include <iostream>


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
//    using pointer = T*;
    using const_iterator = const T*;

private:
    size_t sz_;
    size_t cap_;
    T* arr_;
public:
    ////// конструктор /////
    Vector():sz_(0u), cap_(0u), arr_(nullptr) {}

    Vector(const Vector &other) : sz_(other.sz_), cap_(other.cap_), arr_(other.arr_) {}

    Vector(Vector &&other) : sz_(other.sz_), cap_(other.cap_), arr_(other.arr_) {
        other.arr_= nullptr;
        other.sz_= other.cap_ = 0;
    }

    ~Vector(){ delete[] arr_; }

    iterator begin() const {return arr_;}

    iterator end() const {return arr_ + sz_;}

    Vector(std::initializer_list<value_type> const &items);

    // parametrized constructor for fixed size vector (explicit was used in order to
    // avoid automatic type conversion)
    explicit Vector(size_type n)
            : sz_(n), cap_(n), arr_(n ? new T[n]() : nullptr) {}

    ref at(size_t i);

    const_ref at(size_t i) const ;

    //////////////////////
    void reserve(size_t n);

    size_type capacity() const;

    size_type size() const {return sz_;}

    void push_back(const_ref value);

    void pop_back();

    void swap(Vector& other);

    ref operator[](size_t i) { return arr_[i]; }

    const_ref operator[](size_t i) const { return arr_[i]; }

    bool empty(){return !sz_;}

    void clear();

    iterator insert(iterator pos, const T& value);

    const_ref front() {return arr_[0];}

    const_ref back() {return arr_[sz_-1];}

    Vector& operator=(const Vector &other);

    Vector& operator=(Vector &&other);

    size_type max_size()const;

    iterator erase(iterator pos);

    void shrink_to_fit();

    template <typename... Args>
    iterator emplace(iterator pos, Args &&...args);

    template <typename... Args>
    void emplace_back(Args&&... args);

//    iterator data() noexcept;

    ref operator+(int n){return *(arr_+= n);}
    ref operator-(int n){return *(arr_-= n);}
    ref operator++(int){return *(arr_++);}
    ref operator--(int){return *(arr_--);}
    ref operator++(){return *(++arr_);}
    ref operator--(){return *(--arr_);}
    ref operator*(){return *arr_;}
    bool operator != (const iterator &it) {return arr_ != it.arr_;}
    bool operator == (const iterator &it) {return arr_ == it.arr;}

private:
    void swap_(Vector& to, Vector& other);
    void reserve_more_capacity_(size_t size);
};
} // namespase s21

// #include "s21_vector_relize.h"
#endif //  S21_VECTOR_H_