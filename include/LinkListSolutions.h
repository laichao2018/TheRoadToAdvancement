//
// Created by LaiChao on 2020/11/1.
//

#ifndef THEROADTOADVANCEMENT_LINKLISTSOLUTIONS_H
#define THEROADTOADVANCEMENT_LINKLISTSOLUTIONS_H

#include "./__OSJudge.h"
#include "./DataStructure/List.h"
#include "./DataStructure/Tree.h"
#include <vector>

using namespace std;

class LinkListSolution {
public:
    static ListNode *initLinkList();                        // 链表初始化
    static bool destroyLinklist(ListNode *headNode);        // 链表置空
    static bool createLinklist_PreInsert(ListNode *&headNode, int initData, int dataNum);    // 链表创建(头插法)
    static bool createLinklist_BehInsert(ListNode *&headNode, int initData, int dataNum);    // 链表创建(尾插法)
    static int getLinklistLength(ListNode *&headNode);      // 获取链表长度&链表遍历
    static bool deleteLinklist(ListNode *&headNode, int index, int &delData);       // 删除链表结点
    static ListNode *listRotate(ListNode *headNode);        // 链表逆序***
    static bool isLinklistLoop(ListNode *headNode);         // 是否是环形链表***
    static ListNode *getIntersectionNode(ListNode *headA, ListNode *headB);         // 160. 相交链表 || 剑指 Offer 52. 两个链表的第一个公共节点
    static ListNode *deleteDuplicates(ListNode *headNode);          // 83. 删除排序链表中的重复元素
    static ListNode *removeNthFromEnd(ListNode *headNode, int n);   // 19. 删除链表的倒数第N个节点
    static ListNode *swapPairs(ListNode *headNode);        // 24. 两两交换链表中的节点
    static bool isPalindrome(ListNode *headNode);          // 234. 回文链表
    static vector<ListNode *> splitListToParts(ListNode *root, int k);    // *** 725. 分隔链表 ***
    static ListNode *oddEvenList(ListNode *head);          // 328. 奇偶链表
    static ListNode *deleteNode(ListNode *head, int val);       // 剑指 Offer 18. 删除链表的节点
    static vector<ListNode *> listOfDepth(TreeNode *tree);      // 面试题 04.03. 特定深度节点链表
    static ListNode *sortList(ListNode *head);                  // 148. 排序链表
    static ListNode *partition(ListNode *head, int x);             // 面试题 02.04. 分割链表
    static ListNode *partition2(ListNode *head, int x);            // 面试题 02.04. 分割链表	==== 不使用 vector 写法
    static ListNode *reverseKGroup(ListNode *head, int k);         // 25. K 个一组翻转链表
    static ListNode *mergeTwoLists(ListNode *l1, ListNode *l2);    // 21. 合并两个有序链表
    static ListNode *FindFirstCommonNode_3(ListNode *pHead1, ListNode *pHead2);    // 两个链表的第一个公共结点
    static ListNode *getKthFromEnd(ListNode *head, int k);         // 剑指 Offer 22. 链表中倒数第k个节点
};

#endif //THEROADTOADVANCEMENT_LINKLISTSOLUTIONS_H
