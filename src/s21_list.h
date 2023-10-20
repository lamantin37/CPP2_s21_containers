#ifndef S21_LIST_H_INCLUDED
#define S21_LIST_H_INCLUDED

#include <iostream>
#include <algorithm>
#include <functional>

namespace s21 {
template <typename T>
class list {
private:
    struct Node {
        T value;
        Node* prev = nullptr;
        Node* next = nullptr;
        double relative_position = 0;
    };
    Node* tail = nullptr;
    Node* head = nullptr;

public:
    template <bool IsConst = false>
    class list_iterator {
    private:
        using Node = std::conditional_t<IsConst, const Node, Node>;

    protected:
        Node* current;
        friend class list<T>;

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using pointer = std::conditional_t<IsConst, const T*, T*>;
        using reference = std::conditional_t<IsConst, const T&, T&>;
        using difference_type = std::ptrdiff_t;

        list_iterator() : current(nullptr) {}
        list_iterator(Node* ptr) : current(ptr) {}
        ~list_iterator() {};

        ////////////////////////////////////////
        // Increment and Decrement Operators
        ////////////////////////////////////////

        list_iterator& operator++() {
            current = current->next;
            return *this;
        }

        list_iterator operator++(int) {
            list_iterator temp = *this;
            ++(*this);
            return temp;
        }

        list_iterator& operator--() {
            current = current->prev;
            return *this;
        }

        list_iterator operator--(int) {
            list_iterator temp = *this;
            --(*this);
            return temp;
        }

        ////////////////////////////////////////
        // Addition and subtraction operators
        ////////////////////////////////////////

        list_iterator operator+(difference_type n) const {
            list_iterator temp = *this;
            temp += n;
            return temp;
        }

        list_iterator operator-(difference_type n) const {
            list_iterator temp = *this;
            temp -= n;
            return temp;
        }

        list_iterator& operator+=(difference_type n) {
            for (difference_type i = 0; i < n; ++i) {
                ++(*this);
            }
            return *this;
        }

        list_iterator& operator-=(difference_type n) {
            for (difference_type i = 0; i < n; ++i) {
                --(*this);
            }
            return *this;
        }

        ////////////////////////////////////////
        // Dereference operator
        ////////////////////////////////////////

        reference operator*() const { return current->value; }
        pointer operator->() const { return &(current->value); }

        ////////////////////////////////////////
        // Operator for accessing elements via index
        ////////////////////////////////////////

        reference operator[](difference_type n) const {
            list_iterator temp = *this;
            temp += n;
            return *temp;
        }

        ////////////////////////////////////////
        // Comparison operator
        ////////////////////////////////////////

        bool operator==(const list_iterator& other) const { return current == other.current; }
        bool operator!=(const list_iterator& other) const { return current != other.current; }
        bool operator<(const list_iterator& other) const {return (current->relative_position) < (other.current->relative_position);}
        bool operator>(const list_iterator& other) const {return !(*this < other) && (*this != other);}
        bool operator>=(const list_iterator& other) const {return (*this > other) || (*this == other);}
        bool operator<=(const list_iterator& other) const {return (*this < other) || (*this == other);}
        difference_type operator-(const list_iterator& other) const {return (other.current->relative_position - current->relative_position + 1) * (*this <= other ? 1: -1);}
    };

    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using iterator = list_iterator<false>;
    using const_iterator = list_iterator<true>;
    using size_type = size_t;

    ////////////////////////////////////////
    // CONSTRUCTORS
    ////////////////////////////////////////

    #define ZERO_BLOCK head = tail = new Node {0, nullptr, nullptr, 0.f};
    list() { ZERO_BLOCK }

    list(size_type n) {
        ZERO_BLOCK
        for (size_type i = 0; i < n; ++i) push_back(T{});
    }

    list(std::initializer_list<value_type> const &items): head(new Node {0, nullptr, nullptr, 0.f}), tail(head) {
        ZERO_BLOCK
        for (const auto &item : items) push_back(item);
    }
    #undef ZERO_BLOCK

    list(const list &l) { list tmp(l.begin(), l.end()); swap(tmp); }
    list(list &&l) noexcept { swap(l); }
    operator=(list &&l) noexcept { swap(l); return *this; }
    ~list() {clear();}

    ////////////////////////////////////////
    // List Element access
    ////////////////////////////////////////

    const_reference front() noexcept { return head->value; }
    const_reference back() noexcept { return tail->value; }

    ////////////////////////////////////////
    // List Iterators
    ////////////////////////////////////////

    iterator begin() noexcept { return iterator(head); };
    iterator end() noexcept { return iterator(tail); }

    ////////////////////////////////////////
    // List Capacity
    ////////////////////////////////////////

    bool empty() { return size() == 0; }
    size_type size() { return std::distance(begin(), end()); }
    size_type max_size() { return std::numeric_limits<size_type>::max(); }

    ////////////////////////////////////////
    // List Modifiers
    ////////////////////////////////////////

    #define try_catch_block(func_name) try { func_name(); } catch (const std::exception &exception) { std::cerr << "Exception: " << exception.what() << std::endl; throw;}
    void push_back(const_reference value) { try_catch_block([&]() { insert(end(), value); }); }
    void pop_back() { try_catch_block([&]() { erase(end()); }); }
    void push_front(const_reference value) { try_catch_block([&]() { insert(begin(), value); }); }
    void pop_front() { try_catch_block([&]() { erase(begin()); }); }
    #undef try_catch_block

    void sort() noexcept { std::sort(begin(), end()); }
    void reverse() noexcept { std::reverse(begin(), end()); }
    void unique() noexcept { std::unique(begin(), end()); }

    iterator insert(iterator pos, const_reference value) {
        Node* tmp = new Node{value, pos.current->prev, pos.current, pos.current->prev ? (pos != end() ? (pos.current->prev->relative_position + pos.current->relative_position) / 2.f : pos.current->prev->relative_position + 1.f) : pos.current->relative_position - 1.f};
        head = (pos.current = pos.current->prev = pos.current->prev ? pos.current->prev->next = tmp : tmp)->prev ? head : tmp;
        return iterator(tmp);
    }

    void erase(iterator it) {
        it.current->prev ? (it.current->next ? (it.current->prev->next = it.current->next, it.current->next->prev = it.current->prev): (tail = it.current->prev, it.current->prev->next = nullptr)): (head = it.current->next, it.current->next->prev = nullptr);
        delete[] it.current;
    }

    void swap(list& other) { std::swap(head, other.head), std::swap(tail, other.tail); }
    void merge(list& other) { splice(end(), other); other.clear(); }
    void splice(iterator pos, list& other) { for (; !other.empty(); other.pop_front()) insert(pos, *other.begin()); }
    void clear() { std::for_each(begin(), end(), [&](const T& value) { erase(iterator(head)); }); }
};
}; // namespace s21

#endif // S21_LIST_H_INCLUDED
