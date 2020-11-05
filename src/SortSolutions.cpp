//
// Created by LaiChao on 2020/11/1.
//

#include "../include/SortSolutions.h"
#include <iostream>

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

void help_quickSort(int left, int right, vector<int> &arr) {
    if (left >= right) {    //递归边界条件
        return;
    }
    if (left < 0 || right >= arr.size()) {
        std::cout << "error args! array bound." << endl;
        return;
    }                       //非法输入判断,防止数组越界
    int i, j, base, temp;
    i = left, j = right;
    base = arr[left];       //取最左边的数为基准数
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
    //基准数归位
    arr[left] = arr[i];
    arr[i] = base;
    help_quickSort(left, i - 1, arr);    //递归左边
    help_quickSort(i + 1, right, arr);   //递归右边
}

void SortSolution::quickSort(vector<int> &nums) {
    help_quickSort(0, nums.size() - 1, nums);
}
