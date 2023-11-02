#ifndef S21_ARRAY_H_INCLUDED
#define S21_ARRAY_H_INCLUDED

#include <algorithm>
#include <initializer_list>
#include <limits>
#include <stdexcept>

namespace s21 {
template <typename T, int _size>
class array {
 public:
  ////////////////////////////////////////
  // Iterator
  ////////////////////////////////////////

  template <bool IsConst>
  class array_iterator {
   private:
    using _innerdata = std::conditional_t<IsConst, const T*, T*>;
    _innerdata _data_ptr;

   public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using pointer = std::conditional_t<IsConst, const T*, T*>;
    using reference = std::conditional_t<IsConst, const T&, T&>;
    using difference_type = std::ptrdiff_t;

    array_iterator() : _data_ptr(nullptr) {}
    array_iterator(_innerdata ptr) : _data_ptr(ptr) {}
    ~array_iterator() {}

    ////////////////////////////////////////
    // Increment and Decrement Operators
    ////////////////////////////////////////

    array_iterator& operator++() {
      ++_data_ptr;
      return *this;
    }

    array_iterator operator++(int) {
      array_iterator temp(*this);
      ++_data_ptr;
      return temp;
    }

    array_iterator& operator--() {
      --_data_ptr;
      return *this;
    }

    array_iterator operator--(int) {
      array_iterator temp(*this);
      --_data_ptr;
      return temp;
    }

    ////////////////////////////////////////
    // Addition and subtraction operators
    ////////////////////////////////////////

    array_iterator operator+(difference_type n) const {
      return array_iterator(_data_ptr + n);
    }

    array_iterator operator-(difference_type n) const {
      return array_iterator(_data_ptr - n);
    }

    array_iterator& operator+=(difference_type n) {
      _data_ptr += n;
      return *this;
    }

    array_iterator& operator-=(difference_type n) {
      _data_ptr -= n;
      return *this;
    }

    ////////////////////////////////////////
    // Dereference operator
    ////////////////////////////////////////

    reference operator*() const { return *_data_ptr; }
    pointer operator->() const { return _data_ptr; }

    ////////////////////////////////////////
    // Operator for accessing elements via index
    ////////////////////////////////////////

    reference operator[](difference_type n) const { return _data_ptr[n]; }

    bool operator==(const array_iterator& other) const {
      return _data_ptr == other._data_ptr;
    }

    bool operator!=(const array_iterator& other) const {
      return _data_ptr != other._data_ptr;
    }

    bool operator<(const array_iterator& other) const {
      return _data_ptr < other._data_ptr;
    }

    bool operator>(const array_iterator& other) const {
      return _data_ptr > other._data_ptr;
    }

    bool operator>=(const array_iterator& other) const {
      return _data_ptr >= other._data_ptr;
    }

    bool operator<=(const array_iterator& other) const {
      return _data_ptr <= other._data_ptr;
    }

    difference_type operator-(const array_iterator& other) const {
      return _data_ptr - other._data_ptr;
    }
  };

  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = array_iterator<false>;
  using const_iterator = array_iterator<true>;
  using size_type = size_t;

  ////////////////////////////////////////
  // Array Member functions
  ////////////////////////////////////////

  array() : _data(new value_type[_size]{}), size_(0), capacity_(_size) {}
  array(std::initializer_list<value_type> const& items)
      : _data(new value_type[items.size()]{}),
        size_(items.size()),
        capacity_(items.size()) {
    std::copy(items.begin(), items.end(), _data);
  }
  array(const array& other)
      : _data(new value_type[other.capacity_]{}),
        size_(other.size_),
        capacity_(other.capacity_) {
    std::copy(other.begin(), other.end(), _data);
  }
  array(array&& other) : _data(nullptr), size_(0), capacity_(0) { swap(other); }
  array& operator=(array&& a) {
    swap(a);
    return *this;
  }

  ~array() { delete[] _data, size_ = 0, capacity_ = 0; }

  ////////////////////////////////////////
  // Array Element access
  ////////////////////////////////////////

  reference at(size_type pos) {
    return (pos >= size_ ? (throw std::out_of_range("Index out of range"))
                         : _data[pos]);
  }
  reference operator[](size_type pos) { return at(pos); }
  const_reference front() const {
    return empty() ? (throw std::out_of_range("Array is empty")) : _data[0];
  }
  const_reference back() const {
    return empty() ? (throw std::out_of_range("Array is empty"))
                   : _data[size_ - 1];
  }
  // iterator data() {}

  ////////////////////////////////////////
  // Array Iterators
  ////////////////////////////////////////

  iterator begin() { return iterator(_data); }
  iterator end() { return iterator(_data + size_); }
  const_iterator begin() const { return const_iterator(_data); }
  const_iterator end() const { return const_iterator(_data + size_); }

  ////////////////////////////////////////
  // Array Capacity
  ////////////////////////////////////////

  bool empty() const { return size_ == 0; }
  size_type size() const { return size_; }
  size_type max_size() const { return capacity_; }

  ////////////////////////////////////////
  // Array Modifiers
  ////////////////////////////////////////

  void swap(array& other) {
    std::swap(_data, other._data);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }
  void fill(const_reference value) {
    for (size_type i = 0; i < size_; ++i) _data[i] = value;
  }

 private:
  value_type* _data;
  size_type size_;
  size_type capacity_;
};
}  // namespace s21

#endif  // S21_ARRAY_H_INCLUDED
