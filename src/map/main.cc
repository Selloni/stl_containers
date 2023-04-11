#include "s21_map.h"
#include "s21_map_reliz.cc"
#include <iostream>
#include <iterator>
#include <map>
#include <string>

int main() {
  //    using namespace s21;
  //  std::map<int, int> m1;
  //      s21::map<int, int> m1;
  // std::map<int, int> mm{{1, 1}, {22, 2}, {13, 3}};
  // // std::cout << lol[13] << "\n";
  // std::map<int, int>::iterator lo = mm.begin();
  // std::cout << lo->second << "\n";
  // ++lo;
  // std::cout << lo->second << "\n";
  // ++lo;
  // std::cout << lo->second << "\n";
  // ++lo;
  // std::cout << lo->second << "\n";
  s21::map<int, int> mm;
  s21::map<int, int> ll{{7, 7}, {8, 8}, {5, 5}, {4, 4}, {6, 6}};
  s21::map<int, int>::iterator l;
  mm = ll;
  for (l = mm.begin(); l != mm.end(); ++l) {
    std::cout << (*l).second << "\n";
  }
}