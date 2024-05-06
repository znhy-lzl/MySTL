#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <stdexcept>


template <typename T>
class Vector {
    template <typename U> friend void printElements(const Vector<U> &v);

private:
    T *m_elements;      /* 指向动态数组的指针 */
    size_t m_capacity;  /* 数组的容量 */
    size_t m_size;      /* 数组中元素的个数 */

public:
    Vector() : m_elements(nullptr), m_capacity(0), m_size(0) {}

    ~Vector() {
        delete[] m_elements;
    }

    /* 拷贝构造函数 */
    Vector(const Vector &other) : m_capacity(other.m_capacity), m_size(other.m_size) {
        m_elements = new T[m_capacity];
        std::copy(other.m_elements, other.m_elements + m_size, m_elements);
    }

    /* 拷贝赋值操作符 */
    Vector& operator=(const Vector &other) {
        if (this != &other) {
            delete[] m_elements;
            m_capacity = other.m_capacity;
            m_size = other.m_size;
            m_elements = new T[m_capacity];
            std::copy(other.m_elements, other.m_elements + m_size, m_elements);
        }

        return *this;
    }

    void push_back(const T &value) {
        if (m_size == m_capacity) {
            reserve(m_capacity == 0 ? 1 : m_capacity * 2);   /* 考虑边界为0的情况 */
        }
        m_elements[m_size++] = value;
    }

    size_t size() const {
        return m_size;
    }

    size_t capacity() const {
        return m_capacity;
    }

    /* 下标操作符 */
    T& operator[](size_t index) {
        if (index >= m_size) {
            throw std::out_of_range("Index out of range");
        }
        return m_elements[index];
    }

    const T& operator[](size_t index) const {
        if (index >= m_size) {
            throw std::out_of_range("Index out of range");
        }
        return m_elements[index];
    }

    void insert(size_t index, const T& value) {
        if (index > m_size) {
            throw std::out_of_range("Index out of range");
        }

        if (m_size == m_capacity) {
            reserve(m_capacity == 0 ? 1 : m_capacity * 2);
        }

        for (size_t i = m_size; i > index; --i) {
            m_elements[i] = m_elements[i - 1];
        }

        m_elements[index] = value;
        ++m_size;
    }

    void pop_back() {
        if (m_size > 0) {
            --m_size;
        }
    }

    void clear() {
        m_size = 0;
    }

    T* begin() {
        return m_elements;
    }

    const T* begin() const {
        return m_elements;
    }

    T* end() {
        return m_elements + m_size;
    }

    const T* end() const {
        return m_elements + m_size;
    }

private:
    /* 扩展数组容量 */
    void reserve(size_t new_capacity) {
        if (new_capacity > m_capacity) {
            T *new_elements = new T[new_capacity];
            std::copy(m_elements, m_elements + m_size, new_elements);
            delete[] m_elements;
            m_elements = new_elements;
            m_capacity = new_capacity;
        }
    }

};

template <typename T>
void printElements(const Vector<T>& v) {
    for (size_t i = 0; i < v.m_size; ++i) {
        std::cout << v.m_elements[i] << " ";
    }
    std::cout << std::endl;
}

#endif
