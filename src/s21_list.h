#ifndef CPP2_S21_CONTAINERS_S21_LIST_H_
#define CPP2_S21_CONTAINERS_S21_LIST_H_

#include <cstddef>
#include <iostream>
#include <limits>
#include <stdexcept>

#include "s21_multiset.h"
#include "s21_set.h"

namespace s21 {

template <typename T>
struct node;

template <typename T>
struct node {
  T value;
  node *prev;
  node *next;
};

template <typename T>
class list {
 public:
  class ListIterator {
   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using pointer = T *;
    using reference = T &;
    using difference_type = std::ptrdiff_t;

    ListIterator(node<T> *ptr) : current(ptr) {}

    reference operator*() const { return current->value; }

    pointer operator->() const { return &(current->value); }

    ListIterator &operator++() {
      current = current->next;
      return *this;
    }

    ListIterator &operator--() {
      current = current->prev;
      return *this;
    }

    bool operator==(const ListIterator &other) const {
      return current == other.current;
    }

    bool operator!=(const ListIterator &other) const {
      return !(*this == other);
    }

   private:
    node<T> *current;
    friend class list<T>;
  };

  class ListConstIterator {
   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using pointer = const T *;
    using reference = const T &;
    using difference_type = std::ptrdiff_t;

    ListConstIterator(const node<T> *ptr) : current(ptr) {}

    reference operator*() const { return current->value; }

    pointer operator->() const { return &(current->value); }

    ListConstIterator &operator++() {
      current = current->next;
      return *this;
    }

    ListConstIterator &operator--() {
      current = current->prev;
      return *this;
    }

    bool operator==(const ListConstIterator &other) const {
      return current == other.current;
    }

    bool operator!=(const ListConstIterator &other) const {
      return !(*this == other);
    }

   private:
    const node<T> *current;
    friend class list<T>;
  };

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = size_t;

  // List Member functions ==================================
  list() {
    data.value = T{};
    data.prev = nullptr;
    data.next = nullptr;
  };

  list(size_type n) {
    data.prev = nullptr;
    data.next = nullptr;
    for (size_type i = 0; i < n; ++i) {
      push_back(T());
    }
  };

  list(std::initializer_list<T> const &items) {
    data.prev = nullptr;
    data.next = nullptr;
    for (const_reference item : items) {
      push_back(item);
    }
  };

  list(const list &l) {
    data.prev = nullptr;
    data.next = nullptr;
    for (const_reference item : l) {
      push_back(item);
    }
  };

  list(list &&l) {
    data.prev = nullptr;
    data.next = nullptr;
    swap(l);
  };

  list &operator=(list &&l) {
    if (this != &l) {
      swap(l);
      l.clear();
    }
    return *this;
  }

  ~list() { clear(); };

  // ========================================================

  // List Element access =====================================
  const_reference front() const {
    if (data.next == nullptr) {
      throw std::runtime_error("The list is empty, front() cannot be called.");
    }
    return data.next->value;
  };

  const_reference back() const {
    if (data.next == nullptr) {
      throw std::runtime_error("The list is empty, back() cannot be called.");
    }
    node<T> *lastNode = data.next;
    while (lastNode->next != nullptr) {
      lastNode = lastNode->next;
    }
    return lastNode->value;
  };

  // ========================================================

  // List Iterators  =========================================
  iterator begin() noexcept { return iterator(data.next); };
  iterator end() noexcept { return iterator(nullptr); };
  const_iterator begin() const noexcept { return const_iterator(data.next); };
  const_iterator end() const noexcept { return const_iterator(nullptr); };

  // ========================================================

  // Map Capacity ===========================================
  bool empty() const noexcept { return data.next == nullptr; };

  size_type size() const noexcept {
    size_type count = 0;
    for (auto it = begin(); it != end(); ++it) {
      ++count;
    }
    return count;
  }

  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max();
  };

  // ========================================================

  //  Map Modifiers =========================================
  void clear() noexcept {
    while (!empty()) {
      pop_back();
    }
  };

  iterator insert(iterator pos, const_reference value) noexcept {
    node<T> *newNode = new node<T>{value, nullptr, nullptr};
    if (pos.current == nullptr) {
      if (data.next == nullptr) {
        data.next = newNode;
        newNode->prev = &data;
      } else {
        node<T> *lastNode = data.next;
        while (lastNode->next != nullptr) {
          lastNode = lastNode->next;
        }
        lastNode->next = newNode;
        newNode->prev = lastNode;
      }
    } else {
      newNode->next = pos.current;
      newNode->prev = pos.current->prev;
      pos.current->prev->next = newNode;
      pos.current->prev = newNode;
    }
    return iterator(newNode);
  };

  iterator erase(iterator pos) noexcept {
    if (pos == begin()) {
      pop_front();
    } else if (pos == end()) {
      pop_back();
    } else {
      pos.current->prev->next = pos.current->next;
      pos.current->next->prev = pos.current->prev;
      node<T> *tmp = pos.current->next;
      delete pos.current;
      pos.current = tmp;
    }
    return pos;
  }

  void erase(iterator *pos) noexcept { *pos = erase(*pos); }

  void push_back(const_reference value) noexcept { insert(end(), value); };

  void push_front(const_reference value) noexcept { insert(begin(), value); };

  void pop_back() noexcept {
    if (data.next == nullptr) {
      return;
    }
    node<T> *lastNode = data.next;
    while (lastNode->next != nullptr) {
      lastNode = lastNode->next;
    }
    lastNode->prev->next = nullptr;
    delete lastNode;
  };

  void pop_front() noexcept {
    if (data.next == nullptr) {
      return;
    }
    node<T> *firstNode = data.next;
    data.next = firstNode->next;
    data.next->prev = &data;
    delete firstNode;
  };

  void swap(list &other) noexcept {
    std::swap(data.next, other.data.next);
    std::swap(data.prev, other.data.prev);
    if (data.next != nullptr) {
      data.next->prev = &data;
    }
    if (other.data.next != nullptr) {
      other.data.next->prev = &(other.data);
    }
  };

  void merge(list<T> &other) noexcept {
    sort();
    other.sort();
    if (&other == this) {
      return;
    }
    for (auto it = other.begin(); it != other.end(); ++it) {
      push_back(*it);
    }
    other.clear();
    unique();
  }

  void splice(const_iterator pos, list &other) noexcept {
    if (&other == this || other.empty()) {
      return;
    }

    auto connect_nodes = [](node<T> *prev_node, node<T> *first_node,
                            node<T> *last_node) {
      prev_node->next = first_node;
      first_node->prev = prev_node;
      last_node->next = nullptr;
    };

    auto thisCurrent = pos.current;
    auto otherFirst = other.data.next;
    auto otherLast = otherFirst;

    if (!thisCurrent) {
      while (otherLast->next) {
        otherLast = otherLast->next;
      }
    }

    if (thisCurrent == data.next) {
      data.next = otherFirst;
      otherFirst->prev = &data;
    } else {
      connect_nodes(thisCurrent->prev, otherFirst, otherLast);
    }

    if (thisCurrent) {
      thisCurrent->prev = otherLast;
    }

    other.data.next = nullptr;
  }

  void reverse() noexcept {
    list<T> temp;
    for (const auto &value : *this) {
      temp.push_front(value);
    }
    swap(temp);
  }

  void unique() noexcept {
    s21_set<T> tmp_set_list;
    for (auto it = begin(); it != end(); ++it) {
      tmp_set_list.insert(*it);
    }
    clear();
    for (auto it = tmp_set_list.begin(); it != tmp_set_list.end(); it++) {
      push_back(it->first);
    }
  };

  void sort() noexcept {
    s21_multiset<T> tmp_set_list;
    for (auto it = begin(); it != end(); ++it) {
      tmp_set_list.insert(*it);
    }
    clear();
    for (auto it = tmp_set_list.begin(); it != tmp_set_list.end(); it++) {
      push_back(it->first);
    }
  };

  // ========================================================

  // Insert Many  ===========================================
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    iterator it = insert(pos, std::forward<Args>(args)...);
    return it;
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    ((void)push_back(std::forward<Args>(args)), ...);
  }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    ListIterator it = begin();
    while (it != end()) {
      it = insert(it, std::forward<Args>(args)...);
    }
  }

 private:
  struct node<T> data;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_LIST_H_