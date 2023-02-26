// #include "s21_container.h"
#include <vector>
#include <iostream>
#include "s21_vector_relize.h"

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
  std::cout<< "gg" <<v.size();
  v.reserve(10);
  std::cout << "jj" << v.size();

  }


