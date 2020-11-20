//
// Created by LaiChao on 2020/11/20.
//

#include "AcWingSolutions.h"
#include <vector>

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
