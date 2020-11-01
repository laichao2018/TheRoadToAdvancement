//
// Created by LaiChao on 2020/11/1.
//

#include "../include/LinkListSolutions.h"
#include <stack>

using namespace std;

ListNode *LinkListSolution::getKthFromEnd(ListNode *head, int k) {
    // 双指针法
    if (head == nullptr) {
        return head;
    }
    ListNode * preNode = head;
    ListNode * behNode = head;
    while (k) {
        preNode = preNode->next;
        k--;
    }
    while (preNode != nullptr) {
        preNode = preNode->next;
        behNode = behNode->next;
    }
    return behNode;
}

ListNode *LinkListSolution::mergeTwoLists(ListNode *l1, ListNode *l2) {
    if (l1 == nullptr) {
        return l2;
    }
    if (l2 == nullptr) {
        return l1;
    }
    ListNode * resNode = new ListNode(0);
    ListNode * pResNode = resNode;
    ListNode * pL1 = l1, *pL2 = l2;
    while (pL1 && pL2) {
        if (pL1->val >= pL2->val) {
            pResNode->next = pL2;
            pL2 = pL2->next;
        } else {
            pResNode->next = pL1;
            pL1 = pL1->next;
        }
        pResNode = pResNode->next;
    }
    if (pL1 != nullptr) {
        pResNode->next = pL1;
    }
    if (pL2 != nullptr) {
        pResNode->next = pL2;
    }
    return resNode->next;
}

ListNode *LinkListSolution::removeNthFromEnd(ListNode *headNode, int n) {
    ListNode * dummy = new ListNode(0, headNode);
    stack<ListNode *> sNodes;
    ListNode * currNode = dummy;
    while (currNode) {
        sNodes.push(currNode);
        currNode = currNode->next;
    }
    while (n) {
        sNodes.pop();
        n--;
    }
    ListNode * preNode = sNodes.top();
    preNode->next = preNode->next->next;
    ListNode * resNode = dummy->next;
    delete dummy;
    return resNode;
}















