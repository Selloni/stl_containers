// #include "s21_container.h"
#include <vector>
#include <iostream>
#include "s21_vector.h"

// template <typename T>
// void f(T x) {
//   std::cout << "T param" << std::endl;
// }

// template <>
// void f<int>(int x) {
//   std::cout << "its int" << std::endl;
// }


// using namespace s21;

int main () {
  s21::Vector<int> v = {1,2,3};
  v.push_back(25);
  for (int i = 0 ; i < 3; ++i) {
    std::cout << v.at(i);
  }


}