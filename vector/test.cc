#include <gtest/gtest.h>
#include <vector>
#include "s21_vector.h"


TEST(vector, 1) {
  s21::Vector<int> s21_v = {1,2,3};
  std::vector<int> v = {1,2,3};
  v.push_back(25);
  s21_v.push_back(25);
  for (int i = 0 ; i < 4; ++i) {
    ASSERT_EQ(true,v.at(i)=s21_v.at(i));
  }
}

// int main(int argc, char **argv) {
//   testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }