#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <list>
#include <vector>

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class HashTable {

    template <typename K, typename V>
    friend void printElements(const HashTable<K, V>& ht);
    
    class HashNode {
    public:
        Key key;
        Value value;

        /* 从 key 构造节点，value使用默认构造 */
        explicit HashNode(const Key &k) : key(k), value() {}

        /* 从key和value构造节点 */
        HashNode(const Key &k, const Value &v) : key(k), value(v) {}

        /* 比较运算符重载，只按照key进行比较 */
        bool operator==(const HashNode &other) const
        {
            return key == other.key;
        }

        bool operator!=(const HashNode &other) const
        {
            return key != other.key;
        }

        bool operator<(const HashNode &other) const
        {
            return key < other.key;
        }

        bool operator>(const HashNode &other) const
        {
            return key > other.key;
        }

        bool operator==(const Key &key_) const
        {
            return key == key_;
        }

        void print() const {
            std::cout << key << " " << value << " ";
        }
    };

private:
    using Bucket = std::list<HashNode>;      /* 定义桶的类型为存储键的链表 */
    std::vector<Bucket> buckets;             /* 存储所有桶的动态数组 */
    Hash hash_function;                      /* 哈希函数对象 */
    size_t table_size;                       /* 哈希表的大小，即桶的数量 */
    size_t num_elements;                     /* 哈希表中元素的数量 */

    float max_load_factor = 0.75;            /* 默认的最大负载因子 */

    /* 计算键的哈希值，并将其映射到桶的索引 */
    size_t hash(const Key &key) const
    {
        return hash_function(key) % table_size;
    }

    /* 当元素数量超过最大负载因子定义的容量时，增加桶的数量并重新分配所有键 */
    void rehash(size_t new_size)
    {
        std::vector<Bucket> new_buckets(new_size);    /* 创建新的桶数组 */

        for (Bucket &bucket : buckets) {              /* 遍历旧桶 */
            for (HashNode &hash_node : bucket) {      /* 遍历桶中的每个键 */
                size_t new_index = hash_function(hash_node.key) % new_size;       /* 为键计算新的索引 */
                new_buckets[new_index].push_back(hash_node);                      /* 将键添加到新桶中 */
            }
        }  
        buckets = std::move(new_buckets);             /* 使用移动语义更新桶数组 */
        table_size = new_size;                        /* 更新哈希表大小 */
    }

public:
    /* 构造函数初始化哈希表 */
    HashTable(size_t size = 10, const Hash &hash_func = Hash())
        : buckets(size), hash_function(hash_func), table_size(size), num_elements(0) {}
    
    /* 插入键到哈希表中 */
    void insert(const Key &key, const Value &value)
    {
        if ((num_elements + 1) > max_load_factor * table_size) {        /* 检查是否需要rehash */
            /* 处理clear后再次插入元素时 table_size = 0 的情况 */
            if (table_size == 0) {
                table_size = 1;
            }
            rehash(table_size * 2);             /* rehash, 桶数量翻倍 */
        }

        size_t index = hash(key);                        /* 计算键的索引 */
        std::list<HashNode> &bucket = buckets[index];    /* 获取对应的桶 */
        /* 如果键不在桶中，则添加到桶中 */
        if (std::find(bucket.begin(), bucket.end(), key) == bucket.end()) {
            bucket.push_back(HashNode(key, value));
            ++num_elements;             /* 增加元素数量 */
        }
    }

    void insert_key(const Key &key)
    {
        insert(key, Value{});
    }

    /* 从哈希表中移除键 */
    void erase(const Key &key)
    {
        size_t index = hash(key);
        auto &bucket = buckets[index];
        auto it = std::find(bucket.begin(), bucket.end(), key);    /* 查找键 */
        if (it != bucket.end()) {
            bucket.erase(it);      /* 从桶中移除键 */
            --num_elements;
        }
    }

    /* 查找键是否存在于哈希表中 */
    Value* find(const Key &key)
    {
        size_t index = hash(key);
        auto &bucket = buckets[index];

        /* 返回键是否在桶中 */
        auto it = std::find(bucket.begin(), bucket.end(), key);
        if (it != bucket.end()) {
            return &it->value;
        }
        return nullptr;
    }

    size_t size() const
    {
        return num_elements;
    }

    void clear()
    {
        this->buckets.clear();
        this->num_elements = 0;
        this->table_size = 0;
    }
};

template <typename Key, typename Value>
void printElements(const HashTable<Key, Value, std::hash<Key>>& ht) {
    for (size_t i = 0; i < ht.buckets.size(); ++i) {
        for (const typename HashTable<Key, Value, std::hash<Key>>::HashNode &element : ht.buckets[i]) {
            element.print();
        }
    }

    std::cout << std::endl;
}

#endif


/* 输入：
    14
    insert 1 2
    insert 3 4
    insert 5 6
    size
    print
    find 1
    find 2
    erase 1
    find 1
    size
    print
    clear
    print
    size
*/

/* 输出：
    3
    1 2 3 4 5 6 
    2
    not exist
    not exist
    2
    3 4 5 6 
    empty
    0
*/
