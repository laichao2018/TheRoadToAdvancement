//
// Created by LaiChao on 2020/11/5.
//

#include "OfferSolutions.h"
#include <queue>
#include <vector>
#include <set>

using namespace std;

int OfferSolutions::TreeDepth(TreeNode *pRoot) {
    if (pRoot == nullptr) {
        return 0;
    }
    int res = 0;
    queue<TreeNode *> qNodes;
    qNodes.push(pRoot);
    while (!qNodes.empty()) {
        int currSize = qNodes.size();
        for (int i = 0; i < currSize; i++) {
            res++;
            TreeNode *currNode = qNodes.front();
            qNodes.pop();
            if (currNode->left != nullptr) {
                qNodes.push(currNode->left);
            }
            if (currNode->right != nullptr) {
                qNodes.push(currNode->right);
            }
        }
    }
    return res;
}

int OfferSolutions::numWays(int n) {
    vector<int> dpArr(n + 1, 0);
    dpArr[0] = 1;
    dpArr[1] = 1;
    dpArr[2] = 2;
    for (int i = 3; i <= n; i++) {
        dpArr[i] = (dpArr[i - 1] + dpArr[i - 2]) % 1000000007;
    }
    return dpArr[n];
}

vector<int> OfferSolutions::multiply(const vector<int> &A) {
    if (A.empty()) {
        return {};
    }
    vector<int> result;
    for (int i = 0; i < A.size(); i++) {
        int tmpValue = 1;
        for (int j = 0; j < A.size(); j++) {
            if (i != j) {
                tmpValue *= A[j];
            }
        }
        result.push_back(tmpValue);
    }
    return result;
}

int OfferSolutions::Add(int num1, int num2) {
    /*_asm
    {
        MOV EAX, a
        MOV ECX, b
        ADD EAX, ECX
    }*/

    while (num2) {
        int temp = num1 ^num2;
        num2 = (num1 & num2) << 1;
        num1 = temp;
    }
    return num1;
}

void OfferSolutions::Mirror(TreeNode *pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    if (pRoot->left == nullptr && pRoot->right == nullptr) {
        return;
    }
    swap(pRoot->left, pRoot->right);

    if (pRoot->left != nullptr) {
        Mirror(pRoot->left);
    }
    if (pRoot->right != nullptr) {
        Mirror(pRoot->right);
    }
}

vector<int> OfferSolutions::twoSum(vector<int> &nums, int target) {
    if (nums.size() < 2) {
        return {};
    }
    vector<int> result;
    int minIndex = 0, maxIndex = nums.size() - 1;
    while (minIndex < maxIndex) {
        int currSum = nums[minIndex] + nums[maxIndex];
        if (currSum > target) {
            maxIndex--;
        } else if (currSum < target) {
            minIndex++;
        } else {
            result.push_back(nums[minIndex]);
            result.push_back(nums[maxIndex]);
            return result;
        }
    }
    return result;
}

vector<int> OfferSolutions::exchange(vector<int> &nums) {
    deque<int> lNums;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] % 2) {
            lNums.push_front(nums[i]);
        } else {
            lNums.push_back(nums[i]);
        }
    }
    vector<int> res;
    auto pList = lNums.begin();
    while (pList != lNums.end()) {
        res.push_back(*pList++);
    }
    return res;
}

vector<int> OfferSolutions::exchange2(vector<int> &nums) {
    /// ===== 双 指 针 法 =====
    int left = 0, right = nums.size() - 1;
    while (left < right) {
        if (nums[left] % 2 == 0) {
            while (left < right && nums[right] % 2 == 0) {
                right--;
            }
            swap(nums[left], nums[right--]);
        }
        left++;
    }
    return nums;
}

bool OfferSolutions::findNumberIn2DArray(vector<vector<int>> &matrix, int target) {
    if (matrix.size() == 0) {
        return false;
    }
    int matrixRow = matrix.size();
    int matrixCol = matrix[0].size();
    int posRow = matrixRow - 1, posCol = 0;
    while (posRow >= 0 && posCol < matrixCol) {
        int currNumber = matrix[posRow][posCol];
        if (target == currNumber) {
            return true;
        } else if (currNumber < target) {
            posCol++;
        } else {
            posRow--;
        }
    }
    return false;
}

int OfferSolutions::minArray(vector<int> &numbers) {
    if (numbers.empty()) {
        return {};
    }
    if (numbers.size() == 1) {
        return numbers[0];
    }
    for (int forword = 1, behind = 0; forword < numbers.size() && behind < numbers.size(); forword++, behind++) {
        if (numbers[forword] < numbers[behind]) {
            return numbers[forword];
        }
    }
    return numbers[0];
}

int OfferSolutions::Sum_Solution(int n) {
    int result = n;
    result && (result += Sum_Solution(n - 1));
    return result;
}

int OfferSolutions::FindGreatestSumOfSubArray(vector<int> array) {
    if (array.empty()) {
        return 0;
    }
    int max_sum = -99999;
    int curr_sum = array[0];
    for (int i = 1; i < array.size(); i++) {
        curr_sum = curr_sum > 0 ? curr_sum + array[i] : array[i];
        max_sum = max(max_sum, curr_sum);
    }
    return max_sum;
}

int OfferSolutions::jumpFloor(int number) {
    if (number < 1) {
        return 0;
    }
    if (number == 1) {
        return 1;
    }
    if (number == 2) {
        return 2;
    }
    return jumpFloor(number - 1) + jumpFloor(number - 2);
}

void OfferSolutions::FindNumsAppearOnce(vector<int> data, int *num1, int *num2) {
    if (data.size() < 2) {
        return;
    }
    set<int> save;
    set<int>::iterator pSave;
    for (int i = 0; i < data.size(); i++) {
        if (save.find(data[i]) == save.end()) {        //// 没找到
            save.insert(data[i]);
        } else {    /// 找到的话直接删除
            pSave = save.find(data[i]);
            save.erase(pSave);
        }
    }
    pSave = save.begin();
    *num1 = *pSave;
    *num2 = *(++pSave);
}

ListNode *OfferSolutions::FindFirstCommonNode(ListNode *pHead1, ListNode *pHead2) {
    if (pHead1 == nullptr || pHead2 == nullptr) {
        return {};
    }
    ListNode *p1 = pHead1, *p2 = pHead2;
    while (p1 != p2) {
        p1 = (p1 == nullptr) ? pHead2 : p1->next;
        p2 = (p2 == nullptr) ? pHead1 : p2->next;
    }
    return p1;
}

ListNode *OfferSolutions::EntryNodeOfLoop(ListNode *pHead) {
    //// 使用快慢指针
    ListNode *pFastNode = pHead, *pSlowNode = pHead;
    while (pFastNode && pFastNode->next) {
        pFastNode = pFastNode->next->next;
        pSlowNode = pSlowNode->next;
        if (pFastNode == pSlowNode) {
            break;
        }
    }
    if (!pFastNode || !pFastNode->next) {
        return nullptr;        //// 说明是没有环的
    }
    pSlowNode = pHead;    //// 重新从链表前出发
    while (pSlowNode != pFastNode) {
        pFastNode = pFastNode->next;    //// fast 指针从相遇点出发
        pSlowNode = pSlowNode->next;
    }
    return pSlowNode;
}
