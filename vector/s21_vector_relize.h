#ifndef S21_RELIZE_V
#define S21_RELIZE_V

#include "s21_vector.h"
#include <memory>


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
void Vector<T>::reserve_more_capacity_(size_t size)
{
        value_type *buff = new value_type[size];
        for (size_t i = 0; i < sz_; ++i)
            buff[i] = std::move(arr_[i]);
        delete[] arr_;
        arr_ = buff;
        cap_ = size;
}

template <typename T>
void Vector<T>::reserve(size_t n) {
    if (n > max_size()) throw std::out_of_range("lenght error");
    reserve_more_capacity_(n);
}

template <typename T>
size_t  Vector<T>::capacity() const {
    return (cap_);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector &other) {
    if (this == std::addressof(other)) {
        return *this;
    }
    delete [] arr_;
    sz_ = other.sz_;
    cap_ = other.cap_;
    try {
        arr_= new T[sz_];
    } catch (std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }
    std::copy(other.begin(), other.end(), arr_);
    return *this;
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector<T> &&other) {
    if (this == &other) {
        return *this;
    }
    delete [] arr_;
    swap_(*this, other);
    return *this;
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
size_t Vector<T>::max_size() const {
    std::allocator<T> alloc;
    return alloc.max_size();
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

template <typename T>
void Vector<T>::swap(Vector<T> &other) {
    Vector<T> tmp(std::move(other));
    other = std::move(*this);
    *this = std::move(tmp);
}


template <typename T>
void Vector<T>::swap_(Vector& to, Vector& other) {
    std::swap(to.arr_, other.arr_);
    std::swap(to.sz_, other.sz_);
    std::swap(to.cap_, other.cap_);
}

template <typename T>
void Vector<T>::clear(){while (sz_ != 0) pop_back();}

template <typename T>
T* Vector<T>::insert(iterator pos, const_ref value) {
    if (pos > end()) return pos;
    Vector tmp(std::move(*this));
    arr_ = new T[tmp.sz_+1]();
    sz_ = tmp.sz_ + 1;
    cap_ = tmp.cap_;

    if(cap_ <= sz_) reserve(cap_ * 2);
    int i = 0;
    for(iterator it = tmp.begin(); it < tmp.end(); ++it) {
       if (it == pos) {
           arr_[i++]= value;
           arr_[i++]= *it;

       }else {
           arr_[i++] = *it;
       }
    }
    return pos;
}

template <typename T>
T* Vector<T>::erase(iterator pos) {
    if(pos < begin() || pos >= end()) {
        return pos;
    }
    Vector<T> tmp(std::move(*this));
    try {
        arr_ = new T[tmp.sz_ - 1];
    } catch (std::exception &exc) {
        std::cerr << exc.what() << '\n';
        return pos;
    }
    sz_ = tmp.sz_ - 1;
    cap_ = tmp.cap_;
    iterator current = pos;
    int i = 0;
    for(auto it = tmp.begin(); it != tmp.end(); ++it) {
        if (it != pos) {
            arr_[i++] = *it;
        }
    }
    return current;
}

template <typename T>
void Vector<T>::shrink_to_fit() {
    if (sz_ == cap_) return;
    reserve_more_capacity_(sz_);
}

    template <typename T>
    template <typename... Args>
    typename Vector<T>::iterator Vector<T>::emplace(iterator pos, Args &&...args) {
        for (auto &i : {args...}) insert(pos, i);
        return pos;
    }

}// s21

#endif  //S21_RELIZE_V