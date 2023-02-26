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
    std::vector<int> ll = {1,2,5};
  s21::Vector<int> v = {1,2,3};
   v.insert(v.begin,25);
//   ll.insert(2,3);
  for (int i = 0 ; i < 4; ++i) {
    std::cout << ll.at(i);
  }


}