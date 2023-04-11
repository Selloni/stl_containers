#include <vector>
#include <iostream>

#include "s21_vector.h"
//#include "s21_vector_realiz.cc"
int main () {
    std::vector<int> v {2,5,6};
    std::vector<int> v2;
    v2 = v;
    std::cout << v2[0];
}