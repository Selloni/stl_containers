#include "s21_set.h"

using namespace s21;

template <typename T, typename S>
set<T, S>::set(std::initializer_list<key_type> const &items) {
  for (auto it = items.begin(); it != items.end(); ++it) {
    value_type pair = std::make_pair(*it, *it);
    this->insert(pair);
  }
}

template <typename T, typename S> set<T, S>::set(const set &s) {
  this->root_ = s.root_;
}

template <typename T, typename S> set<T, S>::set(set &&s) {
  this = std::move(s);
}

template <typename T, typename S> set<T, S> &set<T, S>::operator=(set &s) {
  for (iterator it = s.begin(); it != s.end(); ++it) {
    value_type pair = std::make_pair(it.elem->pair.first, it.elem->pair.first);
    this->insert(pair);
  }
  return *this;
}

template <typename T, typename S> set<T, S> &set<T, S>::operator=(set &&s) {
  this->root_ = s.root_;
  s.clear();
}

template <typename T, typename S>
typename set<T, S>::iterator set<T, S>::begin() {
  iterator it(this->min_elem(this->root_));
  return it;
}

template <typename T, typename S>
typename set<T, S>::iterator set<T, S>::end() {
  node<T, S> *max = this->max_elem(this->root_);
  if (max != this->end_dummy) {
    this->end_dummy = new node<T, S>(max->pair, max, nullptr, nullptr);
    max->right = this->end_dummy;
  }
  iterator it(this->end_dummy);
  return it;
}

template <typename T, typename S>
std::pair<typename set<T, S>::iterator, bool>
set<T, S>::insert(const value_type &value) {
  return this->push(this->root_, value);
}

template <typename T, typename S>
typename set<T, S>::iterator set<T, S>::find(const T &key) {
  iterator it(find_pair(this->root_, key));
  return it;
}

template <typename T, typename S> void set<T, S>::merge(set &other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    this->insert(*it);
  }
}

/////////////////////////////////////
////////////// PRIVATE /////////////
///////////////////////////////////

template <typename T, typename S>
std::pair<typename set<T, S>::iterator, bool>
set<T, S>::push(node<T, S> *(&knot), std::pair<T, S> value) {
  std::pair<typename set<T, S>::iterator, bool> res;
  if (knot == nullptr) {
    knot = new node<T, S>(value, knot, nullptr, nullptr);
    return std::pair<typename set<T, S>::iterator, bool>{knot, true};
  } else if (value < knot->pair) {
    if (knot->left == nullptr) {
      node<T, S> *tmp = new node<T, S>(value, knot, nullptr, nullptr);
      knot->left = tmp;
    } else {
      res = push(knot->left, value);
    }
    if ((this->height(knot->left) - this->height(knot->right)) > 1) {
      if (this->height(knot->left->left) < this->height(knot->left->right))
        this->turn_left(knot->left);
      this->turn_right(knot);
    }
  } else if (value.first == knot->pair.first) {
    return std::pair<typename set<T, S>::iterator, bool>{knot, false};
  } else {
    if (knot->right == nullptr) {
      node<T, S> *tmp = new node<T, S>(value, knot, nullptr, nullptr);
      knot->right = tmp;
    } else {
      res = push(knot->right, value);
    }
    if ((this->height(knot->right) - this->height(knot->left)) > 1) {
      if (this->height(knot->right->right) < this->height(knot->right->left))
        this->turn_right(knot->right);
      this->turn_left(knot);
    }
  }
  return res;
}