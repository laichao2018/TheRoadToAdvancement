//
// Created by laichao on 2021/3/29.
//
// 大根堆的简单实现

#ifndef __MAXHEAP_SOLUTION__
#define __MAXHEAP_SOLUTION__

#include <string>

// 将堆中的元素以二叉树的形式存入在数组
// 使用数组实现整数类型的「最大堆」和「最小堆」
class MaxHeap {
public:
    MaxHeap(int _heap_size_) {
        this->heapSize = _heap_size_;
        heapData = new int[_heap_size_ + 1];
        heapData[0] = 0; // 数组的第0个索引的元素我们不会使用，请随便设置设置成任何一个值。
    }

    // 添加元素
    void add(int _element) {
        realSize++;
        if (realSize > heapSize) {      // 添加过多的数据
            realSize--;
            return;
        }
        heapData[realSize] = _element;   // 将添加的元素添加到数组中的最后一个位置
        int index = realSize;           // 新增元素的索引位置
        // 注意，如果用数组表示完全二叉树，并且根结点存储在数组的索引1的位置的时候，任何一个节点的父节点索引位置为「该节点的索引位置/2」
        // 任何一个节点的左孩子节点的索引位置为「该节点的索引位置*2」，任何一个节点的右孩子节点的索引位置为「该节点的索引位置*2+1」
        int parent = index / 2;         // 找到元素的父节点
        while (heapData[parent] < heapData[index] && index > 1) {     // 当添加的元素大于父节点时，需要将父节点的值和新增元素的值交换
            int tmp = heapData[index];
            heapData[index] = heapData[parent];
            heapData[parent] = tmp;
            index = parent;
            parent = index / 2;
        }
    }

    // 获取堆顶元素
    int peek() {
        return heapData[1];
    }

    // 删除堆顶元素
    int pop() {
        if (realSize < 1) return -1;    // 如果堆中无元素
        else {
            int removeNum = heapData[1];
            heapData[1] = heapData[realSize];   // 将「堆」中的最后一个元素赋值给堆顶元素
            realSize--;     // 相当于抹去了最后一个元素
            int index = 1;
            // 当删除的元素不是孩子节点时
            while (index < realSize && index <= realSize / 2) { // 当删除的元素不是孩子节点
                int left = index * 2;       // 被删除节点的左孩子节点
                int right = index * 2 + 1;  // 被删除节点的右孩子节点
                // 当删除节点的元素小于 左孩子节点或者右孩子节点，代表该元素的值小，此时需要将该元素与左、右孩子节点中最大的值进行交换
                if (heapData[index] < heapData[left] || heapData[index] < heapData[right]) {
                    if (heapData[left] > heapData[right]) {     // 插入到较大元素处
                        int tmp = heapData[left];
                        heapData[left] = heapData[index];
                        heapData[index] = tmp;
                        index = left;
                    } else {
                        int tmp = heapData[right];
                        heapData[right] = heapData[index];
                        heapData[index] = tmp;
                        index = right;
                    }
                } else break;   // 仍然满足大根堆条件
            }
            return removeNum;   // 返回被删除的元素
        }
    }

    // 返回「堆」的元素个数
    int size() {
        return realSize;
    }

    // 打印「堆」元素
    std::string toString() {
        if (realSize < 1) return "No Data...\n";
        std::string res;
        res.push_back('[');
        for (int i = 1; i <= realSize; i++) {
            res.push_back(heapData[i]);
            res.push_back(',');
        }
        res.push_back(']');
        return res;
    }

private:
    int realSize = 0;   // 用于记录「堆」的元素个数
    int heapSize = 0;   // 用于数组的大小，因为数组在创建的时候至少需要指明数组的元素个数
    int *heapData;       // 使用数组创建完全二叉树的结构，然后使用二叉树构建一个「堆」
};

#endif
