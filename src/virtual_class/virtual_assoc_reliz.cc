#include "virtual_associativ.h"

using namespace s21;

template <typename T, typename S> bool virtual_map_set<T, S>::empty() {
  return !size();
}

template <typename T, typename S> size_t virtual_map_set<T, S>::max_size() {
  std::allocator<T> alloc;
  return alloc.max_size();
}

template <typename T, typename S> void virtual_map_set<T, S>::clear() {
  destroy(root_);
}

template <typename T, typename S>
void virtual_map_set<T, S>::swap(virtual_map_set &other) {
  std::swap(root_, other.root_);
}

template <typename T, typename S>
bool virtual_map_set<T, S>::contains(const T &key) {
  if (find_pair(root_, key))
    return true;
  return false;
}

/////////////////////////////////////
////////////// PRIVATE /////////////
///////////////////////////////////

template <typename T, typename S> size_t virtual_map_set<T, S>::size() {
  return count(root_);
}

template <typename T, typename S>
node<T, S> *virtual_map_set<T, S>::find_pair(node<T, S> *knot, const T &key) {
  if (knot == nullptr)
    return nullptr;
  if (key < knot->pair.first) {
    return find_pair(knot->left, key);
  } else if (key > knot->pair.first) {
    return find_pair(knot->right, key);
  } else {
    return knot;
  }
}

template <typename T, typename S>
node<T, S> *virtual_map_set<T, S>::max_elem(node<T, S> *elem) {
  if (elem->right != nullptr)
    return max_elem(elem->right);
  return elem;
}

template <typename T, typename S>
node<T, S> *virtual_map_set<T, S>::min_elem(node<T, S> *elem) {
  if (elem->left != nullptr) {
    return min_elem(elem->left);
  }
  return elem;
}

template <typename T, typename S>
size_t virtual_map_set<T, S>::count(node<T, S> *knot) {
  if (knot == nullptr)
    return 0;
  return count(knot->left) + count(knot->right) + 1;
}

template <typename T, typename S>
void virtual_map_set<T, S>::second_case(node<T, S> *(&knot)) {
  knot = (knot->left) ? knot->left : knot->right;
}

template <typename T, typename S>
void virtual_map_set<T, S>::first_case(node<T, S> *(&knot)) {
  delete knot;
  knot = nullptr;
}

template <typename T, typename S>
node<T, S> *virtual_map_set<T, S>::get_min(node<T, S> *(&knot)) {
  if (knot->left == nullptr) {
    return knot;
  } else {
    return get_min(knot->left);
  }
}

template <typename T, typename S>
node<T, S> *virtual_map_set<T, S>::get_max(node<T, S> *(&knot)) {
  if (knot->right == nullptr) {
    return knot;
  } else {
    return get_max(knot->right);
  }
}

template <typename T, typename S>
void virtual_map_set<T, S>::third_case(node<T, S> *(&knot)) {
  node<T, S> *min = get_min(knot->right);
  node<T, S> *tmp =
      new node<T, S>(min->pair, knot->parent, knot->left, knot->right);
  if (min->right != nullptr) {
    min->parent->left = min->right;
  }
  knot = tmp;
  remove(tmp->right, min->pair);
  if (height(knot->left) - height(knot->right) < 1) {
    turn_right(knot);
  } else if ((height(knot->left) - height(knot->right) > 1)) {
    turn_left(knot);
  }
}

template <typename T, typename S>
void virtual_map_set<T, S>::destroy(node<T, S> *&knot) {
  if (knot == nullptr)
    return;
  destroy(knot->left);
  destroy(knot->right);
  delete knot;
  knot = nullptr;
}

template <typename T, typename S>
void virtual_map_set<T, S>::remove(node<T, S> *(&knot), std::pair<T, S> value) {
  if (knot == nullptr)
    return;
  if (value < knot->pair) {
    remove(knot->left, value);
  } else if (value > knot->pair) {
    remove(knot->right, value);
  } else {
    if (knot->right == nullptr && knot->left == nullptr) {
      first_case(knot);
    } else if (knot->right == nullptr || knot->left == nullptr) {
      second_case(knot);
    } else {
      third_case(knot);
    }
  }
}

////// определяем максимальную высоту дерева
template <typename T, typename S>
int virtual_map_set<T, S>::height(node<T, S> *knot) {
  if (knot == nullptr)
    return 0;
  return std::max(height(knot->left), height(knot->right)) + 1;
}

/////

template <typename T, typename S>
void virtual_map_set<T, S>::print_key(node<T, S> *knot) {
  if (knot != nullptr) {
    if (knot->left != nullptr) {
      print_key(knot->left);
    }
    std::cout << knot->pair.first << "-" << knot->pair.second << std::endl;
    if (knot->right != nullptr) {
      print_key(knot->right);
    }
  }
}
/////////

////// поворот лeвого подтерева на право/выше
template <typename T, typename S>
void virtual_map_set<T, S>::turn_right(node<T, S> *(&root)) {
  node<T, S> *knot_left = root->left;
  node<T, S> *knot_left_sub_right = root->left->right;
  knot_left->right = root;
  knot_left->parent = root->parent;
  root->parent = knot_left;
  root->left = knot_left_sub_right;
  root = knot_left;
}

template <typename T, typename S>
void virtual_map_set<T, S>::turn_left(node<T, S> *(&root)) {
  node<T, S> *knot_rght = root->right;
  node<T, S> *knot_rght_sub_left = root->right->left;
  knot_rght->left = root;
  knot_rght->parent = root->parent;
  root->parent = knot_rght;
  root->right = knot_rght_sub_left;
  root = knot_rght;
}