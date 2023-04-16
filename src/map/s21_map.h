#ifndef S21_MAP_H_
#define S21_MAP_H_

// #include "../tree/tree.h"
#include "../virtual_class/virtual_assoc_reliz.cc"

namespace s21 {

template <typename T, typename S> class map : public virtual_map_set<T, S> {

public:
  ////////////////////////////
  ////  Map Member type  ////
  //////////////////////////
  using key_type = T;
  using mapped_type = S;
  using value_type = std::pair<const key_type, mapped_type>;
  using refernce = value_type &;
  using const_reference = const value_type &;
  using iterator = iterator_map<T, S>;
  using size_type = size_t;
  /////////////////////////////
  ////Map Member functions////
  ///////////////////////////
  map(){};
  map(std::initializer_list<value_type> const &items);
  map(const map &m);
  map(map &&m);
  ~map();
  map &operator=(map &m);
  map &operator=(map &&m);
  /////////////////////////////
  ////   Map Iterators    ////
  ///////////////////////////
  S &at(const T &key);
  S &operator[](const T &key);
  iterator begin();
  iterator end();
  /////////////////////////////
  ////    Map Capacity    ////
  ///////////////////////////
  // bool empty();
  // size_type size();
  // size_type max_size();
  /////////////////////////////
  ////   Map Modifiers    ////
  ///////////////////////////
  // void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const T &key, const S &obj);
  std::pair<iterator, bool> insert_or_assign(const T &key, const S &obj);
  void erase(iterator pos);
  // void swap(map &other);
  void merge(map &other);
  /////////////////////////////
  ////     Map Lookup     ////
  ///////////////////////////
  // bool contains(const T &key);

protected:
  // node<T, S> *find_pair(node<T, S> *knot, const T &key);
  // node<T, S> *max_elem(node<T, S> *elem);
  // node<T, S> *min_elem(node<T, S> *elem);
  // size_type count(node<T, S> *knot);
  // void turn_left(node<T, S> *(&root));
  // void turn_right(node<T, S> *(&root));
  // void print_key(node<T, S> *knot);
  std::pair<iterator, bool> push(node<T, S> *(&knot), std::pair<T, S> value);
  // void set_balance(node<T, S> *knot);
  // int height(node<T, S> *knot);
  // void destroy(node<T, S> *&knot);
  // void remove(node<T, S> *&knot, std::pair<T, S> value);
  // node<T, S> *get_min(node<T, S> *(&knot));
  // node<T, S> *get_max(node<T, S> *(&knot));
  // void first_case(node<T, S> *(&knot));
  // void second_case(node<T, S> *(&knot));
  // void third_case(node<T, S> *(&knot));
};
} // namespace s21

#endif // S21_MAP_H_