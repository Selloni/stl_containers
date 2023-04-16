#ifndef S21_SET_H_
#define S21_SET_H_

#include "../virtual_class/virtual_assoc_reliz.cc"

namespace s21 {

template <class T, typename S> class set : public virtual_map_set<T, S> {
public:
  using key_type = T;
  using value_type = std::pair<const T, T>;
  using refernce = value_type &;
  using const_reference = const value_type &;
  using iterator = iterator_set<T, S>;
  using const_iterator = const iterator_set<T, S>;
  using size_type = size_t;

  set(){};
  set(std::initializer_list<key_type> const &items);
  set(const set &s);
  set(set &&s);
  ~set() { this->destroy(this->root_); };

  set &operator=(set &s);
  set &operator=(set &&s);
  /////////////////////////////
  ////   Set Iterators    ////
  ///////////////////////////
  iterator begin();
  iterator end();
  //   /////////////////////////////
  //   ////    Set Capacity    ////
  //   ///////////////////////////
  //   bool empty();
  //   size_type size();
  //   size_type max_size();
  //   /////////////////////////////
  //   ////   Set Modifiers    ////
  //   ///////////////////////////
  //   void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  //   void swap(set &other);
  void merge(set &other);
  /////////////////////////////
  ////     Set Lookup     ////
  ///////////////////////////
  iterator find(const T &key);
  //   bool contains(const T &key);

private:
  node<T, S> *find_pair(node<T, S> *knot, const T &key);
  //   node<T, S> *max_elem(node<T, S> *elem);
  //   node<T, S> *min_elem(node<T, S> *elem);
  //   size_type count(node<T, S> *knot);
  //   void turn_left(node<T, S> *(&root));
  //   void turn_right(node<T, S> *(&root));
  //   void print_key(node<T, S> *knot);
  std::pair<iterator, bool> push(node<T, S> *(&knot), std::pair<T, S> value);
  //  void set_balance(node<T, S> *knot);
  //  int height(node<T, S> *knot);
  //   void destroy(node<T, S> *&knot);
  //   void remove(node<T, S> *&knot, std::pair<T, S> value);
  //   node<T, S> *get_min(node<T, S> *(&knot));
  //   node<T, S> *get_max(node<T, S> *(&knot));
  //   void first_case(node<T, S> *(&knot));
  //   void second_case(node<T, S> *(&knot));
  //   void third_case(node<T, S> *(&knot));
}; // set

} // namespace s21

#endif // S21_SET_H_