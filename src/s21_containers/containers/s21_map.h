#ifndef CPP2_S21_CONTAINERS_S21_MAP_H_
#define CPP2_S21_CONTAINERS_S21_MAP_H_

#include <limits>

#include "s21_rb_iterator.h"

namespace s21 {
template <typename Key, typename T>
class s21_map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const Key, T>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator_category = std::bidirectional_iterator_tag;
  using size_type = size_t;
  using iterator = s21_iterator<Key, T>;
  // Map Member functions ==================================
  s21_map() : rb_tree_(){};

  s21_map(std::initializer_list<value_type> const &items) {
    for (const auto &item : items)
      rb_tree_.insertValue(0, item.first, item.second);
  }

  s21_map(const s21_map &m) { copy(m.rb_tree_.getNode()); }

  s21_map &operator=(const s21_map &m) { return *this = s21_map(m); }

  s21_map(s21_map &&m) noexcept : rb_tree_(std::move(m.rb_tree_)) { m.clear(); }

  s21_map &operator=(s21_map &&m) {
    if (this != &m) {
      clear();
      rb_tree_ = std::move(m.rb_tree_);
      m.clear();
    }
    return *this;
  }

  ~s21_map() { clear(); }
  // ========================================================

  // Map Element access =====================================
  T &operator[](const Key &key) {
    return (rb_tree_.findValue(key) ?: [&] { rb_tree_.insertValue(0, key, T()); return rb_tree_.findValue(key); }())->key_value.second;
  }

  T &at(const Key &key) {
    return rb_tree_.findValue(key) ? rb_tree_.findValue(key)->key_value.second
                                   : throw std::out_of_range("map::at");
  }

  // ========================================================

  // Map Iterators ==========================================
  iterator begin() noexcept {
    return empty() ? iterator(nullptr, &rb_tree_)
                   : iterator(rb_tree_.getMinimum(), &rb_tree_);
  }

  iterator end() noexcept { return iterator(nullptr, &rb_tree_); }
  // ========================================================

  // Map Capacity ===========================================
  bool empty() const noexcept { return rb_tree_.getSize() == 0; }

  size_type size() const noexcept { return rb_tree_.getSize(); }

  size_type max_size() const noexcept {
    return std::numeric_limits<size_t>::max() / sizeof(size_t) / 10;
  }
  // ========================================================

  //  Map Modifiers =========================================
  void clear() noexcept {
    clearNode(rb_tree_.getNode());
    rb_tree_ = Tree<Key, T>();
  }

  std::pair<iterator, bool> insert(const value_type &value) {
    return insert_impl(value.first, value.second);
  }

  std::pair<iterator, bool> insert(const Key &key, const T &obj) {
    return insert_impl(key, obj);
  }

  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj) {
    return insert_impl(key, obj, true);
  }

  std::pair<iterator, bool> insert_or_assign(Key &key, T &obj) {
    return insert_impl(key, obj, true);
  }

  void erase(iterator pos) noexcept {
    if (pos != end()) rb_tree_.removeValue(pos->first);
  }

  void swap(s21_map &other) noexcept { std::swap(rb_tree_, other.rb_tree_); }

  void merge(s21_map &other) {
    for (auto it = other.begin(); it != other.end(); ++it)
      rb_tree_.insertValue(0, it->first, it->second);
    other.clear();
  }
  // ========================================================

  // Map Lookup =============================================
  bool contains(const Key &key) noexcept {
    return rb_tree_.findValue(key) != nullptr;
  }
  // ========================================================

  // Insert Many  ===========================================
  template <class... Args>
  std::pair<iterator, bool> insert_many(Args &&...args) {
    return insert_impl(std::forward<Args>(args)...);
  }
  // ========================================================
 private:
  Tree<Key, T> rb_tree_;

  void copy(node<Key, T> *n) {
    if (n) {
      insert_impl(n->key_value.first, n->key_value.second);
      copy(n->left);
      copy(n->right);
    }
  }

  std::pair<iterator, bool> insert_impl(const Key &key, const T &obj,
                                        bool assign_if_exists = false) {
    node<Key, T> *node_found = rb_tree_.findValue(key);
    if (node_found) {
      if (assign_if_exists) node_found->key_value.second = obj;
      return std::make_pair(iterator(node_found, &rb_tree_), false);
    } else {
      rb_tree_.insertValue(0, key, obj);
      node<Key, T> *new_node = rb_tree_.findValue(key);
      return std::make_pair(iterator(new_node, &rb_tree_), true);
    }
  }

  void clearNode(node<Key, T> *root) {
    if (root) {
      clearNode(root->left);
      clearNode(root->right);
      delete root;
    }
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MAP_H_
