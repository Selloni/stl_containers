#ifndef S21_SET_H_
#define S21_SET_H_

#include "../set/s21_set.h"
#include "../set/s21_set_reliz.cc"
#include "../tree/tree.h"
#include "../virtual_class/virtual_associativ.h"

namespace s21 {

template <typename T, typename S> class multiset : public set<T, S> {
public:
  using key_type = T;
  using value_type = std::pair<const T, T>;
  using refernce = value_type &;
  using const_reference = const value_type &;
  using iterator = iterator_set<T, S>;
  using const_iterator = const iterator_set<T, S>;
  using size_type = size_t;

public:
  multiset() {}
  multiset(std::initializer_list<value_type> const &items);
  multiset(const multiset &ms);
  multiset(multiset &&ms);
  ~multiset();

  // multiset &operator=(multiset &&ms);
  // iterator begin();
  // iterator end();
  // bool empty();
  // size_type size();
  // size_type max_size();
  // void clear();
  iterator insert(const value_type &value);
  // void erase(iterator pos);
  // void swap(multiset &other);
  // void merge(multiset &other);
  // size_type count(const key_type &key);
  // iterator find(const key_type &key);
  // bool contains(const key_type &key);
  std::pair<iterator, iterator> equal_range(const key_type &key);
  iterator lower_bound(const key_type &key);
  iterator upper_bound(const key_type &key);
}; // multiset

} // namespace s21

#endif // S21_SET_H_