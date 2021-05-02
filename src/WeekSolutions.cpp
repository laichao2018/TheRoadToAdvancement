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
