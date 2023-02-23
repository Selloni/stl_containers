#ifndef SRC_VECTOR_S21_VECTOR_H_
#define SRC_VECTOR_S21_VECTOR_H_


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
    // Vector(size_t n, const T& value = T()); // создать вектор от параметров

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

    // Vector<T>::Vector(size_type size, const_ref value)

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