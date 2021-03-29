//
// Created by laichao on 2021/3/29.
//
// 哈希函数

#include <list>
#include <vector>

// 设计哈希集合
class MyHashSet {
public:
    /** Initialize your data structure here. */
    MyHashSet() : data(base) {}

    void add(int key) {
        int index = hash(key);
        for (auto it = data[index].begin(); it != data[index].end(); it++) {
            if (*it == key) return;
        }
        data[index].push_back(key);
    }

    void remove(int key) {
        int index = hash(key);
        for (auto it = data[index].begin(); it != data[index].end(); it++) {
            if (*it == key) {
                data[index].erase(it);
                return;
            }
        }
    }

    /** Returns true if this set contains the specified element */
    bool contains(int key) {
        int index = hash(key);
        for (auto it = data[index].begin(); it != data[index].end(); it++) {
            if (*it == key) return true;
        }
        return false;
    }

private:
    std::vector<std::list<int>> data;
    static const int base = 769;    // 为了尽可能避免冲突，应当将base取为一个质数

    static int hash(int key) {
        return key % base;
    }
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */

// 设计哈希映射
class MyHashMap {
public:
    /** Initialize your data structure here. */
    MyHashMap() {

    }

    /** value will always be non-negative. */
    void put(int key, int value) {

    }

    /** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
    int get(int key) {

    }

    /** Removes the mapping of the specified value key if this map contains a mapping for the key */
    void remove(int key) {

    }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */