//
// Created by LaiChao on 2020/11/1.
//

#include "../include/SortSolutions.h"

void SortSolution::bubleSort(vector<int> &nums) {
    if (nums.size() < 2) {
        return;
    }
    for (int i = 0; i < nums.size(); i++) {     // 外层循环控制总趟数
        for (int j = 1; j < nums.size() - i; j++) {
            if (nums[j - 1] > nums[j]) {
                swap(nums[j - 1], nums[j]);
            }
        }
    }
}

void SortSolution::quickSort(vector<int> &nums) {

}
