//
// Created by LaiChao on 2020/11/1.
//

#include "../include/SortSolutions.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void help_quickSort(int left, int right, vector<int> &arr) {
    if (left >= right) {    //递归边界条件
        return;
    }
    if (left < 0 || right >= arr.size()) {
        std::cout << "error args! array bound." << endl;
        return;
    }                       // 非法输入判断,防止数组越界
    int i, j, base, temp;
    i = left, j = right;
    base = arr[left];       // 取最左边的数为基准数
    while (i < j) {
        while (arr[j] <= base && i < j)
            j--;
        while (arr[i] >= base && i < j)
            i++;
        if (i < j) {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // 基准数归位
    arr[left] = arr[i];
    arr[i] = base;
    help_quickSort(left, i - 1, arr);   // 递归左边
    help_quickSort(i + 1, right, arr);   // 递归右边
}

void SortSolution::bubleSort(vector<int> &nums) {
    if (nums.size() < 2) {
        return;
    }
    for (int i = 0; i < nums.size(); i++) {     // 外层循环控制总趟数
        bool flag = false;
        for (int j = 1; j < nums.size() - i; j++) {
            if (nums[j - 1] > nums[j]) {
                swap(nums[j - 1], nums[j]);
                flag = true;
            }
        }
        if (!flag) {    // 说明已经排序完成，避免无用计算
            return;
        }
    }
}

void SortSolution::quickSort(vector<int> &nums) {
    help_quickSort(0, nums.size() - 1, nums);
}

void SortSolution::insertionSort(vector<int> &nums) {
    int j, tmp;
    for (int i = 1; i < nums.size(); i++) {
        tmp = nums[i];
        for (j = i - 1; j >= 0 && nums[j] > tmp; j--) {
            nums[j + 1] = nums[j];
        }
        nums[j + 1] = tmp;
    }
}

void SortSolution::selectionSort(vector<int> &nums) {
    if (nums.size() < 2) {
        return;
    }
    for (int i = 0; i < nums.size(); i++) {
        // 寻找 [i, n) 区间里的最小值
        int minIndex = i;
        for (int j = i + 1; j < nums.size(); j++) {
            if (nums[j] < nums[minIndex]) {
                minIndex = j;
            }
        }
        swap(nums[minIndex], nums[i]);
    }
}

void SortSolution::radixSort(vector<int> &nums) {
    if (nums.size() < 2) {
        return;
    }
    int exp = 1;
    vector<int> buff(nums.size());
    int maxVal = *max_element(nums.begin(), nums.end());
    while (maxVal >= exp) {
        vector<int> cnt(10);
        for (int i = 0; i < nums.size(); i++) {
            int digit = (nums[i] / exp) % 10;
            cnt[digit]++;
        }
        for (int i = 1; i < 10; i++) {
            cnt[i] += cnt[i - 1];
        }
        for (int i = nums.size() - 1; i >= 0; i--) {
            int digit = (nums[i] / exp) % 10;
            buff[cnt[digit] - 1] = nums[i];
            cnt[digit]--;
        }
        copy(buff.begin(), buff.end(), nums.begin());
        exp *= 10;
    }
    return;
}

void SortSolution::shellSort(vector<int> &nums) {
    int n = nums.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int key = nums[i], j;
            for (j = i; j >= gap && key < nums[j - gap]; j -= gap) {
                nums[j] = nums[j - gap];
            }
            nums[j] = key;
        }
    }
}
