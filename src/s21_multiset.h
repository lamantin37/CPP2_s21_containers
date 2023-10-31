#ifndef CPP2_S21_CONTAINERS_S21_MULTISET_H_
#define CPP2_S21_CONTAINERS_S21_MULTISET_H_

#include <algorithm>
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
  s21_multiset() : rb_tree_(){};

  s21_multiset(std::initializer_list<value_type> const &items) {
    for (const auto &item : items) rb_tree_.insertValue(1, item);
  }

  s21_multiset(const s21_multiset &s) { copy(s.rb_tree_.getNode()); }

  s21_multiset &operator=(const s21_multiset &s) {
    return *this = s21_multiset(s);
  }

  s21_multiset(s21_multiset &&s) noexcept : rb_tree_(std::move(s.rb_tree_)) {
    s.clear();
  }

  s21_multiset &operator=(s21_multiset &&s) {
    if (this != &s) {
      clear();
      rb_tree_ = std::move(s.rb_tree_);
      s.clear();
    }
    return *this;
  }

  ~s21_multiset() { clear(); }
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

  iterator insert(const value_type &value) {
    rb_tree_.insertValue(1, value);
    return iterator(rb_tree_.findValue(value), &rb_tree_);
  }

  void erase(iterator pos) noexcept {
    if (pos != end()) rb_tree_.removeValue(*pos);
  }

  void swap(s21_multiset &other) noexcept {
    std::swap(rb_tree_, other.rb_tree_);
  }

  void merge(s21_multiset &other) {
    for (iterator it = other.begin(); it != other.end(); ++it)
      rb_tree_.insertValue(1, *it);
    other.clear();
  }
  // ========================================================

  // Set Lookup  ============================================
  bool contains(const Key &key) noexcept {
    return rb_tree_.findValue(key) != nullptr;
  }

  iterator find(const Key &key) {
    return iterator(rb_tree_.findValue(key) ?: nullptr, &rb_tree_);
  }

  size_type count(const Key &key) {
    size_type counter = 0;
    for (iterator it = begin(); it != end(); ++it) counter += *it == key;
    return counter;
  }

  iterator lower_bound(const Key &key) { return bound(key, false); }

  iterator upper_bound(const Key &key) { return bound(key, true); }

  std::pair<iterator, iterator> equal_range(const Key &key) {
    return {lower_bound(key), upper_bound(key)};
  }
  // ========================================================

  // Insert many  ===========================================
  template <class... Args>
  std::pair<iterator, bool> insert_many(Args &&...args) {
    value_type value(std::forward<Args>(args)...);
    rb_tree_.insertValue(1, value);
    return std::make_pair(iterator(rb_tree_.findValue(value), &rb_tree_), true);
  }

  Tree<value_type, int> getTree() { return rb_tree_; }
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
      rb_tree_.insertValue(1, n->key_value.first);
      copy(n->left);
      copy(n->right);
    }
  }

  iterator bound(const Key &key, bool upper) {
    for (auto it = begin(); it != end(); ++it)
      if (*it > key || (!upper && *it == key)) return it;
    return end();
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MULTISET_H_