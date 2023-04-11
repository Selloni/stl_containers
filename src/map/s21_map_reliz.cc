#include "s21_map.h"

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

template <typename T, typename S> bool map<T, S>::empty() { return !size(); }

template <typename T, typename S> size_t map<T, S>::size() {
  return count(root_);
}

template <typename T, typename S> size_t map<T, S>::max_size() {
  std::allocator<T> alloc;
  return alloc.max_size();
}

template <typename T, typename S> void map<T, S>::clear() { destroy(root_); }

template <typename T, typename S>
std::pair<typename map<T, S>::iterator, bool>
map<T, S>::insert(const value_type &value) {
  return push(root_, value);
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
  node<T, S> *knot = root_;
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
    if ((height(knot->left) - height(knot->right)) > 1) {
      if (height(knot->left->left) < height(knot->left->right))
        turn_left(knot->left);
      turn_right(knot);
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
    if ((height(knot->right) - height(knot->left)) > 1) {
      if (height(knot->right->right) < height(knot->right->left))
        turn_right(knot->right);
      turn_left(knot);
    }
  }
  return res;
}

template <typename T, typename S> void map<T, S>::erase(iterator pos) {
  remove(root_, pos.elem->pair);
}

template <typename T, typename S> void map<T, S>::swap(map &other) {
  std::swap(root_, other.root_);
}

template <typename T, typename S> S &map<T, S>::at(const T &key) {
  iterator it(find_pair(root_, key));
  if (it.elem == nullptr)
    throw std::out_of_range("Map: at: out of range");
  return it.elem->pair.second;
}

template <typename T, typename S> S &map<T, S>::operator[](const T &key) {
  iterator it(find_pair(root_, key));
  return it.elem->pair.second;
}

template <typename T, typename S>
typename map<T, S>::iterator map<T, S>::begin() {
  iterator it(min_elem(root_));
  return it;
}

//// должен возвращать на адрес за элементом
template <typename T, typename S>
typename map<T, S>::iterator map<T, S>::end() {
  iterator it(max_elem(root_));
  return it;
}

template <typename T, typename S> void map<T, S>::merge(map &other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    this->insert(*it);
  }
}

template <typename T, typename S> bool map<T, S>::contains(const T &key) {
  if (find_pair(root_, key))
    return true;
  return false;
}

////////////////////////////////////
////////////// PRIVATE /////////////
//////////////////////////////////

template <typename T, typename S>
node<T, S> *map<T, S>::find_pair(node<T, S> *knot, const T &key) {
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
node<T, S> *map<T, S>::max_elem(node<T, S> *elem) {
  if (elem->right != nullptr)
    return max_elem(elem->right);
  return elem;
}

template <typename T, typename S>
node<T, S> *map<T, S>::min_elem(node<T, S> *elem) {
  if (elem->left != nullptr) {
    return min_elem(elem->left);
  }
  return elem;
}

template <typename T, typename S> size_t map<T, S>::count(node<T, S> *knot) {
  if (knot == nullptr)
    return 0;
  return count(knot->left) + count(knot->right) + 1;
}

template <typename T, typename S>
void map<T, S>::second_case(node<T, S> *(&knot)) {
  knot = (knot->left) ? knot->left : knot->right;
}

template <typename T, typename S>
void map<T, S>::first_case(node<T, S> *(&knot)) {
  delete knot;
  knot = nullptr;
}

template <typename T, typename S>
node<T, S> *map<T, S>::get_min(node<T, S> *(&knot)) {
  if (knot->left == nullptr) {
    return knot;
  } else {
    return get_min(knot->left);
  }
}

template <typename T, typename S>
node<T, S> *map<T, S>::get_max(node<T, S> *(&knot)) {
  if (knot->right == nullptr) {
    return knot;
  } else {
    return get_max(knot->right);
  }
}

template <typename T, typename S>
void map<T, S>::third_case(node<T, S> *(&knot)) {
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

template <typename T, typename S> void map<T, S>::destroy(node<T, S> *&knot) {
  if (knot == nullptr)
    return;
  destroy(knot->left);
  destroy(knot->right);
  delete knot;
  knot = nullptr;
}

template <typename T, typename S>
void map<T, S>::remove(node<T, S> *(&knot), std::pair<T, S> value) {
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
template <typename T, typename S> int map<T, S>::height(node<T, S> *knot) {
  if (knot == nullptr)
    return 0;
  return std::max(height(knot->left), height(knot->right)) + 1;
}

// возможжны проблемы из-за  res
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
    if ((height(knot->left) - height(knot->right)) > 1) {
      if (height(knot->left->left) < height(knot->left->right))
        turn_left(knot->left);
      turn_right(knot);
    }
  } else if (value.first == knot->pair.first) {
    //        knot->pair = value;
    return std::pair<typename map<T, S>::iterator, bool>{knot, false};
  } else {
    if (knot->right == nullptr) {
      node<T, S> *tmp = new node<T, S>(value, knot, nullptr, nullptr);
      knot->right = tmp;
    } else {
      res = push(knot->right, value);
    }
    if ((height(knot->right) - height(knot->left)) > 1) {
      if (height(knot->right->right) < height(knot->right->left))
        turn_right(knot->right);
      turn_left(knot);
    }
  }
  return res;
}

/////

template <typename T, typename S> void map<T, S>::print_key(node<T, S> *knot) {
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

////// поворот лувого подтерева на право/выше
template <typename T, typename S>
void map<T, S>::turn_right(node<T, S> *(&root)) {
  node<T, S> *knot_left = root->left;
  node<T, S> *knot_left_sub_right = root->left->right;
  knot_left->right = root;
  knot_left->parent = root->parent;
  root->parent = knot_left;
  root->left = knot_left_sub_right;
  root = knot_left;
}

template <typename T, typename S>
void map<T, S>::turn_left(node<T, S> *(&root)) {
  node<T, S> *knot_rght = root->right;
  node<T, S> *knot_rght_sub_left = root->right->left;
  knot_rght->left = root;
  knot_rght->parent = root->parent;
  root->parent = knot_rght;
  root->right = knot_rght_sub_left;
  root = knot_rght;
}

// ////////////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////////////////
// #include <memory>
// #include <vector>
// #define LN \
//   { std::cout << __LINE__ << std::endl; }
// #define DEB(x) \
//   { std::cout << #x << "=(" << (x) << ") "; }
// // std::string ch_hor = "-", ch_ver = "|", ch_ddia = "/", ch_rddia = "\\",
// // ch_udia = "\\", ch_ver_hor = "|-", ch_udia_hor = "\\-", ch_ddia_hor =
// "/-",
// // ch_ver_spa = "| ";
// static std::string ch_hor = "\u2500" /*─*/, ch_ver = "\u2502" /*│*/,
//                    ch_ddia = "\u250C" /*┌*/, ch_rddia = "\u2510" /*┐*/,
//                    ch_udia = "\u2514" /*└*/, ch_ver_hor = "\u251C\u2500"
//                    /*├─*/, ch_udia_hor = "\u2514\u2500" /*└─*/, ch_ddia_hor =
//                    "\u250C\u2500" /*┌─*/, ch_ver_spa = "\u2502 " /*│ */;

// template <typename T, typename S>
// void print_tree(
//     node<T, S> const *knot, bool high = true,
//     std::vector<std::string> const &lpref = std::vector<std::string>(),
//     std::vector<std::string> const &cpref = std::vector<std::string>(),
//     std::vector<std::string> const &rpref = std::vector<std::string>(),
//     bool root = true, bool left = true,
//     std::shared_ptr<std::vector<std::vector<std::string>>> lines = nullptr) {
//   if (!knot)
//     return;
//   typedef std::vector<std::string> VS;
//   auto VSCat = [](VS const &a, VS const &b) {
//     auto r = a;
//     r.insert(r.end(), b.begin(), b.end());
//     return r;
//   };
//   if (root)
//     lines = std::make_shared<std::vector<VS>>();
//   if (knot->left)
//     print_tree(knot->left, high,
//                VSCat(lpref, high ? VS({" ", " "}) : VS({" "})),
//                VSCat(lpref, high ? VS({ch_ddia, ch_ver}) : VS({ch_ddia})),
//                VSCat(lpref, high ? VS({ch_hor, " "}) : VS({ch_hor})), false,
//                true, lines);
//   auto sval = std::to_string(knot->pair.first);
//   size_t sm =
//       left || sval.empty() ? sval.size() / 2 : ((sval.size() + 1) / 2 - 1);
//   for (size_t i = 0; i < sval.size(); ++i)
//     lines->push_back(VSCat(i < sm    ? lpref
//                            : i == sm ? cpref
//                                      : rpref,
//                            {std::string(1, sval[i])}));
//   if (knot->right)
//     print_tree(knot->right, high,
//                VSCat(rpref, high ? VS({ch_hor, " "}) : VS({ch_hor})),
//                VSCat(rpref, high ? VS({ch_rddia, ch_ver}) : VS({ch_rddia})),
//                VSCat(rpref, high ? VS({" ", " "}) : VS({" "})), false, false,
//                lines);
//   if (root) {
//     VS out;
//     for (size_t l = 0;; ++l) {
//       bool last = true;
//       std::string line;
//       for (size_t i = 0; i < lines->size(); ++i)
//         if (l < (*lines).at(i).size()) {
//           line += lines->at(i)[l];
//           last = false;
//         } else
//           line += " ";
//       if (last)
//         break;
//       out.push_back(line);
//     }
//     for (size_t i = 0; i < out.size(); ++i)
//       std::cout << out[i] << std::endl;
//   }
// }
// ////////////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////////////////
