#include <gtest/gtest.h>
#include <vector>
#include "s21_vector_relize.h"


TEST(vector, 1) {
    s21::Vector<int> s21_v = {0, 1, 2};
    for (size_t i = 0; i < s21_v.size(); ++i) {
        ASSERT_EQ(s21_v[i], i);
    }
}

TEST(vector, 2) {
  s21::Vector<unsigned int> s21_v = {1,2,3};
  std::vector<unsigned int> v = {1,2,3};
  for (int i = 0 ; i != 3; ++i) {
    ASSERT_EQ(s21_v[i],v[i]);
  }
}

TEST(vector, 3) {
    s21::Vector<double> s21_v = {0,1,2};
    s21_v.push_back(3);
    std::vector<double> v = {0,1,2};
    v.push_back(3);
    for (auto i = 0 ; i != 4; ++i) {
    ASSERT_EQ(s21_v[i],v[i]);
    }
}

TEST(vector, 4) {
    s21::Vector<double> s21_v = {0,1,2};
    ASSERT_ANY_THROW(s21_v.at(4));
}

TEST(vector, 5) {
    s21::Vector<double> s21_v = {1};
    ASSERT_TRUE(s21_v.empty());
    s21_v.pop_back();
    ASSERT_FALSE(s21_v.empty());
}

TEST(vector, 6) {
    s21::Vector<double> s21_v = {1,1,3};
    s21_v.pop_back();
    ASSERT_ANY_THROW(s21_v.at(2));
}

TEST(vector, 7) {
    s21::Vector<double> s21_v = {1,1,3};
    s21_v.clear();
    ASSERT_TRUE(s21_v.empty());
}

TEST(vector, 8) {
     s21::Vector<double> s21_v = {0.2, 0.02, 0.111};

     s21_v.reserve(100);


}

//TEST(vector, ) {
//
//}
//
//TEST(vector, ) {
//
//}
//
//TEST(vector, ) {
//
//}
//
//TEST(vector, ) {
//
//}
//
//TEST(vector, ) {
//
//}
//


//TEST(vector, ) {
//
//}

 int main(int argc, char **argv) {
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
 }