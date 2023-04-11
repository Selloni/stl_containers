#include "s21_set.h"

using namespace s21;

template <typename T, typename S>
set<T, S>::set(std::initializer_list<value_type> const &items) {
  for (auto it = items.begin(); it != items.end(); ++it)
    this->insert(*it);
}

template <typename T, typename S> set<T, S>::set(const set &s) {
  this->root_ = s.root_;
}

template <typename T, typename S> set<T, S>::set(set &&s) {
  this = std::move(s);
}

template <typename T, typename S> set<T, S> &set<T, S>::operator=(set &s) {
  for (auto it = s.begin(); it != s.end(); ++it) {
    this->insert(*it);
  }
}

template <typename T, typename S> set<T, S> &set<T, S>::operator=(set &&s) {
  this->root_ = s.root_;
  s.clear();
}

template <typename T, typename S>
std::pair<typename map<T, S>::iterator, bool>
set<T, S>::insert(const value_type &value) {
  return this->push(root_, value);
}

template <typename T, typename S>
typename set<T, S>::iterator set<T, S>::find(const T &key) {
  iterator it(find_pair(root_, key));
  return it;
}