//
// Created by LaiChao on 2020/10/31.
//

#ifndef THEROADTOADVANCEMENT_TREE_H
#define THEROADTOADVANCEMENT_TREE_H

///// 剑指offer && LeetCode 中的二叉树数据结构
//struct TreeNode {
//public:
//    int val;
//    struct TreeNode *left;
//    struct TreeNode *right;
//};

typedef struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
} TreeNode;

/// LeetCode 中的另一种树结构
class Node {
public:
    int val;
    Node *left;
    Node *right;
    Node *next;

    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int _val, Node *_left, Node *_right, Node *_next)
            : val(_val), left(_left), right(_right), next(_next) {}
};

// 剑指offer 35 复杂链表的复制
// 原名： Node
class RandomNode {
public:
    int val;
    RandomNode *next;
    RandomNode *random;

    RandomNode(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

#endif //THEROADTOADVANCEMENT_TREE_H
