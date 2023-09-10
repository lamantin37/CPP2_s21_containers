#ifndef CPP2_S21_CONTAINERS_S21_SET_H_
#define CPP2_S21_CONTAINERS_S21_SET_H_

#include <iostream>
#include <limits>

#include "s21_rb_iterator.h"

namespace s21 {
template <typename Key>
class s21_set {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using iterator = s21_iterator<Key>;
  // Set Member functions ==================================
  s21_set() : rb_tree(){};
  s21_set(std::initializer_list<value_type> const &items) {
    for (const auto &item : items) {
      rb_tree.insert_value(0, item);
    }
  }
  s21_set(s21_set &s) { copy(s.rb_tree.getNode()); }
  s21_set(s21_set &&s) {
    rb_tree = std::move(s.rb_tree);
    s.clear();
  }
  ~s21_set() { clear(); }
  s21_set &operator=(s21_set &&s) {
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
  std::pair<iterator, bool> insert(const value_type &value) {
    node<value_type> *node_found = rb_tree.find_value(value);
    if (node_found) {
      return std::make_pair(iterator(node_found, &rb_tree), false);
    } else {
      rb_tree.insert_value(0, value);
      node<value_type> *new_node = rb_tree.find_value(value);
      return std::make_pair(iterator(new_node, &rb_tree), true);
    }
  }
  void erase(iterator pos) {  // обработать удаление последнего элемента
    if (pos != end()) {
      rb_tree.remove_value(*pos);
    }
  }
  void swap(s21_set &other) { std::swap(rb_tree, other.rb_tree); }
  void merge(s21_set &other) {
    for (iterator it = other.begin(); it != other.end(); it++) {
      rb_tree.insert_value(0, *it);
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
  // ========================================================

  // Emplace  ===============================================
  template <class... Args>
  std::pair<iterator, bool> emplace(Args &&...args) {
    value_type value(std::forward<Args>(args)...);
    node<value_type> *node_found = rb_tree.find_value(value);
    if (node_found) {
      return std::make_pair(iterator(node_found, &rb_tree), false);
    } else {
      rb_tree.insert_value(0, value);
      node<value_type> *new_node = rb_tree.find_value(value);
      return std::make_pair(iterator(new_node, &rb_tree), true);
    }
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
        rb_tree.insert_value(0, n->key_value.first);
        copy(n->left);
        copy(n->right);
      }
    }
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_SET_H_