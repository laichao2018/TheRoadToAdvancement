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

class WeekSolutions {
public:
    //=================================== No.51 - 双周塞 ===================================
    static string replaceDigits(string s);      // 5730. 将所有数字用字符替换
    static int maximumElementAfterDecrementingAndRearranging(vector<int> &arr);     // 5732. 减小和重新排列数组后的最大元素
    static vector<int> closestRoom(vector<vector<int>> &rooms, vector<vector<int>> &queries);       // 5733. 最近的房间
};

// No.51 - 双周赛
// 5731. 座位预约管理系统
class SeatManager {
private:
    priority_queue<int, vector<int>, greater<int>> heap;
public:
    SeatManager(int n) {
        for (int i = 1; i <= n; i++) heap.push(i);
    }

    int reserve() {
        int minNum = heap.top();
        heap.pop();
        return minNum;
    }

    void unreserve(int seatNumber) {
        heap.push(seatNumber);
    }
};

#endif //THEROADTOADVANCEMENT_WEEKSOLUTIONS_H
