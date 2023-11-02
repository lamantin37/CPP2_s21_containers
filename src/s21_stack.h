#include "s21_list.h"

namespace s21 {
template <typename T>
class stack {
 private:
  list<T> data;

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  ////////////////////////////////////////
  // CONSTRUCTORS
  ////////////////////////////////////////

  stack() {}
  stack(std::initializer_list<T> values) : data(values) {}
  stack(const stack<T>& other) : data(other.data) {}
  stack(stack<T>&& other) : data(std::move(other.data)) {}
  stack& operator=(stack&& other) {
    data = std::move(other.data);
    return *this;
  }
  ~stack() { data.clear(); }

  ////////////////////////////////////////
  // List Element access
  ////////////////////////////////////////

  const_reference top() const { return data.back(); }

  ////////////////////////////////////////
  // List Capacity
  ////////////////////////////////////////

  bool empty() const { return data.empty(); }
  size_type size() const { return data.size(); }

  ////////////////////////////////////////
  // List Modifiers
  ////////////////////////////////////////

  void push(const T& value) { data.push_back(value); }
  void pop() { data.pop_back(); }
  void swap(stack& other) { data.swap(other.data); }
};
}  // namespace s21
