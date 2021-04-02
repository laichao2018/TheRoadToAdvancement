//
// Created by laichao on 2021/3/29.
//
// 哈希函数

#include <vector>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////
//                                            HASH_SET                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////////
// 设计哈希映射
// 采用单链表法
class MyHashSet {
private:
    // 在类中定义单链表结构
    struct Node {
        int val;
        Node *next;

        Node(int _v) : val(_v), next(nullptr) {}
    };

public:
    /** Initialize your data structure here. */
    MyHashSet() {
        bucket = vector<Node *>(hashRange); // 初始化bucket，一定要加初始大小，否则会面的函数中会访问出错
    }

    /** value will always be non-negative. */
    void add(int key) {
        int index = hash(key);
        if (bucket[index] == nullptr) {
            bucket[index] = new Node(key);  // 没有数据，新增，返回
            return;
        }
        Node *tmp = bucket[index];
        if (tmp->val == key) return;
        while (tmp->next != nullptr) {
            if (tmp->next->val == key) return;
            tmp = tmp->next;
        }
        tmp->next = new Node(key);
    }

    /** Removes the mapping of the specified value key if this map contains a mapping for the key */
    void remove(int key) {
        int index = hash(key);
        if (bucket[index] == nullptr) return;
        Node *tmp = bucket[index];
        if (tmp->val == key) {
            bucket[index] = tmp->next;
            delete tmp;
        } else {
            Node *next = tmp->next;
            while (next != nullptr) {
                if (next->val == key) {
                    tmp->next = next->next;
                    delete next;
                    return;
                }
                tmp = next;
                next = next->next;
            }
        }
    }

    /** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
    bool contains(int key) {
        int index = hash(key);
        Node *tmp = bucket[index];
        while (tmp != nullptr) {
            if (tmp->val == key) return true;
            tmp = tmp->next;
        }
        return false;
    }

private:
    int hashRange = 31;     // 一般为质数，常见的还有769等数字
    vector<Node *> bucket;

    int hash(int key) {
        return (key % hashRange);
    }
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */

///////////////////////////////////////////////////////////////////////////////////////////////////////
//                                            HASH_MAP                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////////
// 设计哈希映射
// 采用单链表法
class MyHashMap {
private:
    struct Node {
        int key;    // 链表中包含了 “键-值”
        int value;
        Node *next;

        Node(int _k, int _v) : key(_k), value(_v), next(nullptr) {}
    };

public:
    /** Initialize your data structure here. */
    MyHashMap() {
        bucket.resize(hashRange);
    }

    /** value will always be non-negative. */
    void put(int key, int value) {
        int index = hash(key);
        if (bucket[index] == nullptr) { // 没有数据，插入
            bucket[index] = new Node(key, value);
            return;
        }
        Node *tmp = bucket[index];
        if (tmp->key == key) {  // 修改值
            bucket[index]->value = value;
            return;
        }
        while (tmp->next != nullptr) {
            if (tmp->next->key == key) {
                tmp->next->value = value;
                return;
            }
            tmp = tmp->next;
        }
        tmp->next = new Node(key, value);
    }

    /** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
    int get(int key) {
        int index = hash(key);
        if (bucket[index] == nullptr) { // 没有找到该数据
            return -1;
        }
        Node *tmp = bucket[index];
        if (tmp->key == key) return tmp->value;
        while (tmp != nullptr) {
            if (tmp->key == key) return tmp->value;
            tmp = tmp->next;
        }
        return -1;  // 没有找到数据
    }

    /** Removes the mapping of the specified value key if this map contains a mapping for the key */
    void remove(int key) {
        int index = hash(key);
        if (bucket[index] == nullptr) return;
        Node *tmp = bucket[index];
        if (tmp->key == key) {
            bucket[index] = tmp->next;
            delete tmp;
            return;
        }
        Node *next = tmp->next;
        while (next != nullptr) {
            if (next->key == key) {
                tmp->next = next->next;
                delete next;
                return;
            }
            tmp = next;
            next = next->next;
        }
    }

private:
    int hashRange = 31;
    vector<Node *> bucket;

    int hash(int key) {
        return key % hashRange;
    }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */