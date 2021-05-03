//
// Created by laichao on 2021/1/2.
// ========= 周 赛 题 =========
//

#ifndef THEROADTOADVANCEMENT_WEEKSOLUTIONS_H
#define THEROADTOADVANCEMENT_WEEKSOLUTIONS_H

#include <string>
#include <vector>
#include <queue>

using namespace std;

///// ================================== CLASS Declaration ==================================
class WeekSolutions {
public:
    //=================================== No.51 - 双周塞 ===================================
    static string replaceDigits(string s);      // 5730. 将所有数字用字符替换
    static int maximumElementAfterDecrementingAndRearranging(vector<int> &arr);     // 5732. 减小和重新排列数组后的最大元素
    static vector<int> closestRoom(vector<vector<int>> &rooms, vector<vector<int>> &queries);       // 5733. 最近的房间

    //=================================== No.239 - 周塞 ===================================
    static int getMinDistance(vector<int> &nums, int target, int start);            // 1848. 到目标元素的最小距离
    static bool splitString(string s);          // 1849. 将字符串拆分为递减的连续值
    static int getMinSwaps(string num, int k);  // 1850. 邻位交换的最小次数
};

// No.51 - 双周赛
// 5731. 座位预约管理系统
class SeatManager;

#endif //THEROADTOADVANCEMENT_WEEKSOLUTIONS_H
