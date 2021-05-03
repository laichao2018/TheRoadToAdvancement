//
// Created by laichao on 2021/1/2.
//

#include "WeekSolutions.h"
#include <algorithm>
#include <set>

///// ================================== HELP CLASS ==================================
struct Query {
    int id, p, m;

    bool operator<(const Query &t) const {
        return m < t.m;
    }
};

///// =============================== CLASS Definition ===============================
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

///// ================================== CLASS FUNC ==================================
string WeekSolutions::replaceDigits(string s) {
    for (int i = 0; i < s.size(); i += 2) {
        int add = (int) (s[i + 1] - '0');
        s[i + 1] = (char) (s[i] + add);
    }
    return s;
}

int WeekSolutions::maximumElementAfterDecrementingAndRearranging(vector<int> &arr) {
    sort(arr.begin(), arr.end());
    int last = 1;
    for (int i = 1; i < arr.size(); i++) {
        last = min(arr[i], last + 1);   // 保证相邻元素之间差不大于1
    }
    return last;
}

vector<int> WeekSolutions::closestRoom(vector<vector<int>> &rooms, vector<vector<int>> &queries) {
    int n = queries.size();
    vector<Query> q;
    for (int i = 0; i < queries.size(); i++) {
        q.push_back({i, queries[i][0], queries[i][1]});
    }
    sort(q.begin(), q.end());
    sort(rooms.begin(), rooms.end(), [](vector<int> &a, vector<int> &b) {
        return a[1] < b[1];     // 按面积从小到大排序
    });
    const int INF_MAX = 1e9;
    set<int> S{-INF_MAX, INF_MAX};
    vector<int> res(n);
    for (int i = n - 1, j = rooms.size() - 1; i >= 0; i--) {    // 双指针
        while (j >= 0 && rooms[j][1] >= q[i].m) S.insert(rooms[j--][0]);  // 所有满足条件的room_id
        int p = q[i].p, id = q[i].id;
        auto k = S.lower_bound(p);  // 二分查找第一个小于p的位置
        auto u = k;
        --u;
        if (p - *u <= *k - p)res[id] = *u;
        else res[id] = *k;
        if (abs(res[id]) == INF_MAX) res[id] = -1;
    }
    return res;
}

int WeekSolutions::getMinDistance(vector<int> &nums, int target, int start) {
    int res = INT_MAX;
    for (int i = 0; i < nums.size(); i++) {
        if (target == nums[i]) {
            res = min(res, abs(i - start));
        }
    }
    return res;
}

bool WeekSolutions::splitString(string s) {
    // 暴力枚举法， 使用位运算增加速度
    int n = s.size();
    for (int i = 1; i < (1 << (n - 1)); i++) {
        bool flag = true;
        unsigned long long pre = -1, curr = s[0] - '0';     // 分别存储上一个数和当前数
        // 从前往后依次枚举
        for (int j = 0; j < n - 1; j++) {   // 寻找分割位置，规定在数字右边分割，最后一个数字无法分割
            if ((i >> j) & 1) {     // 如果此位置是1，表示分割线
                if (pre != -1 && curr != pre - 1) {
                    flag = false;
                    break;
                }
                pre = x;    // 可以分割
                x = s[j + 1] - '0';
            } else {
                curr = curr * 10 + s[j + 1] - '0';
            }
        }
        if (curr != pre - 1) flag = false;
        if (flag) return true;
    }
    return false;
}

int WeekSolutions::getMinSwaps(string num, int k) {
    string s = num;
    while (k--) next_permutation(s.begin(), s.end());
    int n = s.size();
    vector<int> c(n);
    int cnt[10] = {0};
    for (int i = 0; i < n; i++) {
        int x = num[i] - '0';
        cnt[x]++;
        int y = cnt[x];
        for (int j = 0; j < n; j++) {
            if (s[j] - '0' == x && --y == 0) {
                c[i] = j;
                break;
            }
        }
    }
    int res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (c[i] > c[j]) res++;
        }
    }
    return res;
}
