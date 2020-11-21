//
// Created by LaiChao on 2020/11/20.
//

#include "DynamicProgramming.h"
#include <vector>

using namespace std;

int DPSolutions::climbStairs(int n) {
    if (n == 1) {
        return 1;
    }
    if (n == 2) {
        return 2;
    }
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
