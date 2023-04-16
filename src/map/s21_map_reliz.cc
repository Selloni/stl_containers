#include "s21_map.h"
#include <utility>

using namespace s21;

template <typename T, typename S>
map<T, S>::map(std::initializer_list<value_type> const &items) {
  for (auto it = items.begin(); it != items.end(); ++it)
    insert(*it);
}

template <typename T, typename S> map<T, S>::map(const map &m) { *this = m; }

template <typename T, typename S> map<T, S>::map(map &&m) {
  *this = std::move(m);
}

template <typename T, typename S> map<T, S>::~map() {
  this->destroy(this->root_);
}

template <typename T, typename S> map<T, S> &map<T, S>::operator=(map &m) {
  this->clear();
  for (iterator it = m.begin(); it != m.end(); ++it)
    insert(*it);
  return *this;
}

template <typename T, typename S> map<T, S> &map<T, S>::operator=(map &&m) {
  this->root_ = m.root_;
  m.root_ = nullptr;
  m.clear();
}

template <typename T, typename S>
std::pair<typename map<T, S>::iterator, bool>
map<T, S>::insert(const value_type &value) {
  return push(this->root_, value);
}

template <typename T, typename S>
std::pair<typename map<T, S>::iterator, bool> map<T, S>::insert(const T &key,
                                                                const S &obj) {
  return insert(std::make_pair(key, obj));
}

template <typename T, typename S>
std::pair<typename map<T, S>::iterator, bool>
map<T, S>::insert_or_assign(const T &key, const S &obj) {
  std::pair<T, S> value = std::make_pair(key, obj);
  std::pair<typename map<T, S>::iterator, bool> res;
  node<T, S> *knot = this->root_;
  if (knot == nullptr) {
    knot = new node<T, S>(value, knot, nullptr, nullptr);
    return std::pair<typename map<T, S>::iterator, bool>{knot, true};
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
    knot->pair = value;
    return std::pair<typename map<T, S>::iterator, bool>{knot, false};
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

template <typename T, typename S> void map<T, S>::erase(iterator pos) {
  remove(this->root_, pos.elem->pair);
}

template <typename T, typename S> void map<T, S>::merge(map &other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    this->insert(*it);
  }
}

template <typename T, typename S> S &map<T, S>::at(const T &key) {
  iterator it(this->find_pair(this->root_, key));
  if (it.elem == nullptr)
    throw std::out_of_range("Map: at: out of range");
  return it.elem->pair.second;
}

template <typename T, typename S> S &map<T, S>::operator[](const T &key) {
  iterator it(this->find_pair(this->root_, key));
  return it.elem->pair.second;
}

template <typename T, typename S>
typename map<T, S>::iterator map<T, S>::begin() {
  iterator it(this->min_elem(this->root_));
  return it;
}

template <typename T, typename S>
typename map<T, S>::iterator map<T, S>::end() {
  node<T, S> *max = this->max_elem(this->root_);
  if (max != this->end_dummy) {
    this->end_dummy = new node<T, S>(max->pair, max, nullptr, nullptr);
    max->right = this->end_dummy;
  }
  iterator it(this->end_dummy);
  return it;
}

/////////////////////////////////////
////////////// PRIVATE /////////////
///////////////////////////////////

template <typename T, typename S>
std::pair<typename map<T, S>::iterator, bool>
map<T, S>::push(node<T, S> *(&knot), std::pair<T, S> value) {
  std::pair<typename map<T, S>::iterator, bool> res;
  if (knot == nullptr) {
    knot = new node<T, S>(value, knot, nullptr, nullptr);
    return std::pair<typename map<T, S>::iterator, bool>{knot, true};
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
    return std::pair<typename map<T, S>::iterator, bool>{knot, false};
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
