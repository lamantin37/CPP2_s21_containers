#pragma once

#include "s21_list.h"

namespace s21 {

    template<typename T>
    class queue {
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

        queue() {}
        queue(std::initializer_list<value_type> const &items) : data(items) {}
        queue(const queue<T>& other) : data(other.data) {}
        queue(queue<T>&& other) : data(std::move(other.data)) {}
        operator=(queue<T>&& other) {return *this = other;}
        ~queue() {data.clear();}

        ////////////////////////////////////////
        // queue Element access
        ////////////////////////////////////////

        const_reference front() const {return data.front();}
        const_reference back() const {return data.back();}

        ////////////////////////////////////////
        // queue Capacity
        ////////////////////////////////////////

        bool empty() const {return data.empty();}
        size_type size() const {return data.getSize();}

        ////////////////////////////////////////
        // queue Modifiers
        ////////////////////////////////////////

        void push(const_reference value) {data.push_front(value);}
        void pop() {data.pop_front();}
        void swap(queue& other) { data.swap(other.data); }
    };
}

