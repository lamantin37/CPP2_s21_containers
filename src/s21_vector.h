#ifndef CPP2_S21_CONTAINERS_S21_VECTOR_H_
#define CPP2_S21_CONTAINERS_S21_VECTOR_H_

#include <iostream>
#include <limits>
#include <memory>
#include <new>

namespace s21 {
template <typename T>
class s21_vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  // итераторы
  class iterator {
   public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;

    iterator(const iterator &other) : ptr_(other.ptr_) {}
    iterator(iterator &&other) noexcept : ptr_(other.ptr_) {
      other.ptr_ = nullptr;
    }
    iterator(T *ptr) : ptr_(ptr) {}
    iterator operator++() {
      ++ptr_;
      return *this;
    }
    iterator operator++(int) {
      iterator iter = *this;
      ++(*this);
      return iter;
    }
    iterator &operator--() {
      if (ptr_ != nullptr) {
        --ptr_;
      }
      return *this;
    }
    iterator operator--(int) {
      iterator tmp(*this);
      operator--();
      return tmp;
    }
    difference_type operator-(const iterator &other) const {
      return ptr_ - other.ptr_;
    }
    bool operator==(const iterator &other) const { return ptr_ == other.ptr_; }
    bool operator!=(const iterator &other) const { return !(*this == other); }
    T &operator*() { return *ptr_; }
    bool operator>(const iterator &other) const { return ptr_ > other.ptr_; }
    bool operator<(const iterator &other) const { return ptr_ < other.ptr_; }
    bool operator>=(const iterator &other) const { return ptr_ >= other.ptr_; }
    bool operator<=(const iterator &other) const { return ptr_ <= other.ptr_; }
    iterator operator+(int n) const { return iterator(ptr_ + n); }
    iterator operator-(int n) const { return iterator(ptr_ - n); }

   private:
    T *ptr_;
  };

  class const_iterator {
   public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T *;
    using reference = const T &;

    const_iterator(const const_iterator &other) : ptr_(other.ptr_) {}
    const_iterator(const_iterator &&other) noexcept : ptr_(other.ptr_) {
      other.ptr_ = nullptr;
    }
    const_iterator(const T *ptr) : ptr_(ptr) {}
    const_iterator operator++() {
      ++ptr_;
      return *this;
    }
    const_iterator operator++(int) {
      const_iterator iter = *this;
      ++(*this);
      return iter;
    }
    const_iterator &operator--() {
      if (ptr_ != nullptr) {
        --ptr_;
      }
      return *this;
    }
    const_iterator operator--(int) {
      const_iterator tmp(*this);
      operator--();
      return tmp;
    }
    difference_type operator-(const const_iterator &other) const {
      return ptr_ - other.ptr_;
    }
    bool operator==(const const_iterator &other) const {
      return ptr_ == other.ptr_;
    }
    bool operator!=(const const_iterator &other) const {
      return !(*this == other);
    }
    const T &operator*() const { return *ptr_; }
    bool operator>(const const_iterator &other) const {
      return ptr_ > other.ptr_;
    }
    bool operator<(const const_iterator &other) const {
      return ptr_ < other.ptr_;
    }
    bool operator>=(const const_iterator &other) const {
      return ptr_ >= other.ptr_;
    }
    bool operator<=(const const_iterator &other) const {
      return ptr_ <= other.ptr_;
    }
    const_iterator operator+(int n) const { return const_iterator(ptr_ + n); }
    const_iterator operator-(int n) const { return const_iterator(ptr_ - n); }

   private:
    const T *ptr_;
  };
  const_iterator cbegin() const { return const_iterator(array_); }
  const_iterator cend() const { return const_iterator(array_ + size_); }
  iterator begin() { return iterator(array_); }
  iterator end() { return iterator(array_ + size_); }
  iterator data() { return array_; }
  //	-----------------------------------------------------------
  //	конструкторы и деструкторы---------------------------------
  s21_vector(size_type s) : array_(new T[s]), size_(s), capacity_(s) {
    // std::cout << "Constructor" << std::endl;
  }
  s21_vector() : array_(nullptr), size_(0), capacity_(0){};
  s21_vector(std::initializer_list<value_type> const &items)
      : array_(new T[items.size()]),
        size_(items.size()),
        capacity_(items.size()) {
    std::copy(items.begin(), items.end(), array_);
  }
  s21_vector(const s21_vector &v)
      : array_(new T[v.capacity_]), size_(v.size_), capacity_(v.capacity_) {
    std::copy(v.array_, v.array_ + v.size_, array_);
  }

  s21_vector &operator=(const s21_vector &other) {
    if (this != &other) {
      delete[] array_;

      size_ = other.size_;
      capacity_ = other.capacity_;
      array_ = new T[other.capacity_];
      std::copy(other.array_, other.array_ + other.size_, array_);
    }
    return *this;
  }
  s21_vector(s21_vector &&v)
      : array_(v.array_), size_(v.size_), capacity_(v.capacity_) {
    v.array_ = nullptr;
    v.size_ = 0;
    v.capacity_ = 0;
  }

  s21_vector &operator=(s21_vector &&other) {
    if (this != &other) {
      delete[] array_;

      size_ = other.size_;
      capacity_ = other.capacity_;
      array_ = other.array_;

      other.array_ = nullptr;
      other.size_ = 0;
      other.capacity_ = 0;
    }
    return *this;
  }

  ~s21_vector() {
    for (size_t i = 0; i < size_; ++i) {
      array_[i].~T();
    }
    delete[] reinterpret_cast<int8_t *>(array_);
    // std::cout << "Destructor" << std::endl;
  }
  //	-----------------------------------------------------------
  //	доступ к элементам класса
  reference at(size_type pos) {
    if (pos >= size_) {
      throw std::out_of_range("Index is out of range.");
    }
    return array_[pos];
  }
  const_reference at(size_type pos) const {
    if (pos >= size_) {
      throw std::out_of_range("Index is out of range.");
    }
    return array_[pos];
  }
  reference operator[](size_t pos) { return array_[pos]; }
  const_reference front() { return array_[0]; }
  const_reference back() { return array_[size_ - 1]; }
  //	-----------------------------------------------------------
  //	итерирование по элементам класса

  //	-----------------------------------------------------------
  //	методы для доступа к информации о наполнении контейнера
  void reserve(size_type new_cap) {
    if (new_cap <= capacity_) return;
    T *new_array = reinterpret_cast<T *>(new int8_t[new_cap * sizeof(T)]);
    try {
      std::move(array_, array_ + size_, new_array);
      delete[] reinterpret_cast<int8_t *>(array_);
    } catch (...) {
      delete[] reinterpret_cast<int8_t *>(new_array);
      throw;
    }
    array_ = new_array;
    capacity_ = new_cap;
  }
  size_type max_size() {
    return std::numeric_limits<size_t>::max() / sizeof(size_t);
  }
  size_type capacity() { return capacity_; };
  size_type size() { return size_; };
  void resize(size_t new_size) {
    if (new_size > capacity_) {
      throw std::length_error("New size exceeds capacity in resize");
    } else if (new_size < size_) {
      for (size_t i = new_size; i < size_; i++) {
        array_[i].~T();
      }
    }
    size_ = new_size;
  }
  void shrink_to_fit() {
    if (capacity_ > size_) {
      T *new_array = reinterpret_cast<T *>(new int8_t[size_ * sizeof(T)]);
      try {
        std::move(array_, array_ + size_, new_array);
        delete[] reinterpret_cast<int8_t *>(array_);
      } catch (...) {
        delete[] reinterpret_cast<int8_t *>(new_array);
        throw;
      }
      array_ = new_array;
      capacity_ = size_;
    }
  }
  bool empty() { return (size_ == 0); }
  //	-----------------------------------------------------------
  //	 методы для изменения контейнера
  void push_back(const_reference value) {
    if (size_ >= capacity_) {
      reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    array_[size_] = value;
    ++size_;
  }
  void pop_back() {
    if (size_ > 0) {
      --size_;
      (array_ + size_)->~T();
    }
  }
  void clear() {
    for (size_t i = 0; i < size_; ++i) {
      (array_ + i)->~T();
    }
    size_ = 0;
  }
  iterator erase(iterator pos) {
    if (pos < begin() || pos >= end()) {
      throw std::out_of_range("Iterator is out of range.");
    }
    std::move(pos + 1, end(), pos);
    size_--;
    (array_ + size_)->~T();
    return pos;
  }
  iterator erase(iterator first, iterator last) {
    if (first >= begin() && first <= end() && last >= begin() &&
        last <= end() && last >= first) {
      iterator it = std::move(last, end(), first);
      resize(size() - (last - first));
      return it;
    }
    throw std::out_of_range("Invalid iterator range for erase!");
  }
  void swap(s21_vector &other) {
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(array_, other.array_);
  }
  iterator insert(iterator pos, const_reference value) {
    if (pos < begin() || pos > end()) {
      throw std::out_of_range("Iterator is out of range.");
    }
    size_t index = pos - begin();
    if (size_ >= capacity_) {
      reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    std::move_backward(begin() + index, end(), end() + 1);
    array_[index] = value;
    size_++;
    return begin() + index;
  }

  //	-----------------------------------------------------------
  T *getArray() { return array_; };
  template <class... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    if (pos < cbegin() || pos > cend()) {
      throw std::out_of_range("Iterator is out of range.");
    }
    size_t index = pos - cbegin();
    if (size_ >= capacity_) {
      reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    std::move_backward(begin() + index, end(), end() + 1);
    new (array_ + index) T(std::forward<Args>(args)...);
    size_++;
    return begin() + index;
  }
  template <class... Args>
  void emplace_back(Args &&...args) {
    insert_many(cend(), std::forward<Args>(args)...);
  }

 private:
  T *array_;
  size_t size_;
  size_t capacity_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_VECTOR_H_