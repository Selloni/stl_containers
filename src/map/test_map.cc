// #include "../vector/s21_vector_realiz.cc"
#include "s21_map.h"
#include "s21_map_reliz.cc"
#include <gtest/gtest.h>
#include <iterator>
#include <map>

using namespace std;

class Test_map : public testing::Test {
protected:
  s21::map<int, int> *s21_m;
  s21::map<int, int> *s21_emp;
  std::map<int, int> *std_m;
  std::map<int, int> *std_emp;

  void SetUp() {
    s21_m = new s21::map<int, int>(initializer_list<pair<const int, int>>{
        make_pair(1, 1), make_pair(2, 2), make_pair(3, 3)});
    std_m = new std::map<int, int>(initializer_list<pair<const int, int>>{
        make_pair(1, 1), make_pair(2, 2), make_pair(3, 3)});
    s21_emp = new s21::map<int, int>();
    std_emp = new std::map<int, int>();
  }
  void TearDown() {
    delete s21_m;
    delete s21_emp;
    delete std_m;
    delete std_emp;
  }
};

TEST_F(Test_map, 1) {
  s21::map<int, int> m{{1, 1}, {2, 2}, {3, 3}};
  std::map<int, int> s{{1, 1}, {2, 2}, {3, 3}};
  auto p1 = s.insert({3, 3});
  auto p2 = m.insert({3, 3});
  EXPECT_EQ(p1.second, p2.second);
}

TEST_F(Test_map, 2) {
  s21::map<int, int> s21{{1, 1}, {2, 2}, {3, 3}};

  std::map<int, double> std{{1, 1.1}, {2, 2.1}, {3, 3.1}};
  auto p1 = s21.insert({2, 2.2});
  auto p2 = std.insert({2, 2.2});
  EXPECT_EQ(p1.second, p2.second);
}

TEST_F(Test_map, 3) {
  s21::map<int, int> s21{{1, 1}, {2, 2}, {3, 3}};
  std::map<int, int> std{{1, 1}, {2, 2}, {3, 3}};
  auto p1 = s21.insert_or_assign(2, 4);
  EXPECT_EQ(p1.second, 0);
  EXPECT_EQ(s21.size(), 3);
  s21.insert(4, 4);
  s21.insert(5, 5);
  EXPECT_EQ(s21.size(), 5);
  EXPECT_EQ(s21.empty(), false);
}

TEST_F(Test_map, 4) { EXPECT_EQ(s21_emp->empty(), true); }

TEST_F(Test_map, 5) {
  EXPECT_EQ((s21_m->max_size() > 0), (std_m->max_size() > 0));
}

TEST_F(Test_map, 6) {
  EXPECT_EQ(s21_m->size(), std_m->size());
  EXPECT_EQ(s21_emp->size(), std_emp->size());
}

TEST_F(Test_map, 7) {
  s21_m->clear();
  std_m->clear();
  EXPECT_EQ(s21_m->size(), std_m->size());
  EXPECT_EQ(s21_m->empty(), std_m->empty());
}

TEST_F(Test_map, 8) {
  pair<int, int> tmp{1, 1};
  EXPECT_EQ(*s21_m->begin(), tmp);
}

TEST_F(Test_map, 9) {
  for (auto i = 1; i < 3; ++i)
    EXPECT_EQ(s21_m->at(i), std_m->at(i));
}

TEST_F(Test_map, 10) {
  pair<int, int> tmp{3, 3};
  EXPECT_EQ(*s21_m->end(), tmp);
}

TEST_F(Test_map, 11) {
  s21::map<int, int>::iterator it1 = s21_m->begin();
  std::map<int, int>::iterator it2 = std_m->begin();
  for (int i = 0; i < 3; ++i) {
    EXPECT_EQ((*it1).second, it2->second);
    ++it1;
    ++it2;
  }
}

TEST_F(Test_map, 12) {
  s21::map<int, int>::iterator it1;
  std::map<int, int>::iterator it2 = std_m->begin();
  s21::map<int, int> mm;
  mm = *s21_m;
  for (it1 = mm.begin(); it1 != mm.end(); ++it1, ++it2) {
    EXPECT_EQ((*it1).second, it2->second);
  }
}

TEST_F(Test_map, 13) {
  s21::map<int, int> test{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  s21::map<int, int> tmp{{4, 4}, {5, 5}};
  s21_emp->merge(*s21_m);
  s21_emp->merge(tmp);
  auto tst = test.begin();
  for (auto it = s21_emp->begin(); it != s21_emp->end(); ++it, ++tst)
    EXPECT_EQ((*it).second, (*tst).second);
}

TEST_F(Test_map, 14) {
  EXPECT_EQ(s21_m->contains(2), true);
  EXPECT_EQ(s21_m->contains(14), false);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}