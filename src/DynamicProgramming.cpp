//
// Created by LaiChao on 2020/11/20.
//

#include "DynamicProgramming.h"
#include <vector>
#include <algorithm>

using namespace std;

int DPSolutions::climbStairs(int n) {
    if (n == 1) return 1;
    if (n == 2) return 2;
    vector<int> dpArr(n, 0);
    dpArr[1] = 1;
    dpArr[2] = 2;
    for (int i = 3; i <= n; i++) {
        dpArr[i] = dpArr[i - 1] + dpArr[i - 2];
    }
    return dpArr[n];
}

int DPSolutions::minPathSum(vector<vector<int>> &grid) {

    return 0;
}

int DPSolutions::lengthOfLIS(vector<int> &nums) {
    if (nums.empty()) return 0;
    vector<int> dpArr(nums.size(), 0);
    for (int i = 0; i < nums.size(); i++) {
        dpArr[i] = 1;   // 初始值
        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i]) dpArr[i] = max(dpArr[i], dpArr[j] + 1);
        }
    }
    return *max_element(dpArr.begin(), dpArr.end());
}

int DPSolutions::minSwap(vector<int> &A, vector<int> &B) {
    vector<vector<int>> dp(A.size(), vector<int>(2, 0));
    dp[0][0] = 0;
    dp[0][1] = 1;
    for (int i = 1; i < A.size(); i++) {
        //1. 已经各自有序
        //2. 存在交叉
        //3. 既有序，也交叉
        if (A[i - 1] < A[i] && B[i - 1] < B[i]) {// 各自有序
            if (A[i - 1] < B[i] && B[i - 1] < A[i]) {// 且存在交叉
                dp[i][0] = min(dp[i - 1][0], dp[i - 1][1]);
                dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + 1;
            } else {// 有序但不存在交叉
                dp[i][0] = dp[i - 1][0];//不交换，再上一轮不交换的基础上，不变。
                dp[i][1] = dp[i - 1][1] + 1; // 由于不存在交叉，所以如果要交换的话，得在上一轮交换的基础上，本轮再次交换
            }
        } else {//无序，则必然存在交叉
            dp[i][0] = dp[i - 1][1];// 由于必须交叉，所以如果要不换的话，必须在上一轮交换的基础上，本轮才可以不交换
            dp[i][1] = dp[i - 1][0] + 1;// 同上，必须在上一轮不交换的基础上，本轮交换
        }
    }
    return min(dp[dp.size() - 1][0], dp[dp.size() - 1][1]);
}

int DPSolutions::maxSubArray(vector<int> &nums) {
    if (nums.empty()) return 0;
    vector<int> dpArr(nums.size());
    int curr_sum = nums[0];
    int max_sum = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        // 只要前面的数加起来不小于0，就不会对当前数起到减弱作用
        curr_sum = curr_sum > 0 ? curr_sum + nums[i] : nums[i];
        max_sum = max(max_sum, curr_sum);
    }
    return max_sum;
}
