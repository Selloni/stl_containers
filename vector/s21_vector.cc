// #include "s21_container.h"
#include <vector>
#include <iostream>
#include "stopwatch.h"
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
    {
        s21::StopWatch<s21::steady_clock> clock;
        s21::Vector<int> vec{1, 2, 3, 4, 5};
        s21::Vector<int> vet_to_copy = {5, 4, 3, 2, 1};
        clock.start();
        vec.reserve(100);
        clock.stop();
        std::cout << clock.nanoseconds();
    }
    std::cout << '\n';
    {
        s21::StopWatch<s21::steady_clock> clock;
        std::vector<int> vec{1, 2, 3, 4, 5};
        std::vector<int> vet_to_copy = {5, 4, 3, 2, 1};
        clock.start();
        vec.reserve(100);
        clock.stop();
        std::cout << clock.nanoseconds();
    }
//
//    for (int  i = 0; i < vec.size(); ++ i) {
//        std::cout << 'v' <<vec[i] << " ";
//    }
//    std::cout << '\n';
//    for (int  i = 0; i < vet_to_copy.size(); ++ i) {
//        std::cout << vet_to_copy[i] << " ";
//    }

}


