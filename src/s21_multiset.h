#ifndef CPP2_S21_CONTAINERS_S21_MULTISET_H_
#define CPP2_S21_CONTAINERS_S21_MULTISET_H_

#include "s21_base_set.h"

namespace s21 {
template <typename Key>
class s21_multiset : public s21_base_set<Key, true> {
 public:
  using base_class = s21_base_set<Key, true>;
  using iterator = typename base_class::iterator;
  using value_type = typename base_class::value_type;
  using size_type = typename base_class::size_type;

  s21_multiset() : base_class() {}

  s21_multiset(std::initializer_list<value_type> const& items)
      : base_class(items) {}

  s21_multiset(const s21_multiset& other) : base_class(other) {}

  s21_multiset& operator=(const s21_multiset& other) {
    if (this != &other) {
      base_class::operator=(other);
    }
    return *this;
  }

  s21_multiset(s21_multiset&& other) noexcept : base_class(std::move(other)) {}

  s21_multiset& operator=(s21_multiset&& other) noexcept {
    if (this != &other) {
      base_class::operator=(std::move(other));
    }
    return *this;
  }

  ~s21_multiset() {}

  size_type count(const Key& key) {
    size_type counter = 0;
    for (iterator it = this->begin(); it != this->end(); ++it)
      counter += *it == key;
    return counter;
  }

  std::pair<iterator, iterator> equal_range(const Key& key) {
    return {this->lower_bound(key), this->upper_bound(key)};
  }

  iterator lower_bound(const Key& key) { return this->bound(key, false); }

  iterator upper_bound(const Key& key) { return this->bound(key, true); }

 private:
  iterator bound(const Key& key, bool upper) {
    for (auto it = this->begin(); it != this->end(); ++it)
      if (*it > key || (!upper && *it == key)) return it;
    return this->end();
  }
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MULTISET_H_
