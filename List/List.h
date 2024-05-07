#ifndef __LIST_H__
#define __LIST_H__

#include <cstddef>
#include <iostream>
#include <ostream>
#include <stdexcept>
template <typename T>
class List {
    template <typename L> friend void printElements(const List<L> &l);
private:
    /* 定义节点结构 */
    struct Node {
        T data;       /* 数据 */
        Node *prev;   /* 指向前一个节点的指针 */
        Node *next;   /* 指向下一个节点的指针 */

        /* 构造函数 */
        Node(const T &value, Node *prev_node = nullptr, Node *next_node = nullptr)
            : data(value), prev(prev_node), next(next_node) {}
    };

public:
    /* 构造函数 */
    List() : head(nullptr), tail(nullptr), m_size(0) {}

    ~List()
    {
        clear();
    }

    void clear()
    {
        while (head) {
            /* 从头节点开始，依次删除节点 */
            Node *temp = head;
            head = head->next;
            delete temp;
        }

        tail = nullptr;
        m_size = 0;
    }

    void push_back(const T &value)
    {
        /* 创建新的节点 */
        Node *new_node = new Node(value, tail, nullptr);
        if (tail) {
            /* 如果链表非空，将尾节点的 next 指针指向新节点 */
            tail->next = new_node;
        } else {
            /* 如果链表为空，新节点同时也是头节点 */
            head = new_node;
        }

        /* 更新尾节点指针和链表大小 */
        tail = new_node;
        ++m_size;
    }

    void push_front(const T &value)
    {
        Node *new_node = new Node(value, nullptr, head);
        if (head) {
            /* 如果链表非空，将头节点的 prev 指针指向新节点 */
            head->prev = new_node;
        } else {
            tail = new_node;
        }

        head = new_node;
        ++m_size;
    }

    size_t size()
    {
        return m_size;
    }

    void pop_back()
    {
        if (m_size > 0) {
            /* 获取尾节点的前一个节点 */
            Node *new_tail = tail->prev;

            /* 删除尾节点 */
            delete tail;

            /* 更新尾节点指针和链表大小 */
            tail = new_tail;
            if (tail) {
                tail->next = nullptr;
            } else {
                head = nullptr;        /* 如果链表为空，头节点也置为空 */
            }

            --m_size;
        }
    }

    void pop_front()
    {
        if (m_size > 0) {
            Node *new_head = head->next;

            delete head;
            head = new_head;

            if (head) {
                head->prev = nullptr;
            } else {
                tail = nullptr;
            }

            --m_size;
        }
    }

    void remove(const T &value)
    {
        Node *node = head;
        while (node != nullptr && node->data != value) {
            node = node->next;
        }

        if (node == nullptr) {
            /* 没有找到 */
            return;
        }

        if (node != head && node != tail) {
            /* 既不是头节点也不是尾节点 */
            node->prev->next = node->next;
            node->next->prev = node->prev;
        } else if (node == head && node == tail) {
            /* 既是头节点，也是尾节点 */
            head = nullptr;
            node = nullptr;
        } else if (node == head) {
            /* 是头节点 */
            head = node->next;
            head->prev = nullptr;
        } else {
            /* 是尾节点 */
            tail = node->prev;
            tail->next = nullptr;
        }

        --m_size;
        delete node;
        node = nullptr;
    }

    bool empty()
    {
        return m_size == 0;
    }

    Node* begin()
    {
        return head;
    }

    Node *end()
    {
        return nullptr;
    }

    const Node* begin() const {
        return head;
    }

    const Node* end() const {
        return nullptr;
    }

private:
    Node *head;      /* 头节点指针 */
    Node *tail;      /* 尾节点指针 */
    size_t m_size;   /* 链表中节点的数量 */
};


template <typename T>
void printElements(const List<T> &l)
{
    for (typename List<T>::Node *curr = l.head; curr != nullptr; curr = curr->next) {
        std::cout << curr->data << " ";
    }
    std::cout << std::endl;
}

#endif
