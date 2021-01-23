//
// Created by LaiChao on 2020/11/20.
//

#ifndef THEROADTOADVANCEMENT_ACWINGSOLUTIONS_H
#define THEROADTOADVANCEMENT_ACWINGSOLUTIONS_H

#include "./__OSJudge.h"
#include "./DataStructure/List.h"
#include <vector>

using namespace std;

// 算法基础课相关代码模板
class BaseTemplate {
public:
    static void quick_sort(vector<int> &nums);       // 785. 快速排序
    static void merge_sort(vector<int> &nums);       // 787. 归并排序
};

class AcStar {
public:
    static int getNumberOfK(vector<int> &nums, int k);      // 67. 数字在排序数组中出现的次数
    static int getMissingNumber(vector<int> &nums);         // 68. 0到n-1中缺失的数字
    static void reOrderArray(vector<int> &array);           // 32. 调整数组顺序使奇数位于偶数前面
    static vector<int> printListReversingly(ListNode *head);    // 17. 从尾到头打印链表
    static vector<int> getLeastNumbers_Solution(vector<int> input, int k);  // 53. 最小的k个数
    static vector<int> findNumbersWithSum(vector<int> &nums, int target);   // 75. 和为S的两个数字
};


#endif //THEROADTOADVANCEMENT_ACWINGSOLUTIONS_H
