#ifndef CPP2_S21_CONTAINERS_S21_MULTISET_H_
#define CPP2_S21_CONTAINERS_S21_MULTISET_H_

#include <iostream>
#include <limits>

#include "s21_rb_iterator.h"

namespace s21 {
template <typename Key>
class s21_multiset {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using iterator = s21_iterator<Key>;
  // Set Member functions ==================================
  Tree<value_type, int> &getTree() { return rb_tree; }
  s21_multiset() : rb_tree(){};
  s21_multiset(std::initializer_list<value_type> const &items) {
    for (const auto &item : items) {
      rb_tree.insert_value(1, item);
    }
  }
  s21_multiset(s21_multiset &s) { copy(s.rb_tree.getNode()); }
  s21_multiset(s21_multiset &&s) {
    rb_tree = std::move(s.rb_tree);
    s.clear();
  }
  ~s21_multiset() { clear(); }
  s21_multiset &operator=(s21_multiset &&s) {
    if (this != &s) {
      this->clear();
      this->rb_tree = std::move(s.rb_tree);
    }
    return *this;
  }
  // ========================================================

  // Set Iterators  =========================================
  iterator begin() {
    if (empty())
      return iterator(nullptr, &rb_tree);
    else
      return iterator(rb_tree.get_minimum(), &rb_tree);
  }
  iterator end() { return iterator(nullptr, &rb_tree); }
  // ========================================================

  // Set Capacity ===========================================
  bool empty() { return rb_tree.getSize() == 0; }
  size_type size() { return rb_tree.getSize(); }
  size_type max_size() {
    return std::numeric_limits<size_t>::max() / sizeof(node<value_type>) / 2;
  }
  // ========================================================

  // Set Modifiers  =========================================
  void clear() {
    clear_node(rb_tree.getNode());
    rb_tree = Tree<value_type>();
  }
  iterator insert(const value_type &value) {
    rb_tree.insert_value(1, value);
    node<value_type> *new_node = rb_tree.find_value(value);
    return iterator(new_node, &rb_tree);
  }
  void erase(iterator pos) {  // обработать удаление последнего элемента
    if (pos != end()) {
      rb_tree.remove_value(pos->first);
    }
  }
  void swap(s21_multiset &other) { std::swap(rb_tree, other.rb_tree); }
  void merge(s21_multiset &other) {
    for (iterator it = other.begin(); it != other.end(); it++) {
      rb_tree.insert_value(1, *it);  //
    }
    other.clear();
  }
  // ========================================================

  // Set Lookup  ============================================
  bool contains(const Key &key) { return rb_tree.find_value(key); }
  iterator find(const Key &key) {
    node<Key> *node_found = rb_tree.find_value(key);
    if (node_found) {
      return iterator(node_found, &rb_tree);
    } else {
      return end();
    }
  }
  size_type count(const Key &key) {
    size_type counter = 0;
    for (iterator it = begin(); it != end(); it++) {
      if ((*it) == key) counter++;
    }
    return counter;
  }
  std::pair<iterator, iterator> equal_range(const Key &key) {
    iterator it1(rb_tree.find_value(key), &rb_tree);
    iterator it2 = begin();
    std::pair<iterator, iterator> it_pair;
    for (it2; it2 != end(); it2++) {
      if ((*it2) == key) {
        it_pair = std::make_pair(it1, it2);
      }
    }
    return it_pair;
  }
  iterator lower_bound(const Key &key) {
    for (iterator it = begin(); it != end(); it++) {
      if ((*it) >= key) return it;
    }
    iterator def_iteratorl;
    return def_iteratorl;
  }
  iterator upper_bound(const Key &key) {
    for (iterator it = begin(); it != end(); it++) {
      if ((*it) > key) return it;
    }
    iterator def_iteratorl;
    return def_iteratorl;
  }
  // ========================================================

  // Emplace  ===============================================
  template <class... Args>
  std::pair<iterator, bool> insert_many(Args &&...args) {
    value_type value(std::forward<Args>(args)...);
    rb_tree.insert_value(1, value);
    node<value_type> *new_node = rb_tree.find_value(value);
    return std::make_pair(iterator(new_node, &rb_tree), true);
  }
  // ========================================================
 private:
  Tree<value_type, int> rb_tree;
  void clear_node(node<value_type> *root) {
    if (root == nullptr) {
      return;
    }
    clear_node(root->left);
    clear_node(root->right);
    delete root;
  }
  void copy(node<value_type> *n) {
    if (n) {
      if (!rb_tree.find_value(n->key_value.first)) {
        rb_tree.insert_value(1, n->key_value.first);
        copy(n->left);
        copy(n->right);
      }
    }
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MULTISET_H_