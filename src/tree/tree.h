// #pragma
#ifndef S21_TREE_H_
#define S21_TREE_H_

#include <iostream>
#include <utility>

namespace s21 {
template <typename T, typename S> struct node {
public:
  std::pair<T, S> pair;
  node<T, S> *parent = nullptr;
  node<T, S> *left = nullptr;
  node<T, S> *right = nullptr;
  node(std::pair<T, S> two, node *p, node *l, node *r)
      : pair(two), parent(p), left(l), right(r){};
  node() : parent(nullptr), left(nullptr), right(nullptr){};
}; // node

template <typename T, typename S> class iterator_tree {
public:
  node<T, S> *elem = nullptr;
  iterator_tree<T, S> &operator++();
  iterator_tree<T, S> &operator--();
  bool operator!=(const iterator_tree<T, S> &it) { return elem != it.elem; }
  bool operator==(const iterator_tree<T, S> &it) { return elem == it.elem; }
  iterator_tree() : elem(nullptr){};
  iterator_tree(node<T, S> *ref) : elem(ref) {}
  std::pair<T, S> &operator*() { return this->elem->pair; }
}; // iterator_tree
} // namespace s21
#endif //  S21_TREE_H_