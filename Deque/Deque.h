#ifndef __DEQUE_H__
#define __DEQUE_H__

#include <cstddef>
#include <stdexcept>
#include <iostream>

template <typename T>
class Deque {
    template <typename U> friend void printElements(const Deque<U>& v);
private:
    T *elements;        /* 一个循环一维数组 */
    size_t m_capacity;  /* 数组的总容量 */
    size_t m_size;      /* deque 中的元素数量 */
    size_t front_index; /* deque 中的前端索引 */
    size_t back_index;  /* deque 中的后端索引 */

public:
    Deque() : elements(nullptr), m_capacity(0), m_size(0), front_index(0), back_index(0) {}
    
    ~Deque()
    {
        clear();
        delete [] elements;
    }

    void push_front(const T &value)
    {
        /* 检查是否需要扩展数组容量 */
        if (m_size == m_capacity) {
            resize();
        }

        /* 计算新的前端索引 */
        front_index = (front_index - 1 + m_capacity) % m_capacity;

        /* 在新的前端位置插入元素 */
        elements[front_index] = value;

        /* 增加 deque 的元素数量 */
        ++m_size;
    }

    void push_back(const T &value)
    {
        /* 检查是否需要扩展数组容量 */
        if (m_size == m_capacity) {
            resize();
        }

        /* 在当前后端位置插入元素 */
        elements[back_index] = value;

        /* 计算新的后端索引 */
        back_index = (back_index + 1) % m_capacity;

        /* 增加deque的元素数量 */
        ++m_size;
    }

    void pop_front()
    {
        if (m_size == 0) {
            throw std::out_of_range("Deque is empty");
        }

        /* 删除元素不需要显式地删除，以后追加新元素会自动覆盖 */
        front_index = (front_index + 1) % m_capacity;
        --m_size;
    }

    void pop_back()
    {
        if (m_size == 0) {
            throw std::out_of_range("Deque is empty");
        }

        back_index = (back_index - 1 + m_capacity) % m_capacity;
        --m_size;
    }

    /* 随机访问元素 */
    T& operator[](int index)
    {
        if (index < 0 || index >= m_size) {
            throw std::out_of_range("Index out of range");
        }
        return elements[(front_index + index) % m_capacity];
    }

    size_t size()
    {
        return m_size;
    }

    void clear()
    {
        while (m_size > 0) {
            pop_front();
        }
    }

private:
    /* 扩展数组容量 */
    void resize()
    {
        /* 计算新的容量 */
        size_t new_capacity = (m_capacity == 0) ? 1 : m_capacity * 2;

        /* 创建新的数组 */
        T *new_elements = new T[new_capacity];

        /* 复制元素到新数组 */

        size_t index = front_index;
        for (size_t i = 0; i < m_size; ++i) {
            new_elements[i] = elements[index];
            index = (index + 1) % m_capacity;
        }

        delete [] elements;

        /* 更新成员变量 */
        elements = new_elements;
        m_capacity = new_capacity;
        front_index = 0;
        back_index = m_size;
    }
};

template <typename T>
void printElements(const Deque<T>& dq) {
    size_t index = dq.front_index;
    for (size_t i = 0; i < dq.m_size; ++i) {
        std::cout << dq.elements[index] << " ";
        index = (index + 1) % dq.m_capacity;
    }
    std::cout << std::endl;
}
#endif
