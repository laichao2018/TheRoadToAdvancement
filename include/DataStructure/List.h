//
// Created by LaiChao on 2020/10/31.
//

#ifndef THEROADTOADVANCEMENT_LIST_H
#define THEROADTOADVANCEMENT_LIST_H

///// 剑指offer && LeetCode 中的链表数据结构
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

#endif //THEROADTOADVANCEMENT_LIST_H
