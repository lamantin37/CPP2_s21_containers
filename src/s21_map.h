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
  s21_map() : rb_tree(){};
  s21_map(std::initializer_list<value_type> const &items) {
    for (const auto &item : items) {
      rb_tree.insert_value(0, item.first, item.second);
    }
  }
  s21_map(const s21_map &m) { copy(m.rb_tree.getNode()); }
  s21_map &operator=(const s21_map &m) {
    if (this != &m) {
      clear();
      copy(m.rb_tree.getNode());
    }
    return *this;
  }
  s21_map(s21_map &&m) {
    rb_tree = std::move(m.rb_tree);
    m.clear();
  }
  s21_map &operator=(s21_map &&m) {
    if (this != &m) {
      clear();
      rb_tree = std::move(m.rb_tree);
      m.clear();
    }
    return *this;
  }
  ~s21_map() { clear(); }
  // ========================================================

  // Map Element access =====================================
  T &operator[](const Key &key) {
    node<Key, T> *n = rb_tree.find_value(key);
    if (n) {
      return n->key_value.second;
    } else {
      rb_tree.insert_value(0, key, T());
      return rb_tree.find_value(key)->key_value.second;
    }
  }
  T &at(const Key &key) {
    node<Key, T> *n = rb_tree.find_value(key);
    if (n) {
      return n->key_value.second;
    } else {
      throw std::out_of_range("map::at");
    }
  }
  // ========================================================

  // Map Iterators ==========================================
  iterator begin() noexcept {
    if (empty())
      return iterator(nullptr, &rb_tree);
    else
      return iterator(rb_tree.get_minimum(), &rb_tree);
  }
  iterator end() noexcept { return iterator(nullptr, &rb_tree); }
  // ========================================================

  // Map Capacity ===========================================
  bool empty() const noexcept { return rb_tree.getSize() == 0; }
  size_type size() const noexcept { return rb_tree.getSize(); }
  size_type max_size() const noexcept {
    return std::numeric_limits<size_t>::max() / sizeof(size_t) / 10;
  }
  // ========================================================

  //  Map Modifiers =========================================
  void clear() noexcept {
    clear_node(rb_tree.getNode());
    rb_tree = Tree<Key, T>();
  }
  std::pair<iterator, bool> insert(
      const value_type &value) {  // мб добавить другие виды инсертов
    node<Key, T> *node_found = rb_tree.find_value(value.first);
    if (node_found) {
      return std::make_pair(iterator(node_found, &rb_tree), false);
    } else {
      rb_tree.insert_value(0, value.first, value.second);
      node<Key, T> *new_node = rb_tree.find_value(value.first);
      return std::make_pair(iterator(new_node, &rb_tree), true);
    }
  }
  std::pair<iterator, bool> insert(const Key &key, const T &obj) {
    node<Key, T> *node_found = rb_tree.find_value(key);
    if (node_found) {
      return std::make_pair(iterator(node_found, &rb_tree), false);
    } else {
      rb_tree.insert_value(0, key, obj);
      node<Key, T> *new_node = rb_tree.find_value(key);
      return std::make_pair(iterator(new_node, &rb_tree), true);
    }
  }
  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj) {
    node<Key, T> *node_found = rb_tree.find_value(key);
    if (node_found) {
      node_found->key_value.second = obj;
      return std::make_pair(iterator(node_found, &rb_tree), false);
    } else {
      rb_tree.insert_value(0, key, obj);
      node<Key, T> *new_node = rb_tree.find_value(key);
      return std::make_pair(iterator(new_node, &rb_tree), true);
    }
  }
  std::pair<iterator, bool> insert_or_assign(Key &key, T &obj) {
    node<Key, T> *node_found = rb_tree.find_value(key);
    if (node_found) {
      node_found->key_value.second = obj;
      return std::make_pair(iterator(node_found, &rb_tree), false);
    } else {
      rb_tree.insert_value(0, key, obj);
      node<Key, T> *new_node = rb_tree.find_value(key);
      return std::make_pair(iterator(new_node, &rb_tree), true);
    }
  }
  void erase(iterator pos) noexcept {
    if (pos != end()) {
      rb_tree.remove_value(pos->first);
    }
  }
  void swap(s21_map &other) noexcept { std::swap(rb_tree, other.rb_tree); }
  void merge(s21_map &other) {
    for (auto it = other.begin(); it != other.end(); it++) {
      rb_tree.insert_value(0, it->first, it->second);
    }
    other.clear();
  }
  // ========================================================

  // Map Lookup =============================================
  bool contains(const Key &key) noexcept {
    return rb_tree.find_value(key) != nullptr;
  }
  // ========================================================

  // Insert Many  ===============================================
  template <class... Args>
  std::pair<iterator, bool> insert_many(Args &&...args) {
    std::pair<Key, T> value(std::forward<Args>(args)...);
    node<Key, T> *node_found = rb_tree.find_value(value.first);
    if (node_found) {
      return std::make_pair(iterator(node_found, &rb_tree), false);
    } else {
      rb_tree.insert_value(0, value.first, value.second);
      node<Key, T> *new_node = rb_tree.find_value(value.first);
      return std::make_pair(iterator(new_node, &rb_tree), true);
    }
  }
  // ========================================================
 private:
  Tree<Key, T> rb_tree;
  void copy(node<Key, T> *n) {
    if (n) {
      rb_tree.insert_value(0, n->key_value.first, n->key_value.second);
      copy(n->left);
      copy(n->right);
    }
  }

  void clear_node(node<Key, T> *root) {
    if (root == nullptr) {
      return;
    }
    clear_node(root->left);
    clear_node(root->right);
    delete root;
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MAP_H_