//
// Created by LaiChao on 2020/11/20.
//

#include "AcWingSolutions.h"
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>
#include <unordered_set>

using namespace std;

// _________________________________HELP　FUNC_________________________________

void HelpFunc_quick_sort(vector<int> &q, int l, int r) {
    if (l >= r) {
        return;
    }

    int x = q[l + r >> 1], i = l, j = r;
    while (1) {
        while (q[i] < x) i = i + 1;
        while (q[j] > x) j = j - 1;
        if (i >= j) {
            break;
        }
        swap(q[i], q[j]);
        i = i + 1;
        j = j - 1;
    }

    HelpFunc_quick_sort(q, l, j);
    HelpFunc_quick_sort(q, j + 1, r);
}

void HelpFunc_merge_sort(vector<int> q, int l, int r) {
    if (l >= r) {
        return;
    }

    int mid = l + r + 1 >> 1;   //注意mid是向上取整
    HelpFunc_merge_sort(q, l, mid - 1), HelpFunc_merge_sort(q, mid, r);

    int k = 0, i = l, j = mid, tmp[r - l + 1];
    while (i < mid && j <= r)
        if (q[i] <= q[j]) {
            tmp[k++] = q[i++];
        } else {
            tmp[k++] = q[j++];
        }
    while (i < mid) {
        tmp[k++] = q[i++];
    }
    while (j <= r) {
        tmp[k++] = q[j++];
    }

    for (k = 0, i = l; i <= r; k++, i++) {
        q[i] = tmp[k];
    }
}

// _________________________________SOLUTION FUNC_________________________________

void BaseTemplate::quick_sort(vector<int> &nums) {
    HelpFunc_quick_sort(nums, 0, nums.size() - 1);
}

void BaseTemplate::merge_sort(vector<int> &nums) {
    HelpFunc_merge_sort(nums, 0, nums.size() - 1);
}

int AcStar::getNumberOfK(vector<int> &nums, int k) {
    unordered_map<int, int> _map;
    for (int i:nums) {
        _map[i]++;
    }
    return _map[k];
}

int AcStar::getMissingNumber(vector<int> &nums) {
    int curr = 0;
    for (int i = 0; i < nums.size(); i++) curr += nums[i];
    int true_sum = 0;
    for (int i = 0; i < nums.size() + 1; i++) true_sum += i;
    return true_sum - curr;
}

void AcStar::reOrderArray(vector<int> &array) {
    int l = 0, r = array.size() - 1;
    while (l < r) {
        while (l < r && array[l] % 2 == 1) l++;
        while (l < r && array[r] % 2 == 0) r--;
        if (l < r) swap(array[l], array[r]);
    }
}

vector<int> AcStar::printListReversingly(ListNode *head) {
    vector<int> res;
    while (head != nullptr) {
        res.push_back(head->val);
        head = head->next;
    }
    reverse(res.begin(), res.end());
    return res;
}

vector<int> AcStar::getLeastNumbers_Solution(vector<int> input, int k) {
    priority_queue<int, vector<int>, less<int>> q;
    for (int i = 0; i < input.size(); i++) {
        q.push(input[i]);
        if (q.size() > k) q.pop();
    }
    vector<int> res;
    while (!q.empty()) {
        res.push_back(q.top());
        q.pop();
    }
    reverse(res.begin(), res.end());
    return res;
}

vector<int> AcStar::findNumbersWithSum(vector<int> &nums, int target) {
    unordered_set<int> hash;
    for (int i = 0; i < nums.size(); i++) {
        if (hash.count(target - nums[i])) return {target - nums[i], nums[i]};
        else hash.insert(nums[i]);
    }
    return {};
}

// _________________________________OTHER CLASS_________________________________
// *** 20. 用两个栈实现队列 ***
class MyQueue {
public:
    MyQueue() = default;

    void push(int x) {
        stk.push(x);
    }

    int pop() {
        copy(stk, cache);
        int res = cache.top();
        cache.pop();
        copy(cache, stk);
        return res;
    }

    int peek() {
        copy(stk, cache);
        int res = cache.top();
        copy(cache, stk);
        return res;
    }

    bool empty() {
        return stk.empty();
    }

private:
    stack<int> stk, cache;

    void copy(stack<int> &a, stack<int> &b) {
        while (a.size()) {
            b.push(a.top());
            a.pop();
        }
    }
};