#ifndef CPP2_S21_CONTAINERS_S21_RB_ITERATOR_H_
#define CPP2_S21_CONTAINERS_S21_RB_ITERATOR_H_

#include "s21_rb_tree.h"

template <typename Key, typename T>
class s21_map;
template <typename Key>
class s21_set;

template <typename Key, typename T = int>
class s21_iterator {
  friend class s21_map<Key, T>;
  friend class s21_set<Key>;
  using value_type = typename std::conditional<std::is_same<T, int>::value, Key,
                                               std::pair<const Key, T>>::type;

 public:
  s21_iterator(node<Key, T> *ptr, Tree<Key, T> *tree)
      : ptr_(ptr), tree_(tree) {}
  s21_iterator() : ptr_(nullptr) {}
  s21_iterator &operator++(int) {
    if (ptr_->right) {
      ptr_ = ptr_->right;
      while (ptr_->left) {
        ptr_ = ptr_->left;
      }
    } else {
      node<Key, T> *parent = ptr_->parent;
      while (parent && ptr_ == parent->right) {
        ptr_ = parent;
        parent = parent->parent;
      }
      ptr_ = parent;
    }
    return *this;
  }

  s21_iterator &operator--(int) {
    if (!ptr_) {
      ptr_ = tree_->get_maximum();
    } else {
      if (ptr_->left) {
        ptr_ = ptr_->left;
        while (ptr_->right) {
          ptr_ = ptr_->right;
        }
      } else {
        node<Key, T> *parent = ptr_->parent;
        while (parent && ptr_ == parent->left) {
          ptr_ = parent;
          parent = parent->parent;
        }
        if (parent == nullptr) {
          ptr_ = nullptr;
        } else {
          ptr_ = parent;
        }
      }
    }
    return *this;
  }
  value_type &operator*() const {
    if (ptr_ != nullptr) {
      if constexpr (std::is_same<value_type, Key>::value) {
        return ptr_->key_value.first;
      } else {
        return ptr_->key_value;
      }
    } else {
      static value_type default_value;
      return default_value;
    }
  }

  auto *operator->() const { return &ptr_->key_value; }
  // std::pair<Key, T> &operator*() const {
  //   if (ptr_ != nullptr) {
  //     return ptr_->key_value;
  //   } else {
  //     static std::pair<Key, T> default_value = std::pair<Key, T>();
  //     return default_value;
  //   }
  // }

  // Key &operator*() {
  //   if (ptr_ != nullptr) {
  //     return ptr_->key_value.first;
  //   } else {
  //     static Key default_value = Key();
  //     return default_value;
  //   }
  // }

  // Key *operator->() { return &(ptr_->key_value); }

  // std::pair<Key, T> *operator->() const { return &(ptr_->key_value); }

  bool operator==(const s21_iterator &other) const {
    return ptr_ == other.ptr_;
  }

  bool operator!=(const s21_iterator &other) const { return !(*this == other); }

  Key &key() const { return ptr_->key_value.first; }

 private:
  node<Key, T> *ptr_;
  Tree<Key, T> *tree_;
};

#endif  // CPP2_S21_CONTAINERS_S21_RB_ITERATOR_H_