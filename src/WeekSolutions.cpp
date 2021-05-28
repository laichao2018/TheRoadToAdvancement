//
// Created by laichao on 2021/1/2.
//

#include "WeekSolutions.h"
#include <algorithm>
#include <set>
#include <cmath>

///// ================================== HELP CLASS ==================================
struct Query {
    int id, p, m;

    bool operator<(const Query &t) const {
        return m < t.m;
    }
};

int getString(string &a, string &b) {
    int x = 0, y = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) {
            if (a[i] == '0') x++;
            else y++;
        }
    }
    if (x != y) return INT_MAX;
    return x;
}

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
                pre = curr;    // 可以分割
                curr = s[j + 1] - '0';
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

int WeekSolutions::subsetXORSum(vector<int> &nums) {
    //********** 二进制枚举 **********
    // 用一个长度为n的二进制数来表示所有的子集，每一位对应nums每一位取还是不取（二进制1和0）
    // 比如：1010对应的就是nums数组的第一个数和第三个数组成的子集。
    int n = nums.size();
    int res = 0;
    for (int i = 0; i < 1 << n; i++) {  // 总共有(1<<n)种子集情况
        int s = 0;
        for (int j = 0; j < n; j++) {
            if (i >> j & 1) {   // 如果当前位为1，表示当前数被选入子集
                s ^= nums[j];
            }
        }
        res += s;
    }
    return res;
}

int WeekSolutions::minSwaps(string s) {
    int n = s.size();
    string a(n, '0'), b(n, '0');
    for (int i = 1; i < a.size(); i += 2) a[i] = '1';
    for (int i = 0; i < b.size(); i += 2) b[i] = '1';
    int res = min(getString(s, a), getString(s, b));
    if (res == INT_MAX) return -1;
    return res;
}

bool WeekSolutions::checkZeroOnes(string s) {
    int one = 0, zero = 0;
    for (int i = 0, x = 0, y = 0; i < s.length(); i++) {
        if (s[i] == '0') y++, x = 0;
        else x++, y = 0;
        one = max(x, one);
        zero = max(y, zero);
    }
    return one > zero;
}

int WeekSolutions::minSpeedOnTime(vector<int> &dist, double hour) {
    int n = dist.size();
    long long hr = llround(hour * 100); // 将 hour 乘 100 以转为整数
    // 时间必须大于路段数减1
    if (hr <= (n - 1) * 100) return -1;
    // 使用二分算法
    int l = 1, r = 1e7;
    while (l < r) {
        int mid = l + (r - l) / 2;
        long long t = 0;    // 判断当前时速是否满足时限
        for (int i = 0; i < n - 1; i++) {
            t += (dist[i] - 1) / mid + 1;
        }
        t *= mid;
        t += dist[n - 1];
        if (t * 100 <= hr * mid) r = mid;
        else l = mid + 1;
    }
    return l;
}