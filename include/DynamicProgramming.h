//
// Created by LaiChao on 2020/11/20.
//

#ifndef THEROADTOADVANCEMENT_DYNAMICPROGRAMMING_H
#define THEROADTOADVANCEMENT_DYNAMICPROGRAMMING_H

#include <vector>
#include <string>

using namespace std;

class DPSolutions {
public:
    // 线性动态规划问题
    static int climbStairs(int n);      // 70. 爬楼梯
    static int minSwap(vector<int> &A, vector<int> &B); // 801. 使序列递增的最小交换次数（*** 难理解 ***）
    static int maxSubArray(vector<int> &nums);          // 53. 最大子序和

    // Other DP Solutions
    static int minPathSum(vector<vector<int>> &grid);   // 64. 最小路径和
    static int lengthOfLIS(vector<int> &nums);          // 300. 最长递增子序列
    static int strangePrinter(string s);                // 664. 奇怪的打印机
};

#endif //THEROADTOADVANCEMENT_DYNAMICPROGRAMMING_H
