//
// Created by LaiChao on 2020/11/1.
//

#include "../include/LinkListSolutions.h"
#include <stack>
#include <iostream>
#include <vector>

using namespace std;

ListNode *LinkListSolution::getKthFromEnd(ListNode *head, int k) {
    // 双指针法
    if (head == nullptr) {
        return head;
    }
    ListNode *preNode = head;
    ListNode *behNode = head;
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
    ListNode *resNode = new ListNode(0);
    ListNode *pResNode = resNode;
    ListNode *pL1 = l1, *pL2 = l2;
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
    ListNode *dummy = new ListNode(0, headNode);
    stack<ListNode *> sNodes;
    ListNode *currNode = dummy;
    while (currNode) {
        sNodes.push(currNode);
        currNode = currNode->next;
    }
    while (n) {
        sNodes.pop();
        n--;
    }
    ListNode *preNode = sNodes.top();
    preNode->next = preNode->next->next;
    ListNode *resNode = dummy->next;
    delete dummy;
    return resNode;
}

ListNode *LinkListSolution::initLinkList() {
    ListNode *headNode = (ListNode *) malloc(sizeof(ListNode));     // 开辟空间
    if (headNode == nullptr) {
        return nullptr;     // 存储空间不足
    } else {
        headNode = nullptr;     // 不带头结点
        headNode->val = 0;      // 头结点初始化
        headNode->next = nullptr;
    }
    return headNode;
}

bool LinkListSolution::destroyLinklist(ListNode *headNode) {
    ListNode *currNode = headNode, *nextNode;
    while (currNode) {
        nextNode = currNode->next;
        free(currNode);
        currNode = nextNode;
    }
    currNode->next = nullptr;
    nextNode->next = nullptr;
    return true;
}

bool LinkListSolution::createLinklist_PreInsert(ListNode *&headNode, int initData, int dataNum) {
    int posFlag = 0;
    ListNode *s;    // 动态开辟空间的临时节点
    headNode = (ListNode *) malloc(sizeof(ListNode));
    if (headNode == nullptr) {
        return false;
    }
    headNode->next = nullptr;
    while (posFlag < dataNum) {
        s = (ListNode *) malloc(sizeof(ListNode));
        if (s == nullptr) {
            return false;
        }
        s->val = initData;
        s->next = headNode->next;
        headNode->next = s;
        posFlag++;
    }
    return true;
}

bool LinkListSolution::createLinklist_BehInsert(ListNode *&headNode, int initData, int dataNum) {
    int posFlag = 0;
    ListNode *r, *s;
    headNode = (ListNode *) malloc(sizeof(ListNode));
    if (headNode == nullptr) {
        return false;
    }
    r = headNode, s = headNode;
    while (posFlag < dataNum) {
        // 每次用s开辟新空间，r保持指向尾指针
        s = (ListNode *) malloc(sizeof(ListNode));
        if (s == nullptr) {
            return false;
        }
        s->val = initData;
        r->next = s;
        r = s;
        posFlag++;
    }
    r->next = nullptr;
    return true;
}

int LinkListSolution::getLinklistLength(ListNode *&headNode) {
    int resLen = 0;
    ListNode *pNode = headNode;
    while (pNode != nullptr) {
        pNode = pNode->next;
        resLen++;
    }
    return resLen;
}

bool LinkListSolution::deleteLinklist(ListNode *&headNode, int index, int &delData) {
    if (headNode == nullptr) {
        return false;
    }
    ListNode *pCurrNode = headNode;
    ListNode *pNode;
    while (pCurrNode->val != delData && pCurrNode->next != nullptr) {
        pNode = pCurrNode;
        pCurrNode = pCurrNode->next;
    }
    if (delData == pCurrNode->val) {
        if (pCurrNode == headNode) {
            headNode = pCurrNode->next;
        } else {
            pNode->next = pCurrNode->next;
        }
        free(pCurrNode);
    }
    return true;
}

ListNode *LinkListSolution::listRotate(ListNode *headNode) {
    ListNode *currNode = headNode;
    ListNode *preNode = nullptr, *tmpNode = nullptr;
    while (currNode != nullptr) {
        tmpNode = currNode->next;
        currNode->next = preNode;
        preNode = currNode;
        currNode = tmpNode;
    }
    return preNode;
}

bool LinkListSolution::isLinklistLoop(ListNode *headNode) {
    if (headNode == nullptr) {
        return false;
    }
    ListNode *pFast = headNode, *pSlow = headNode;
    while (pFast->next != nullptr && pSlow->next != nullptr) {
        if (pFast->next->next == nullptr) {
            return false;
        } else {
            pFast = pFast->next->next;
            pSlow = pSlow->next;
            if (pFast == pSlow) {
                return true;
            }
        }
    }
    return false;
}

ListNode *LinkListSolution::getIntersectionNode(ListNode *headA, ListNode *headB) {
    if (headA == nullptr || headB == nullptr) {
        return nullptr;
    }
    ListNode *ha = headA, *hb = headB;
    while (ha != hb) {
        ha = (ha == nullptr) ? headB : ha->next;
        hb = (hb == nullptr) ? headA : hb->next;
    }
    return ha;
}

ListNode *LinkListSolution::deleteDuplicates(ListNode *headNode) {
    if (headNode == nullptr) {
        return nullptr;
    }
    ListNode *pCurr = headNode, *pNext = headNode->next;
    while (pNext != nullptr) {
        if (pCurr->next == pNext->next) {
            pCurr->next = pNext->next;
            free(pNext);
            pNext = pCurr->next;
        } else {
            pCurr = pCurr->next;
            pNext = pNext->next;
        }
    }
    return headNode;
}

















