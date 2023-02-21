// #include "s21_container.h"
#include <vector>
#include <iostream>

template <typename T>
void f(T x) {
  std::cout << "T param" << std::endl;
}

template <>
void f<int>(int x) {
  std::cout << "its int" << std::endl;
}


int main () {
}