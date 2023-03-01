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
    ASSERT_FALSE(s21_v.empty());
    s21_v.pop_back();
    ASSERT_TRUE(s21_v.empty());
}

TEST(vector, 6) {
    s21::Vector<double> s21_v = {1,1,3};
    s21_v.pop_back();
    ASSERT_ANY_THROW(s21_v.at(2));
}

TEST(vector, 7) {
    s21::Vector<double> s21_v = {1,1,3};
    std::vector<int> v = {2,4};
    s21_v.clear();
    v.clear();
    ASSERT_TRUE(s21_v.empty());
    ASSERT_EQ(v.empty(),s21_v.empty());
}

//TEST(vector, 8) {
//     s21::Vector<double> s21_v = {0.2, 0.02, 0.111};
//     s21_v.reserve(100);
//}

TEST(vector, 9) {
s21::Vector<double> v = {6, 5, 8};
std::vector<double> vc = {6, 5, 8};

ASSERT_EQ(v.front(), vc.front());
ASSERT_EQ(v.back(), vc.back());
}

TEST(vector, 10) {
s21::Vector<double> v = {-2, 6, 5, 8};
std::vector<double> vc = {-2, 6, 5, 8};

ASSERT_EQ(*v.begin(), *vc.begin());
}

TEST(vector, 11) {
s21::Vector<double> v = {-2, 6, 5, 8};
std::vector<double> vc = {-2, 6, 5, 8};
ASSERT_EQ(v.empty(), vc.empty());
ASSERT_EQ(v.size(), vc.size());
ASSERT_EQ(v.max_size(), vc.max_size());
}

TEST(vector, 12) {
s21::Vector<double> v = {-2, 6, 5, 8};
std::vector<double> vc = {-2, 6, 5, 8};
v.reserve(20);
vc.reserve(20);

ASSERT_EQ(v.empty(), vc.empty());
ASSERT_EQ(v.size(), vc.size());
ASSERT_EQ(v.max_size(), vc.max_size());
ASSERT_EQ(v.capacity(), vc.capacity());
}

TEST(vector, 13) {
s21::Vector<double> v = {-2, 6, 5, 8};
std::vector<double> vc = {-2, 6, 5, 8};
v.reserve(20);
vc.reserve(20);
v.shrink_to_fit();
vc.shrink_to_fit();

ASSERT_EQ(v.empty(), vc.empty());
ASSERT_EQ(v.size(), vc.size());
ASSERT_EQ(v.max_size(), vc.max_size());
ASSERT_EQ(v.capacity(), vc.capacity());
}

TEST(vector, 14) {
s21::Vector<double> v = {-2, 6, 5, 8};
std::vector<double> vc = {-2, 6, 5, 8};
v.clear();
vc.clear();

ASSERT_EQ(v.empty(), vc.empty());
ASSERT_EQ(v.size(), vc.size());
ASSERT_EQ(v.max_size(), vc.max_size());
ASSERT_EQ(v.capacity(), vc.capacity());
}
//
//TEST(vector, 15) {
//s21::Vector<double> v = {-2, 6, 5, 8};
//std::vector<double> vc = {-2, 6, 5, 8};
//v.insert(v.begin(), 15);
//vc.insert(vc.begin(), 15);
//
//ASSERT_EQ(v.empty(), vc.empty());
//ASSERT_EQ(v.size(), vc.size());
//ASSERT_EQ(v[0], vc[0]);
//ASSERT_EQ(v.capacity(), vc.capacity());
//}

TEST(vector, 16) {
s21::Vector<double> v = {-2, 6, 5, 8};
std::vector<double> vc = {-2, 6, 5, 8};
v.erase(v.begin());
vc.erase(vc.begin());

ASSERT_EQ(v.empty(), vc.empty());
ASSERT_EQ(v.size(), vc.size());
ASSERT_EQ(v[0], vc[0]);
ASSERT_EQ(v.capacity(), vc.capacity());
}

TEST(vector, 17) {
s21::Vector<double> v = {-2, 6, 5, 8};
std::vector<double> vc = {-2, 6, 5, 8};
v.push_back(15);
vc.push_back(15);

ASSERT_EQ(v.size(), vc.size());
ASSERT_EQ(v[4], vc[4]);
ASSERT_EQ(v.capacity(), vc.capacity());
}

TEST(vector, 18) {
s21::Vector<double> v = {-2, 6, 5, 8};
std::vector<double> vc = {-2, 6, 5, 8};
v.pop_back();
vc.pop_back();

ASSERT_EQ(v.size(), vc.size());
ASSERT_EQ(v.capacity(), vc.capacity());
}

TEST(vector, 19) {
s21::Vector<double> v = {-2, 6, 5, 8};
std::vector<double> vc = {-2, 6, 5, 8};
s21::Vector<double> v2;
std::vector<double> vc2;

v.swap(v2);
vc.swap(vc2);

ASSERT_EQ(v2.size(), vc2.size());
ASSERT_EQ(v2.capacity(), vc2.capacity());
}

//TEST(vector, 20) {
//s21::Vector<double> v = {-2, 6, 5, 8};
//std::vector<double> vc = {-2, 6, 5, 8};
//
//auto v2 = v.begin();
//auto vc2 = vc.begin();
//
//ASSERT_EQ(*v2, *vc2);
//v2++;
//vc2++;
//ASSERT_EQ(*v2, *vc2);
//}
//
//TEST(vector, 21) {
//s21::Vector<double> v = {-2, 6, 5, 8};
//auto it = v.begin();
//++ ++it;
//v.emplace(it, 8, 1, 4, 12, -6);
//
//ASSERT_EQ(v.size(), 9);
//ASSERT_EQ(v.at(3), 5);
//}
//
//TEST(vector, 22) {
//s21::Vector<double> v = {-2, 6, 5, 8};
//auto it = v.begin();
//++ ++it;
//v.emplace_back(8, 1, 4, 12, -6);
//
//ASSERT_EQ(v.size(), 9);
//ASSERT_EQ(v.at(5), 1);
//ASSERT_EQ(v.back(), -6);
//}


//TEST(vector, ) {
// for reserve;
//}
//
//TEST(vector, ) {
//конструктор копирования
//}
//
//TEST(vector, ) {
// перемещение
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