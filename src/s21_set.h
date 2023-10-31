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
  s21_set() : rb_tree_(){};

  s21_set(std::initializer_list<value_type> const &items) {
    for (const auto &item : items) rb_tree_.insertValue(0, item);
  }

  s21_set(const s21_set &s) { copy(s.rb_tree_.getNode()); }

  s21_set &operator=(const s21_set &s) { return *this = s21_set(s); }

  s21_set(s21_set &&s) : rb_tree_(std::move(s.rb_tree_)) { s.clear(); }

  s21_set &operator=(s21_set &&s) {
    if (this != &s) {
      clear();
      rb_tree_ = std::move(s.rb_tree_);
      s.clear();
    }
    return *this;
  }

  ~s21_set() { clear(); }
  // ========================================================

  // Set Iterators  =========================================
  iterator begin() noexcept {
    return empty() ? iterator(nullptr, &rb_tree_)
                   : iterator(rb_tree_.getMinimum(), &rb_tree_);
  }
  iterator end() noexcept { return iterator(nullptr, &rb_tree_); }
  // ========================================================

  // Set Capacity ===========================================
  bool empty() const noexcept { return rb_tree_.getSize() == 0; }

  size_type size() const noexcept { return rb_tree_.getSize(); }

  size_type max_size() const noexcept {
    return std::numeric_limits<size_t>::max() / sizeof(node<value_type>) / 2;
  }
  // ========================================================

  // Set Modifiers  =========================================
  void clear() noexcept {
    clearNode(rb_tree_.getNode()), rb_tree_ = Tree<value_type>();
  }

  std::pair<iterator, bool> insert(const value_type &value) {
    node<value_type> *node_found = rb_tree_.findValue(value);
    bool inserted = !node_found;
    if (inserted) rb_tree_.insertValue(0, value);
    return {
        iterator(inserted ? rb_tree_.findValue(value) : node_found, &rb_tree_),
        inserted};
  }

  void erase(iterator pos) noexcept {
    if (pos != end()) rb_tree_.removeValue(*pos);
  }

  void swap(s21_set &other) noexcept { std::swap(rb_tree_, other.rb_tree_); }

  void merge(s21_set &other) {
    for (iterator it = other.begin(); it != other.end(); ++it) {
      rb_tree_.insertValue(0, *it);
    }
    other.clear();
  }

  // ========================================================

  // Set Lookup  ============================================
  bool contains(const Key &key) noexcept { return rb_tree_.findValue(key); }

  iterator find(const Key &key) {
    return iterator(rb_tree_.findValue(key) ?: nullptr, &rb_tree_);
  }
  // ========================================================

  // Insert Many  ===========================================
  template <class... Args>
  std::pair<iterator, bool> insert_many(Args &&...args) {
    value_type value(std::forward<Args>(args)...);
    bool inserted = !rb_tree_.findValue(value);
    if (inserted) rb_tree_.insertValue(0, value);
    return {iterator(inserted ? rb_tree_.findValue(value)
                              : rb_tree_.findValue(value),
                     &rb_tree_),
            inserted};
  }
  // ========================================================
 private:
  Tree<value_type, int> rb_tree_;

  void clearNode(node<value_type> *root) {
    if (root) {
      clearNode(root->left);
      clearNode(root->right);
      delete root;
    }
  }

  void copy(node<value_type> *n) {
    if (n && !rb_tree_.findValue(n->key_value.first)) {
      rb_tree_.insertValue(0, n->key_value.first);
      copy(n->left);
      copy(n->right);
    }
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_SET_H_