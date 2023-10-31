#ifndef CPP2_S21_CONTAINERS_S21_SET_H_
#define CPP2_S21_CONTAINERS_S21_SET_H_

#include "s21_base_set.h"

namespace s21 {
template <typename Key>
class s21_set : public s21_base_set<Key, false> {
 public:
  using base_class = s21_base_set<Key, false>;
  using iterator = typename base_class::iterator;

  s21_set() : base_class() {}

  s21_set(std::initializer_list<Key> const& items) : base_class(items) {}

  s21_set(const s21_set& other) : base_class(other) {}

  s21_set& operator=(const s21_set& other) {
    if (this != &other) {
      base_class::operator=(other);
    }
    return *this;
  }

  s21_set(s21_set&& other) noexcept : base_class(std::move(other)) {}

  s21_set& operator=(s21_set&& other) {
    if (this != &other) {
      base_class::operator=(std::move(other));
    }
    return *this;
  }

  ~s21_set() {}
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_SET_H_
