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
void Vector<T>::reserve_more_capacity(size_t size)
{
    if (size > cap_) {
        value_type *buff = new value_type[size];
        for (size_t i = 0; i < sz_; ++i)
            buff[i] = std::move(arr_[i]);
        delete[] arr_;
        arr_ = buff;
        cap_ = size;
    }
}


template <typename T>
void Vector<T>::reserve(size_t n) {
    if (n > max_size()) throw std::out_of_range("lenght error");
    reserve_more_capacity(n);
}

template <typename T>
size_t  Vector<T>::capacity() const {
    return (cap_);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector &other) {
    sz_ = other.sz_;
    cap_ = other.cap_;
    arr_= new T[sz_];
    for(size_t i = 0; i < sz_; ++i){
        arr_[i] = other.arr_[i];
    }
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
    Vector<T> tmp = other;
    other.clear();
    other = this;
}


template <typename T>
void Vector<T>::clear(){while (sz_ != 0) pop_back();}

template <typename T>
T* Vector<T>::insert(const_iterator pos, const T& value ) {
    Vector<T> tmp(*this);
    if (pos == this->end()) {
        push_back(value);
    } else {
        arr_[pos - begin] = value;
        for (size_t i=(pos-begin()+1); i < sz_ - 1; ++i) {
            arr_[i] = tmp.arr_[i-1];
        }

        push_back(tmp.back());

        return pos;
    }
}

}// s21

#endif  //S21_RELIZE_V