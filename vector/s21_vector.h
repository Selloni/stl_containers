#ifndef SRC_VECTOR_S21_VECTOR_H_
#define SRC_VECTOR_S21_VECTOR_H_

namespace s21 {

template <typename T>
class Vector {
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
    // Vector(size_t n, const T& value = T()); // создать вектор от параметров

    Vector<T>(std::initializer_list<value_type> const &items);

    Vector();
    // Vector<T>::Vector(sizetype size, const_ref value)

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

#endif //  SRC_VECTOR_S21_VECTOR_H_