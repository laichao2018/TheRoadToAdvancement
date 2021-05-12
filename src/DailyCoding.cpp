//
// Created by LaiChao on 2020/10/31.
//

#include "../DataStructure/Tree.h"
#include "../include/DailyCoding.h"
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <numeric>
#include <stack>
#include <string>
#include <list>
#include <cmath>
#include <list>

using namespace std;

/// ================================== GLOBAL VAR ==================================
vector<string> gAns;
string gTemp;
string gDic[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
unordered_map<string, priority_queue<string, vector<string>, std::greater<string>>> gvfindItine;
vector<string> gSTK;
vector<vector<int>> gWinnerDPArr(21, vector<int>(21, 0));

// 通用
vector<vector<int>> vvRes;
vector<int> vRes, vPath;

///// ================================== HELP FUNC ==================================
void findSubsequencesbackTracking(vector<int> &nums, vector<vector<int>> &res, vector<int> &subSeq, int startIndex) {
    if (subSeq.size() > 1) {
        res.push_back(subSeq);    // 不return
    }
    unordered_set<int> uSet;
    for (int i = startIndex; i < nums.size(); i++) {
        if ((subSeq.empty() || nums[i] >= subSeq.back()) && uSet.find(nums[i]) == uSet.end()) {
            subSeq.push_back(nums[i]);
            findSubsequencesbackTracking(nums, res, subSeq, i + 1);
            subSeq.pop_back();
            uSet.insert(nums[i]);
        }
    }
}

void letterCombinationDFS(string &digits, int index) {
    if (index == digits.size()) {
        gAns.push_back(gTemp);
        return;
    }
    int t = digits[index] - '0';
    for (int i = 0; i < gDic[t].size(); i++) {
        gTemp[index] = gDic[t][i];
        letterCombinationDFS(digits, index + 1);
    }
}

void findItineDFS(const string &curr) {
    while (gvfindItine.count(curr) && gvfindItine[curr].size() > 0) {
        string tmp = gvfindItine[curr].top();
        gvfindItine[curr].pop();
        findItineDFS(move(tmp));
    }
    gSTK.emplace_back(curr);
}

int winnerSum(const vector<int> &nums, int L, int R) {
    int sum = 0;
    for (int i = L; i <= R; i++) {
        sum += nums[i - 1];
    }
    return sum;
}

int winnerDFS(int L, int R, const vector<int> &nums) {
    if (gWinnerDPArr[L][R] != -1) {
        return gWinnerDPArr[L][R];    // 已经计算过
    }
    if (L == R) {
        return gWinnerDPArr[L][R] = nums[L - 1];
    }
    return gWinnerDPArr[L][R] = winnerSum(nums, L, R) - min(winnerDFS(L + 1, R, nums), winnerDFS(L, R - 1, nums));
}

int sumNumDFS(TreeNode *root, int preSum) {
    if (root == nullptr) {
        return 0;
    }
    int sum = preSum * 10 + root->val;
    if (root->left == nullptr && root->right == nullptr) {
        return sum;
    } else {
        return sumNumDFS(root->left, sum) + sumNumDFS(root->right, sum);
    }
}

int n_queen_backtrack(int n, int row, unordered_set<int> &columns, unordered_set<int> &diagonals1,
                      unordered_set<int> &diagonals2) {
    if (row == n) {
        return 1;
    } else {
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (columns.find(i) != columns.end()) {
                continue;
            }
            int diagonal1 = row - i;
            if (diagonals1.find(diagonal1) != diagonals1.end()) {
                continue;
            }
            int diagonal2 = row + i;
            if (diagonals2.find(diagonal2) != diagonals2.end()) {
                continue;
            }
            columns.insert(i);
            diagonals1.insert(diagonal1);
            diagonals2.insert(diagonal2);
            count += n_queen_backtrack(n, row + 1, columns, diagonals1, diagonals2);
            columns.erase(i);
            diagonals1.erase(diagonal1);
            diagonals2.erase(diagonal2);
        }
        return count;
    }
}

int get_list_length(ListNode *head) {    // 获取链表的长度
    int len = 0;
    while (head) {
        len++;
        head = head->next;
    }
    return len;
}

void help_quick_sort(vector<int> &arr, int l, int r) {     // 快速排序
    if (l < r) {
        int i = l, j = r, save = arr[l];
        while (i < j) {
            while (i < j && arr[j] > save) {
                j--;
            }
            if (i < j) {
                arr[i] = arr[j];
                i++;
            }
            while (i < j && arr[i] <= arr[j]) {    /// 从左往右扫描，找到比轴点大的放右边
                i++;
            }
            if (i < j) {
                arr[j] = arr[i];
            }
        }
        arr[i] = save;        /// 还原轴点值
        help_quick_sort(arr, l, i - 1);
        help_quick_sort(arr, i + 1, r);
    }
}

bool isValid(vector<string> &board, int row, int col) {
    int n = board.size();
    //检查同列
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 'Q') {
            return false;
        }
    }
    //右上
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
        if (board[i][j] == 'Q') {
            return false;
        }
    }
    //左上
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 'Q') {
            return false;
        }
    }
    return true;
}

void nQueensBacktrack(vector<string> &board, int row, vector<vector<string>> &res) {
    if (row == board.size()) {
        res.emplace_back(board);
        return;
    }

    int n = board[row].size();
    for (int col = 0; col < n; ++col) {
        if (!isValid(board, row, col)) {
            continue;
        }
        board[row][col] = 'Q';
        nQueensBacktrack(board, row + 1, res);
        board[row][col] = '.';
    }
}

void buildTreePath(TreeNode *&root, string s, vector<string> &path) {
    if (root != nullptr) {
        s += to_string(root->val);
        if (root->left == nullptr && root->right == nullptr) {
            path.push_back(s);
        } else {
            s += "->";
            buildTreePath(root->left, s, path);
            buildTreePath(root->right, s, path);
        }
    }
}

ListNode *helpFuncMergeList(ListNode *l1, ListNode *l2) {
    ListNode *dummyNode = new ListNode(0);
    ListNode *tail = dummyNode;
    while (l1 != nullptr && l2 != nullptr) {
        if (l1->val <= l2->val) {
            tail->next = l1;
            l1 = l1->next;
            tail = tail->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
            tail = tail->next;
        }
        while (l1 != nullptr) {
            tail->next = l1;
            l1 = l1->next;
            tail = tail->next;
        }
        while (l2 != nullptr) {
            tail->next = l2;
            l2 = l2->next;
            tail = tail->next;
        }
    }
    return dummyNode->next;
}

ListNode *helpFuncMergeSort(ListNode *head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    ListNode *fastNode = head->next;
    ListNode *slowNode = head;
    while (fastNode != nullptr && fastNode->next != nullptr) {
        fastNode = fastNode->next->next;
        slowNode = slowNode->next;
    }
    // Slow 是前半部分L1的最后一个结点, 它的next 一定要设置为nullptr
    ListNode *l2 = slowNode->next;
    slowNode->next = nullptr;
    head = helpFuncMergeSort(head);
    l2 = helpFuncMergeSort(l2);
    return helpFuncMergeList(head, l2);
}

bool helpFuncExists(TreeNode *root, int level, int k) {
    int bits = 1 << (level - 1);
    TreeNode *node = root;
    while (node != nullptr && bits > 0) {
        if (!(bits & k)) {
            node = node->left;
        } else {
            node = node->right;
        }
        bits >>= 1;
    }
    return node != nullptr;
}

int reversePairsRecursive(vector<int> &nums, int left, int right) {
    if (left == right) {
        return 0;
    } else {
        int mid = (left + right) / 2;
        int n1 = reversePairsRecursive(nums, left, mid);
        int n2 = reversePairsRecursive(nums, mid + 1, right);
        int ret = n1 + n2;

        // 首先统计下标对的数量
        int i = left;
        int j = mid + 1;
        while (i <= mid) {
            while (j <= right && (long long) nums[i] > 2 * (long long) nums[j]) j++;
            ret += (j - mid - 1);
            i++;
        }

        // 随后合并两个排序数组
        vector<int> sorted(right - left + 1);
        int p1 = left, p2 = mid + 1;
        int p = 0;
        while (p1 <= mid || p2 <= right) {
            if (p1 > mid) {
                sorted[p++] = nums[p2++];
            } else if (p2 > right) {
                sorted[p++] = nums[p1++];
            } else {
                if (nums[p1] < nums[p2]) {
                    sorted[p++] = nums[p1++];
                } else {
                    sorted[p++] = nums[p2++];
                }
            }
        }
        for (int i = 0; i < sorted.size(); i++) {
            nums[left + i] = sorted[i];
        }
        return ret;
    }
}

bool isPrimer(int n) {
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

vector<int> topSort(vector<int> &deg, vector<vector<int>> &graph, vector<int> &items) {
    queue<int> q;
    for (auto item:items)
        if (deg[item] == 0) q.push(item);
    vector<int> res;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        res.emplace_back(u);
        for (auto &v:graph[u])
            if (--deg[v] == 0) q.push(v);
    }
    return res.size() == items.size() ? res : vector<int>{};
}

int find_func(vector<int> &parent, int index) { // findRedundantConnection - 并查集
    if (parent[index] != index) {
        parent[index] = find_func(parent, parent[index]);
    }
    return parent[index];
}

void union_func(vector<int> &parent, int index01, int index02) {
    parent[find_func(parent, index01)] = find_func(parent, index02);
}

void backTrack_subsets(vector<vector<int>> &res, vector<int> &tmp, vector<int> &nums, int index) {
    res.push_back(tmp);
    for (int i = index; i < nums.size(); i++) {
        tmp.push_back(nums[i]);
        backTrack_subsets(res, tmp, nums, i + 1);
        tmp.pop_back();
    }
}

TreeNode *backTrack_buildTree(vector<int>::iterator ib, vector<int>::iterator ie, vector<int>::iterator pb,
                              vector<int>::iterator pe) {
    // 左闭右开
    if (ib == ie) return nullptr;
    vector<int>::iterator pe1 = pe - 1;
    TreeNode *tree = new TreeNode(*pe1);
    auto pos = find(ib, ie, *pe1);
    tree->left = backTrack_buildTree(ib, pos, pb, pb + (pos - ib));
    tree->right = backTrack_buildTree(pos + 1, ie, pb + (pos - ib), pe1);
    return tree;
}

void dfs_permuteUnique(vector<int> &nums, int level, vector<vector<int>> &ans, vector<bool> &used, vector<int> &path) {
    if (level == nums.size()) {
        ans.push_back(path);
        return;
    }
    for (int i = 0; i < nums.size(); i++) {
        if (used[i] || (i > 0 && nums[i] == nums[i - 1] && !used[i - 1])) continue;
        used[i] = true;
        path.push_back(nums[i]);
        dfs_permuteUnique(nums, level + 1, ans, used, path);
        path.pop_back();
        used[i] = false;
    }
}

void backTrack_combine(vector<vector<int>> &res, vector<int> &path, int pos, int num, int n, int k) {
    if (pos == k) {
        res.push_back(path);
        return;
    }
    for (int i = num; i <= n - (k - pos - 1); i++) {
        path[pos] = i;
        backTrack_combine(res, path, pos + 1, i + 1, n, k);
    }
}

void backTrack_subsetsWithDup(vector<int> &nums, int startIndex, vector<bool> &used) {
    vvRes.push_back(vPath);
    for (int i = startIndex; i < nums.size(); i++) {
        if (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == false) continue;
        vPath.push_back(nums[i]);
        used[i] = true;
        backTrack_subsetsWithDup(nums, i + 1, used);
        vPath.pop_back();
        used[i] = false;
    }
}

void inorder_minDiffInBST(TreeNode *root, TreeNode *&pre, int &res) {
    if (root == nullptr) return;
    inorder_minDiffInBST(root->left, pre, res);
    if (pre != nullptr) res = min(res, root->val - pre->val);
    pre = root;
    inorder_minDiffInBST(root->right, pre, res);
}

void increasingBST_func(TreeNode *root, TreeNode *&parentHead, TreeNode *preHead) {
    if (!root) return;
    if (root->left) increasingBST_func(root->left, parentHead, preHead);
    if (root) {
        TreeNode *tmpNode = new TreeNode(root->val);
        parentHead->right = tmpNode;
        parentHead = parentHead->right;
    }
    if (root->right) increasingBST_func(root->right, parentHead, preHead);
}

bool canMake_func(vector<int> &bloomDay, int days, int m, int k) {
    int bouquets = 0;
    int flowers = 0;
    int lengths = bloomDay.size();
    for (int i = 0; i < lengths && bouquets < m; i++) {
        if (bloomDay[i] <= days) {  // 花开时间小于已经经过的时间，花已开
            flowers++;
            if (flowers == k) {
                bouquets++;
                flowers = 0;
            }
        } else flowers = 0; // 要求相邻
    }
    return bouquets >= m;
}

void traverseTree_func(TreeNode *&root, vector<int> &leafs) {
    if (root == nullptr) return;
    traverseTree_func(root->left, leafs);
    if (root->left == nullptr && root->right == nullptr) leafs.push_back(root->val);
    traverseTree_func(root->right, leafs);
}

///// ================================== HELP CLASS ==================================
class Djset {
public:
    vector<int> parent;
    vector<int> rank;

    Djset(int n) {
        for (int i = 0; i < n; i++) {
            parent.push_back(i);
            rank.push_back(0);
        }
    }

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    void merge(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx != ry) {
            if (rank[rx] < rank[ry]) swap(rx, ry);
            parent[ry] = rx;
            if (rank[rx] == rank[ry]) rank[rx] += 1;
        }
    }
};

// 并查集的类02
class DisjointSetUnion {
private:
    unordered_map<int, int> f, rank;
public:
    int find(int x) {
        if (!f.count(x)) {
            f[x] = x;
            rank[x] = 1;
        }
        return f[x] == x ? x : f[x] = find(f[x]);
    }

    void unionSet(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx == fy) return;
        if (rank[fx] < rank[fy]) {
            swap(fx, fy);
        }
        rank[fx] += rank[fy];
        f[fy] = fx;
    }

    int number_of_connected() {
        int num = 0;
        for (auto &_xfa:f) {
            if (_xfa.first == _xfa.second) {
                num++;
            }
        }
        return num;
    }
};

class UnionFind {
private:
    vector<int> f, sz;
public:
    UnionFind(int n) : f(n), sz(n) {
        for (int i = 0; i < n; i++) {
            f[i] = i;
            sz[i] = 1;
        }
    }

    int find(int x) {
        if (f[x] == x) return x;
        int new_f = find(f[x]);
        f[x] = new_f;
        return f[x];
    }

    void merge(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx == fy) return;
        f[fx] = fy;
        sz[fy] += sz[fx];
    }

    int size(int x) {
        return sz[find(x)];
    }
};

class UnionFind_accountsMerge {
public:
    vector<int> parent;

    UnionFind_accountsMerge(int n) {
        parent.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    void union_set(int index1, int index2) {
        parent[find(index2)] = find(index1);
    }

    int find(int index) {
        if (parent[index] != index) {
            parent[index] = find(parent[index]);
        }
        return parent[index];
    }
};

///// ================================== CLASS FUNC ==================================

int DailyCoding::numJewelsInStones(string J, string S) {
    if (J.empty() || S.empty()) {
        return 0;
    }
    unordered_map<char, int> hashMap;
    for (char &i : J) {
        hashMap[i]++;
    }
    int res = 0;
    for (char &i : S) {
        if (hashMap[i]) {
            res++;
        }
    }
    return res;
}

vector<int> DailyCoding::twoSum(vector<int> &nums, int target) {
    unordered_map<int, int> hashMap;
    for (int i = 0; i < nums.size(); i++) {
        auto iter = hashMap.find(target - nums[i]);
        if (iter != hashMap.end()) {
            return {iter->second, i};
        }
        hashMap[nums[i]] = i;
    }
    return {};
}

void DailyCoding::reverseString(vector<char> &s) {
    int left = 0, right = s.size() - 1;
    while (left < right) {
        swap(s[left], s[right]);
        left++, right--;
    }
}

char DailyCoding::findTheDifference(string s, string t) {
    vector<int> charHash(26, 0);
    for (int i = 0; i < s.length(); i++) {
        charHash[s[i] - 'a']++;
    }
    for (int i = 0; i < t.length(); i++) {
        charHash[t[i] - 'a'];
    }
    for (int i = 0; i < charHash.size(); i++) {
        if (charHash[i] == 1) {
            return (char) ('a' + charHash[i]);
        }
    }
    return 'a';
}

bool DailyCoding::hasCycle(ListNode *head) {
    if (head == nullptr) {
        return false;
    }
    ListNode *fast = head, *slow = head;
    while (fast->next && slow->next) {
        if (fast->next->next == nullptr) {
            return false;
        } else {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow) {
                return true;
            }
        }
    }
    return false;
}

bool DailyCoding::canPartition(vector<int> &nums) {
    int n = nums.size();
    if (n < 2) {
        return false;
    }
    int sum = accumulate(nums.begin(), nums.end(), 0);
    int maxNum = *max_element(nums.begin(), nums.end());
    if (sum & 1) {
        return false;
    }
    int target = sum / 2;
    if (maxNum > target) {
        return false;
    }
    vector<vector<int>> dp(n, vector<int>(target + 1, 0));
    for (int i = 0; i < n; i++) {
        dp[i][0] = true;
    }
    dp[0][nums[0]] = true;
    for (int i = 1; i < n; i++) {
        int num = nums[i];
        for (int j = 1; j <= target; j++) {
            if (j >= num) {
                dp[i][j] = dp[i - 1][j] | dp[i - 1][j - num];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    return dp[n - 1][target];
}

int DailyCoding::getMinimumDifference(TreeNode *root) {
    if (root == nullptr || (root->left == nullptr && root->right == nullptr)) {
        return 0;
    }
    vector<int> allRes;
    queue<TreeNode *> qNodes;
    qNodes.push(root);
    while (!qNodes.empty()) {
        TreeNode *currNode = qNodes.front();
        qNodes.pop();
        allRes.push_back(currNode->val);
        if (currNode->left != nullptr) {
            qNodes.push(currNode->left);
        }
        if (currNode->right != nullptr) {
            qNodes.push(currNode->right);
        }
    }
    sort(allRes.begin(), allRes.end());
    int res = 99999;
    for (int i = 0; i < allRes.size() - 1; i++) {
        //res = min(res, __abs(allRes[i] - allRes[i + 1]));
    }
    return res;
}

ListNode *DailyCoding::swapPairs(ListNode *head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    ListNode *preNode = new ListNode(0);
    preNode->next = head;
    ListNode *tmpNode = preNode;
    while (tmpNode->next != nullptr && tmpNode->next->next != nullptr) {
        ListNode *node1 = tmpNode->next;
        ListNode *node2 = tmpNode->next->next;
        tmpNode->next = node2;
        node1->next = node2->next;
        node2->next = node1;
        tmpNode = node1;    // 此时 node1 在前
    }
    return preNode->next;
}

vector<string> DailyCoding::commonChars(vector<string> &A) {
    if (A.empty()) {
        return {};
    }
    if (A.size() == 1) {
        return A;
    }
    vector<vector<int>> allHash(A.size(), vector<int>(26, 0));
    for (int i = 0; i < A.size(); i++) {
        string currStr = A[i];
        for (int j = 0; j < currStr.size(); j++) {
            int hash = currStr[j] - 'a';
            allHash[i][hash]++;
        }
    }
    vector<string> resVec;
    for (int i = 0; i < 26; i++) {
        char c = (char) ('a' + i);
        string s(c, 1);
        int minCount = 99999;
        bool flag = true;    // 检查是否这个字符至少每个出现一次
        for (int j = 0; j < allHash.size(); j++) {
            if (allHash[j][i] == 0) {
                flag = false;
                break;
            }
            minCount = min(minCount, allHash[j][i]);
        }
        if (flag) {
            for (int k = 0; k < minCount; k++) {
                resVec.push_back(s);
            }
        }
    }
    return resVec;
}

Node *DailyCoding::connect(Node *root) {
    if (root == nullptr) {
        return root;
    }
    queue<Node *> qNodes;
    qNodes.push(root);
    while (!qNodes.empty()) {
        int currSize = qNodes.size();
        for (int i = 0; i < currSize; i++) {
            Node *currNode = qNodes.front();
            qNodes.pop();
            if (i < currSize - 1) {
                currNode->next = qNodes.front();
            }
            if (currNode->left != nullptr) {
                qNodes.push(currNode->left);
            }
            if (currNode->right != nullptr) {
                qNodes.push(currNode->right);
            }
        }
    }
    return root;
}

vector<int> DailyCoding::sortedSquares(vector<int> &A) {
    if (A.empty()) {
        return A;
    }
    for (int i = 0; i < A.size(); i++) {
        A[i] *= A[i];
    }
    sort(A.begin(), A.end());
    return A;
}

ListNode *DailyCoding::removeNthFromEnd2(ListNode *head, int n) {
    if (head == nullptr) {
        return head;
    }
    int len = 0;
    ListNode *phead = head;
    ListNode *dummy = new ListNode(0);
    dummy->next = head;
    while (phead) {
        len++;
        phead = phead->next;
    }
    len -= n;
    phead = dummy;
    while (len) {
        len--;
        phead = phead->next;
    }
    phead->next = phead->next->next;
    return dummy->next;
}

bool DailyCoding::backspaceCompare(string S, string T) {
    if (S.empty() && T.empty()) {
        return true;
    }
    stack<char> sS, sT;
    for (int i = 0; i < S.length(); i++) {
        if (S[i] == '#') {
            if (!sS.empty()) {
                sS.pop();
            }
        } else {
            sS.push(S[i]);
        }
    }
    for (int i = 0; i < T.length(); i++) {
        if (T[i] == '#') {
            if (sT.empty()) {
                sT.pop();
            }
        } else {
            sT.push(T[i]);
        }
    }
    if (sS.size() != sT.size()) {
        return false;
    }
    while (!sS.empty() && !sT.empty()) {
        if (sS.top() != sT.top()) {
            return false;
        }
        sS.pop();
        sT.pop();
    }
    return true;
    // return sS == sT;
}

void DailyCoding::reorderList(ListNode *head) {
    if (head == nullptr || head->next == nullptr) {
        return;
    }
    vector<ListNode *> vAllNodes;    // 保存所有的节点地址
    ListNode *tmp = head;
    while (tmp != nullptr) {
        vAllNodes.push_back(tmp);
        tmp = tmp->next;
    }
    int le_pos = 0, rg_pos = vAllNodes.size() - 1;
    while (le_pos < rg_pos) {
        vAllNodes[le_pos]->next = vAllNodes[rg_pos];
        le_pos++;
        if (le_pos == rg_pos) {
            break;
        }
        vAllNodes[rg_pos]->next = vAllNodes[le_pos];
        rg_pos--;
    }
    vAllNodes[le_pos]->next = nullptr;
}

bool DailyCoding::isLongPressedName(string name, string typed) {
    int i = 0, j = 0;
    while (j < typed.length()) {
        if (i < name.length() && name[i] == typed[j]) {
            i++;
            j++;
        } else if (j > 0 && typed[j] == typed[j - 1]) {
            j++;
        } else {
            return false;
        }
    }
    return i == name.length();
}

vector<int> DailyCoding::partitionLabels(string S) {
    if (S.empty()) {
        return {};
    }
    /// 建立哈希表
    vector<int> hash(26, -1);
    for (int i = 0; i < S.size(); i++) {
        hash[S[i] - 'a'] = i;    /// 保留每个字母的最后的出现位置
    }
    vector<int> answer;
    int pos = 0;
    while (pos < S.size()) {
        int curr_last_pos = hash[S[pos] - 'a'];
        for (int i = pos + 1; i < curr_last_pos; i++) {        /// curr_last_pos随时可能更新
            curr_last_pos = max(curr_last_pos, hash[S[i] - 'a']);
        }
        answer.push_back(curr_last_pos - pos + 1);
        pos = curr_last_pos + 1;
    }
    return answer;
}

bool DailyCoding::isPalindrome(ListNode *head) {
    if (head == nullptr || head->next == nullptr) {
        return true;
    }
    vector<int> getNumbers;
    while (head) {
        getNumbers.push_back(head->val);
        head = head->next;
    }
    int l = 0, r = getNumbers.size() - 1;
    while (l < r) {
        if (getNumbers[l] != getNumbers[r]) {
            return false;
        }
        l++, r--;
    }
    return true;
}

int DailyCoding::videoStitching(vector<vector<int>> &clips, int T) {
    vector<int> dp(T + 1, 99999 - 1);
    dp[0] = 0;
    for (int i = 1; i <= T; i++) {
        for (auto &it : clips) {
            if (it[0] < i && i <= it[1]) {
                dp[i] = min(dp[i], dp[it[0]] + 1);
            }
        }
    }
    return dp[T] == 99999 - 1 ? -1 : dp[T];
}

int DailyCoding::longestMountain(vector<int> &A) {
    int n = A.size();
    if (!n) {
        return 0;
    }
    vector<int> left(n);
    for (int i = 1; i < n; ++i) {
        left[i] = (A[i - 1] < A[i] ? left[i - 1] + 1 : 0);
    }
    vector<int> right(n);
    for (int i = n - 2; i >= 0; --i) {
        right[i] = (A[i + 1] < A[i] ? right[i + 1] + 1 : 0);
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (left[i] > 0 && right[i] > 0) {
            ans = max(ans, left[i] + right[i] + 1);
        }
    }
    return ans;
}

vector<int> DailyCoding::smallerNumbersThanCurrent(vector<int> &nums) {
    vector<int> cnt(101, 0);
    int n = nums.size();
    for (int i = 0; i < n; i++) {
        cnt[nums[i]]++;
    }
    for (int i = 1; i <= 100; i++) {
        cnt[i] += cnt[i - 1];
    }
    vector<int> ret;
    for (int i = 0; i < n; i++) {
        ret.push_back(nums[i] == 0 ? 0 : cnt[nums[i] - 1]);
    }
    return ret;
}

vector<int> DailyCoding::preorderTraversal(TreeNode *root) {
    if (root == nullptr) {
        return {};
    }
    vector<int> res;
    stack<TreeNode *> sNodes;
    sNodes.push(root);
    while (!sNodes.empty()) {
        TreeNode *curr = sNodes.top();
        sNodes.pop();
        res.push_back(curr->val);
        if (curr->right != nullptr) {
            sNodes.push(curr->right);
        }
        if (curr->left != nullptr) {
            sNodes.push(curr->left);
        }
    }
    return res;
}

bool DailyCoding::uniqueOccurrences(vector<int> &arr) {
    if (arr.empty()) {
        return true;
    }
    int maxNum = *max_element(arr.begin(), arr.end());
    vector<int> hash(maxNum + 1, 0);
    for (int i = 0; i < arr.size(); i++) {
        hash[arr[i]]++;
    }
    maxNum = *max_element(hash.begin(), hash.end());
    vector<int> hashhash(maxNum + 1, 0);
    for (int i : hash) {
        hashhash[i]++;
    }
    for (int i : hashhash) {
        if (i > 1) {
            return false;
        }
    }
    return true;
}

int DailyCoding::sumNumbers2(TreeNode *root) {
    if (root == nullptr) {
        return 0;
    }
    int res = 0;
    queue<TreeNode *> qNodes;
    queue<int> qNums;
    qNodes.push(root);
    qNums.push(root->val);
    while (!qNodes.empty()) {
        TreeNode *cNode = qNodes.front();
        qNodes.pop();
        int cNum = qNums.front();
        qNums.pop();
        if (cNode->left == nullptr && cNode->right == nullptr) {
            res += cNum;
        } else {
            if (cNode->left != nullptr) {
                qNodes.push(cNode->left);
                qNums.push(cNode->left->val + cNum * 10);
            }
            if (cNode->right != nullptr) {
                qNodes.push(cNode->right);
                qNums.push(cNode->right->val + cNum * 10);
            }
        }
    }
    return res;
}

int DailyCoding::minDepth(TreeNode *root) {
    if (root == nullptr) {
        return 0;
    }
    int depRes = 1;
    queue<TreeNode *> qNodes;
    qNodes.push(root);
    while (!qNodes.empty()) {
        int currSize = qNodes.size();
        depRes++;
        for (int i = 0; i < currSize; i++) {
            TreeNode *tmpNode = qNodes.front();
            qNodes.pop();
            if (tmpNode->left != nullptr) {
                qNodes.push(tmpNode->left);
            }
            if (tmpNode->right != nullptr) {
                qNodes.push(tmpNode->right);
            }
            if (tmpNode->left == nullptr && tmpNode->right == nullptr) {
                return depRes;
            }
        }
    }
    return depRes;
}

bool DailyCoding::judgeCircle(string moves) {
    if (moves.empty()) {
        return true;
    }
    stack<int> leftRight;
    stack<int> upDown;
    for (int i = 0; i < moves.size(); i++) {
        switch (moves[i]) {
            case 'R':
                leftRight.push(1);
                break;
            case 'L':
                leftRight.push(-1);
                break;
            case 'U':
                upDown.push(1);
                break;
            case 'P':
                upDown.push(-1);
                break;

            default:
                break;
        }
    }
    int tmp01 = 0, tmp02 = 0;
    while (!leftRight.empty()) {
        tmp01 += leftRight.top();
        leftRight.pop();
    }
    while (!upDown.empty()) {
        tmp02 += upDown.top();
        upDown.pop();
    }
    return tmp01 == 0 && tmp02 == 0;
}

string DailyCoding::shortestPalindrome(string s) {
    int n = s.length();
    vector<int> fail(n, -1);
    for (int i = 1; i < n; i++) {
        int j = fail[i - 1];
        while (j != -1 && s[j + 1] != s[i]) {
            j = fail[j];
        }
        if (s[j + 1] == s[i]) {
            fail[i] = j + 1;
        }
    }
    int best = -1;
    for (int i = n - 1; i >= 0; i--) {
        while (best != -1 && s[best + 1] != s[i]) {
            best = fail[best];
        }
        if (s[best + 1] == s[i]) {
            ++best;
        }
    }
    string add = (best == n - 1 ? "" : s.substr(best + 1, n));
    std::reverse(add.begin(), add.end());

    return add + s;
}

string DailyCoding::reverseWords(string s) {
    string resStr;
    string tmp;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != ' ') {
            tmp += s[i];
        } else {
            std::reverse(tmp.begin(), tmp.end());
            resStr += tmp;
            resStr += ' ';
            tmp = "";
        }
    }
    if (!tmp.empty()) {
        std::reverse(tmp.begin(), tmp.end());
        resStr += tmp;
    }
    return resStr;
}

bool DailyCoding::canVisitAllRooms(vector<vector<int>> &rooms) {
    vector<bool> flagRoom(rooms.size(), false);
    for (int i = 0; i < rooms.size(); i++) {
        for (auto _key : rooms[i]) {
            flagRoom[_key] = true;
        }
    }
    for (bool _flag : flagRoom) {
        if (!_flag) {
            return _flag;
        }
    }
    return true;
}

bool DailyCoding::PredictTheWinner(vector<int> &nums) {
    if (nums.size() < 3) {
        return true;
    }
    int n = nums.size();
    // dp[i][j]代表在i,j范围内，先手比后手拿到最好的多多少
    vector<vector<int>> dpArr(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        //当i==j时，取得的在i-j范围内，最大值即为 nums[i]
        dpArr[i][i] = nums[i];
    }
    for (int len = 1; len < n; len++) {
        for (int i = 0, j = len; j < n; i++, j++) {
            dpArr[i][j] = max(nums[i] - dpArr[i + 1][j], nums[j] - dpArr[i][j - 1]);
        }
    }
    //返回dp[0][n-1],因为开始是0，最后一次是n-1,代表在0~n-1范围内先手是否能比后手多
    return dpArr[0][n - 1] >= 0;
}

bool DailyCoding::isNumber(string s) {
    int n = s.size();
    int index = -1;
    bool hasDot = false, hasE = false, hasOp = false, hasNum = false;
    while (index < n && s[++index] == ' ');        /// 跳过前面的空格
    while (index < n) {
        if ('0' <= s[index] && s[index] <= '9') {
            hasNum = true;
        } else if (s[index] == 'e' || s[index] == 'E') {
            if (hasE || !hasNum) return false;
            hasE = true;
            hasOp = false;
            hasDot = false;
            hasNum = false;
        } else if (s[index] == '+' || s[index] == '-') {
            if (hasOp || hasNum || hasDot) return false;
            hasOp = true;
        } else if (s[index] == '.') {
            if (hasDot || hasE) return false;
            hasDot = true;
        } else if (s[index] == ' ') {
            break;
        } else {
            return false;
        }
        ++index;
    }
    while (index < n && s[++index] == ' ');
    return hasNum && index == n;
}

vector<vector<int>> DailyCoding::levelOrderBottom(TreeNode *root) {
    if (root == nullptr) {
        return {};
    }
    queue<TreeNode *> qNodes;
    qNodes.push(root);
    vector<vector<int>> resVec;
    while (!qNodes.empty()) {
        int size = qNodes.size();
        vector<int> tmpVec;
        for (int i = 0; i < size; i++) {
            TreeNode *tmpCurr = qNodes.front();
            qNodes.pop();
            int val = tmpCurr->val;
            tmpVec.push_back(val);
            if (tmpCurr->left != nullptr) {
                qNodes.push(tmpCurr->left);
            }
            if (tmpCurr->right != nullptr) {
                qNodes.push(tmpCurr->right);
            }
        }
        resVec.push_back(tmpVec);
    }
    reverse(resVec.begin(), resVec.end());
    return resVec;
}

vector<int> DailyCoding::topKFrequent(vector<int> &nums, int k) {
    unordered_map<int, int> freq;
    for (int i:nums) freq[i]++;     // 先统计每个元素出现的个数

    list<int> buckets[nums.size() + 1];
    for (auto pos = freq.begin(); pos != freq.end(); pos++) buckets[pos->second].push_back(pos->first);
    vector<int> res(k);
    int cnt = 0;
    for (int i = nums.size(); i > 0; i--) {
        for (auto num:buckets[i]) {
            res[cnt++] = num;
            if (cnt == k) return res;
        }
    }
    return res;
}

int DailyCoding::sumOfLeftLeaves(TreeNode *root) {
    int res = 0;
    if (root == nullptr) {
        return res;
    }
    stack<TreeNode *> sNodes;
    sNodes.push(root);
    while (!sNodes.empty()) {
        TreeNode *currNode = sNodes.top();
        sNodes.pop();
        if (currNode->left != nullptr && currNode->left->left == nullptr && currNode->left->right == nullptr) {
            res += currNode->left->val;
        }
        if (currNode->left != nullptr) {
            sNodes.push(currNode->left);
        }
        if (currNode->right != nullptr) {
            sNodes.push(currNode->right);
        }
    }
    return res;
}

int DailyCoding::sumOfLeftLeaves2(TreeNode *root) {
    if (root == nullptr) {
        return 0;
    }
    int res = 0;
    if (root->left != nullptr && root->left->left == nullptr && root->left->right == nullptr) {
        res += root->left->val;
    }
    return res + sumOfLeftLeaves2(root->left) + sumOfLeftLeaves2(root->right);
}

TreeNode *DailyCoding::buildTree(vector<int> &inorder, vector<int> &postorder) {
    return backTrack_buildTree(inorder.begin(), inorder.end(), postorder.begin(), postorder.end());
}

vector<vector<int>> DailyCoding::findSubsequences(vector<int> &nums) {
    vector<vector<int>> res;
    vector<int> subseq;
    findSubsequencesbackTracking(nums, res, subseq, 0);
    return res;
}

vector<string> DailyCoding::letterCombinations(string digits) {
    if (digits.empty()) {
        return gAns;
    }
    gTemp.resize(digits.size());
    letterCombinationDFS(digits, 0);
    return gAns;
}

vector<string> DailyCoding::findItinerary(vector<vector<string>> &tickets) {
    for (auto &it : tickets) {
        gvfindItine[it[0]].emplace(it[1]);
    }
    findItineDFS("JFK");

    reverse(gSTK.begin(), gSTK.end());
    return gSTK;
}

bool DailyCoding::PredictTheWinner2(vector<int> &nums) {
    return winnerSum(nums, 1, nums.size()) <= (winnerDFS(1, nums.size(), nums) * 2);
}

int DailyCoding::sumNumbers(TreeNode *root) {
    return sumNumDFS(root, 0);
}

int DailyCoding::totalNQueens(int n) {
    unordered_set<int> columns, diagonals1, diagonals2;
    return n_queen_backtrack(n, 0, columns, diagonals1, diagonals2);
}

ListNode *DailyCoding::removeNthFromEnd(ListNode *head, int n) {
    if (head == nullptr) {
        return head;
    }
    ListNode *dummy = new ListNode(0, head);
    int length = get_list_length(head);
    ListNode *curr = dummy;
    for (int i = 1; i < length - n + 1; i++) {
        curr = curr->next;
    }
    curr->next = curr->next->next;
    ListNode *ans = dummy->next;
    delete dummy;
    return ans;
}

void DailyCoding::sortColors(vector<int> &nums) {
    // sort(nums.begin(), nums.end());
    if (nums.size() < 2) {
        return;
    }
    help_quick_sort(nums, 0, nums.size() - 1);
}

vector<vector<string>> DailyCoding::solveNQueens(int n) {
    /// 经典的回溯算法
    vector<vector<string>> res;
    vector<string> board(n, string(n, '.'));
    nQueensBacktrack(board, 0, res);
    return res;
}

vector<vector<int>> DailyCoding::combine(int n, int k) {
    vector<vector<int>> res;
    vector<int> path(k, 0);
    int pos = 0, num = 1;
    backTrack_combine(res, path, pos, num, n, k);
    return res;
}

vector<string> DailyCoding::binaryTreePaths(TreeNode *root) {
    vector<string> res;
    if (root == nullptr) {
        return res;
    }
    queue<TreeNode *> qNodes;
    queue<string> qPath;
    qNodes.push(root);
    qPath.push(to_string(root->val));
    while (!qNodes.empty()) {
        TreeNode *currNode = qNodes.front();
        string currPath = qPath.front();
        qNodes.pop();
        qPath.pop();
        if (currNode->left == nullptr && currNode->right == nullptr) {
            res.push_back(currPath);
        }
        if (currNode->left != nullptr) {
            qNodes.push(currNode->left);
            qPath.push(currPath + "->" + to_string(currNode->left->val));
        }
        if (currNode->right != nullptr) {
            qNodes.push(currNode->right);
            qPath.push(currPath + "->" + to_string(currNode->right->val));
        }
    }
    return res;
}

bool DailyCoding::validMountainArray(vector<int> &A) {
    if (A.size() < 3) {
        return false;
    }
    int prePos = 0, behPos = A.size() - 1;
    while (prePos + 1 < A.size() && A[prePos] < A[prePos + 1]) {
        prePos++;
    }
    while (behPos > 0 && A[behPos - 1] > A[behPos]) {
        behPos--;
    }
    return prePos > 0 && behPos < A.size() - 1 && prePos == behPos;
}

vector<int> DailyCoding::sortByBits(vector<int> &arr) {
    vector<int> bits(10001, 0);
    for (int i = 1; i <= 10000; i++) {
        bits[i] = bits[i >> 1] + (i & 1);   /// *****
    }
    sort(arr.begin(), arr.end(), [&](int x, int y) {
        if (bits[x] < bits[y]) {
            return true;
        }
        if (bits[x] > bits[y]) {
            return false;
        }
        return x < y;
    });
    return arr;
}

vector<int> DailyCoding::relativeSortArray(vector<int> &arr1, vector<int> &arr2) {
    vector<int> vRes;

    for (int i = 0; i < arr2.size(); i++) {
        int currNum = arr2[i];
        vector<int>::iterator pos = arr1.begin();
        while (pos < arr1.end()) {
            if (*pos == currNum) {
                vRes.push_back(currNum);
                arr1.erase(pos);
            } else {
                pos++;
            }
        }
    }
    if (!arr1.empty()) {
        sort(arr1.begin(), arr1.end());
        for (int ii:arr1) {
            vRes.push_back(ii);
        }
    }
    return vRes;
}

string DailyCoding::removeKdigits(string num, int k) {
    vector<char> stk;
    for (char &digit:num) {
        while (stk.size() > 0 && stk.back() > digit && k) {
            stk.pop_back();
            k -= 1;
        }
        stk.push_back(digit);
    }
    while (k > 0) {
        stk.pop_back();
        k--;
    }
    string res = "";
    bool isLoadingZero = true;
    for (char digit:stk) {
        if (isLoadingZero && digit == '0') {
            continue;
        }
        isLoadingZero = false;
        res += digit;
    }
    return res == "" ? "0" : res;
}

vector<vector<int>> DailyCoding::reconstructQueue(vector<vector<int>> &people) {
    if (people.empty()) {
        return {};
    }
    sort(people.begin(), people.end(),
         [](vector<int> &a, vector<int> &b) { return a[0] == b[0] ? a[1] < b[1] : a[0] > b[0]; });
    list<vector<int>> tmp;
    for (int i = 0; i < people.size(); i++) {
        auto pos = tmp.begin();
        advance(pos, people[i][1]);  //// 为了使得list可以随机访问
        tmp.insert(pos, people[i]);
    }
    return vector<vector<int>>(tmp.begin(), tmp.end());
}

vector<vector<int>> DailyCoding::allCellsDistOrder(int R, int C, int r0, int c0) {
    vector<vector<int>> vRes;
    vector<vector<bool>> isVisit(R, vector<bool>(C, false));
    vector<int> dx{0, 0, -1, 1};
    vector<int> dy{1, -1, 0, 0};
    queue<pair<int, int>> qCoords;
    qCoords.push(make_pair(r0, c0));
    while (!qCoords.empty()) {
        int currR = qCoords.front().first;
        int currC = qCoords.front().second;
        qCoords.pop();
        if (isVisit[currR][currC]) {
            continue;
        } else {
            vRes.push_back({currR, currC});
            isVisit[currR][currC] = true;

            for (int i = 0; i < 4; i++) {
                int moveR = dx[i] + currR;
                int moveC = dy[i] + currC;
                if (moveR < 0 || moveR >= R || moveC < 0 || moveC >= C) {
                    continue;
                } else {
                    qCoords.push(make_pair(moveR, moveC));
                }
            }
        }
    }
    return vRes;
}

ListNode *DailyCoding::oddEvenList(ListNode *head) {
    if (head == nullptr) {
        return head;
    }
    ListNode *evenHead = head->next;
    ListNode *odd = head;
    ListNode *even = evenHead;
    while (even != nullptr && even->next != nullptr) {
        odd->next = even->next;
        odd = odd->next;
        even->next = odd->next;
        even = even->next;
    }
    odd->next = evenHead;
    return head;
}

void DailyCoding::moveZeroes(vector<int> &nums) {
    if (nums.empty() || nums.size() == 1) {
        return;
    }
    int zeroCounts = 0;
    auto pos = nums.begin();
    while (pos != nums.end()) {
        if ((*pos) == 0) {
            zeroCounts++;
            nums.erase(pos);
        } else {
            pos++;
        }
    }
    while (zeroCounts) {
        nums.push_back(0);
        zeroCounts--;
    }
}

ListNode *DailyCoding::insertionSortList(ListNode *head) {
    if (head == nullptr) {
        return head;
    }
    ListNode *dummyHead = new ListNode(0);
    dummyHead->next = head;
    ListNode *lastSorted = head;
    ListNode *curr = head->next;
    while (curr != nullptr) {
        if (lastSorted->val <= curr->val) {
            lastSorted = lastSorted->next;
        } else {
            ListNode *prev = dummyHead;
            while (prev->next->val <= curr->val) {
                prev = prev->next;
            }
            lastSorted->next = curr->next;
            curr->next = prev->next;
            prev->next = curr;
        }
        curr = lastSorted->next;
    }
    return dummyHead->next;
}

ListNode *DailyCoding::sortList(ListNode *head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    return helpFuncMergeSort(head);
}

bool DailyCoding::isAnagram(string s, string t) {
    if (s.size() != t.size()) {
        return false;
    }
    vector<int> hashS(26, 0), hashT(26, 0);
    for (int i = 0; i < s.size(); i++) {
        int i_s = (int) s[i] - 'a';
        int i_t = (int) t[i] - 'a';
        hashS[i_s]++, hashT[i_t]++;
    }
    for (int i = 0; i < 26; i++) {
        if (hashS[i] != hashT[i]) {
            return false;
        }
    }
    return true;
}

int DailyCoding::findMinArrowShots(vector<vector<int>> &points) {
    if (points.empty()) {
        return 0;
    }
    sort(points.begin(), points.end(), [](vector<int> a, vector<int> b) { return a.back() < b.back(); });
    int pos = points[0][1];
    int res = 1;
    for (vector<int> &curr:points) {
        if (curr[0] > pos) {
            pos = curr[1];
            res++;
        }
    }
    return res;
}

int DailyCoding::countNodes(TreeNode *root) {
    if (root == nullptr) {
        return 0;
    }
    int level = 0;
    TreeNode *node = root;
    while (node->left != nullptr) {
        level++;
        node = node->left;
    }
    int low = 1 << level, high = (1 << (level + 1)) - 1;
    while (low < high) {
        int mid = (high - low + 1) / 2 + low;
        if (helpFuncExists(root, level, mid)) {
            low = mid;
        } else {
            high = mid - 1;
        }
    }
    return low;
}

string DailyCoding::sortString(string s) {
    vector<int> num(26);
    for (char &ch : s) {
        num[ch - 'a']++;
    }

    string ret;
    while (ret.length() < s.length()) {
        for (int i = 0; i < 26; i++) {
            if (num[i]) {
                ret.push_back(i + 'a');
                num[i]--;
            }
        }
        for (int i = 25; i >= 0; i--) {
            if (num[i]) {
                ret.push_back(i + 'a');
                num[i]--;
            }
        }
    }
    return ret;
}

int DailyCoding::maximumGap(vector<int> &nums) {
    if (nums.size() < 2) {
        return 0;
    }
    int exp = 1;
    vector<int> buff(nums.size());
    int maxVal = *max_element(nums.begin(), nums.end());
    while (maxVal >= exp) {
        vector<int> cnt(10);
        for (int i = 0; i < nums.size(); i++) {
            int digit = (nums[i] / exp) % 10;
            cnt[digit]++;
        }
        for (int i = 1; i < 10; i++) {
            cnt[i] += cnt[i - 1];
        }
        for (int i = nums.size() - 1; i >= 0; i--) {
            int digit = (nums[i] / exp) % 10;
            buff[cnt[digit] - 1] = nums[i];
            cnt[digit]--;
        }
        copy(buff.begin(), buff.end(), nums.begin());
        exp *= 10;
    }
    int res = 0;
    for (int i = 0; i < nums.size() - 1; i++) {
        res = max(res, nums[i + 1] - nums[i]);
    }
    return res;
}

int DailyCoding::fourSumCount(vector<int> &A, vector<int> &B, vector<int> &C, vector<int> &D) {
    unordered_map<int, int> hashMap;
    for (int i:A) {
        for (int j:B) {
            ++hashMap[i + j];
        }
    }
    int res = 0;
    for (int i:C) {
        for (int j:D) {
            res += hashMap[-i - j];
        }
    }
    return res;
}

int DailyCoding::reversePairs(vector<int> &nums) {
    if (nums.size() == 0) {
        return 0;
    }
    return reversePairsRecursive(nums, 0, nums.size() - 1);
}

int DailyCoding::largestPerimeter(vector<int> &A) {
    if (A.size() < 3) {
        return 0;
    }
    sort(A.begin(), A.end());
    for (int i = A.size() - 1; i >= 2; i--) {
        if (A[i - 2] + A[i - 1] > A[i]) {
            return A[i] + A[i - 1] + A[i - 2];
        }
    }
    return 0;
}

vector<int> DailyCoding::searchRange(vector<int> &nums, int target) {
    if (nums.empty()) {
        return {-1, -1};
    }
    vector<int> res{-1, -1};
    int left = 0, right = nums.size() - 1;
    while (left < nums.size()) {
        if (nums[left] == target) {
            res[0] = left;
            break;
        } else {
            left++;
        }
    }
    if (left == nums.size()) {
        return res;
    }
    while (right >= 0) {
        if (nums[right] == target) {
            res[1] = right;
            break;
        } else {
            right--;
        }
    }
    return res;
}

int DailyCoding::maxProfit02(vector<int> &prices) {
    int res = 0;
    for (int i = 1; i < prices.size(); i++) {
        if (prices[i] > prices[i - 1]) {
            res += (prices[i] - prices[i - 1]);
        }
    }
    return res;
}

vector<vector<int>> DailyCoding::insert(vector<vector<int>> &intervals, vector<int> &newInterval) {
    int left = newInterval[0];
    int right = newInterval[1];
    bool placed = false;
    vector<vector<int>> ans;
    for (const auto &interval: intervals) {
        if (interval[0] > right) {
            // 在插入区间的右侧且无交集
            if (!placed) {
                ans.push_back({left, right});
                placed = true;
            }
            ans.push_back(interval);
        } else if (interval[1] < left) {
            // 在插入区间的左侧且无交集
            ans.push_back(interval);
        } else {
            // 与插入区间有交集，计算它们的并集
            left = min(left, interval[0]);
            right = max(right, interval[1]);
        }
    }
    if (!placed) {
        ans.push_back({left, right});
    }
    return ans;
}

bool DailyCoding::isPossible(vector<int> &nums) {
    unordered_map<int, int> nc, tail;
    // 保存原数组中数字i的长度
    for (auto num : nums) {
        nc[num]++;
    }

    for (auto num : nums) {
        if (nc[num] == 0) {
            continue;
        } else if (nc[num] > 0 && tail[num - 1] > 0) {
            nc[num]--;
            tail[num - 1]--;
            tail[num]++;
        } else if (nc[num] > 0 && nc[num + 1] > 0 && nc[num + 2] > 0) {
            nc[num]--;
            nc[num + 1]--;
            nc[num + 2]--;
            tail[num + 2]++;
        } else {
            return false;
        }
    }
    return true;
}

int DailyCoding::countPrimes(int n) {
    int res = 0;
    for (int i = 2; i < n; i++) {
        res += isPrimer(i);
    }
    return res;
}

int DailyCoding::leastInterval(vector<char> &tasks, int n) {
    unordered_map<char, int> freq;
    for (char ch:tasks) {
        ++freq[ch];
    }
    // 获取最多的执行次数
    int maxExec = max_element(freq.begin(), freq.end(),
                              [](const pair<char, int> &u, const pair<char, int> &v) {
                                  return u.second < v.second;
                              })->second;
    // 具有最多执行次数的任务数量
    int maxCount = accumulate(freq.begin(), freq.end(), 0, [=](int acc, const pair<char, int> &u) {
        return acc + (u.second == maxExec);
    });
    return max((maxExec - 1) * (n + 1) + maxCount, static_cast<int>(tasks.size()));
}

vector<vector<int>> DailyCoding::generate(int numRows) {
    if (numRows < 1) {
        return {};
    }
    vector<vector<int>> res(numRows);
    for (int i = 0; i < numRows; i++) {
        res[i].resize(i + 1);
        res[i][0] = res[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            res[i][j] = res[i - 1][j] + res[i - 1][j - 1];
        }
    }
    return res;
}

int DailyCoding::matrixScore(vector<vector<int>> &A) {
    if (A.empty()) {
        return 0;
    }
    for (int i = 0; i < A.size(); i++) {
        if (A[i][0] == 0) {
            for (int j = 0; j < A[i].size(); j++) {
                A[i][j] = (A[i][j] == 0 ? 1 : 0);
            }
        }
    }
    for (int j = 0; j < A[0].size(); j++) {
        int col_zero_count = 0;
        for (int i = 0; i < A.size(); i++) {
            if (A[i][j] == 0) {
                col_zero_count++;
            }
        }
        if (col_zero_count > (A.size() / 2)) {  // 翻转该列
            for (int i = 0; i < A.size(); i++) {
                A[i][j] = (A[i][j] == 0 ? 1 : 0);
            }
        }
    }
    int res = 0;
    for (int i = 0; i < A.size(); i++) {
        int temp = 0;
        int k = A[i].size() - 1;
        for (int j = 0; j < A[i].size(); j++) {
            temp += (pow(2, k) * A[i][j]);
            k--;
        }
        res += temp;
    }
    return res;
}

int DailyCoding::uniquePaths(int m, int n) {
    if (m == 0 || n == 0) {
        return 0;
    }
    vector<vector<int>> dpArr(m, vector<int>(n, 0));
    for (int i = 0; i < m; i++) {
        dpArr[i][0] = 1;
    }
    for (int i = 1; i < n; i++) {
        dpArr[0][i] = 1;
    }
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dpArr[i][j] = dpArr[i][j - 1] + dpArr[i - 1][j];
        }
    }
    return dpArr[m - 1][n - 1];
}

bool DailyCoding::lemonadeChange(vector<int> &bills) {
    int five = 0, ten = 0;
    for (auto curr:bills) {
        if (curr == 5) {
            five++;
        } else if (curr == 10) {
            if (five < 1) {
                return false;
            }
            five--, ten++;
        } else {
            if (five > 0 && ten > 0) {
                five--, ten--;
            } else if (five > 3) {
                five -= 3;
            } else {
                return false;
            }
        }
    }
    return true;
}

int DailyCoding::wiggleMaxLength(vector<int> &nums) {
    int n = nums.size();
    if (n < 2) {
        return n;
    }
    vector<int> up(n), down(n);
    up[0] = down[0] = 1;
    for (int i = 1; i < n; i++) {
        if (nums[i] > nums[i - 1]) {
            up[i] = max(up[i - 1], down[i - 1] + 1);
            down[i] = down[i - 1];
        } else if (nums[i] < nums[i - 1]) {
            up[i] = up[i - 1];
            down[i] = max(up[i - 1] + 1, down[i - 1]);
        } else {
            up[i] = up[i - 1];
            down[i] = down[i - 1];
        }
    }
    return max(up[n - 1], down[n - 1]);
}

bool DailyCoding::containsDuplicate(vector<int> &nums) {
    if (nums.size() < 2) {
        return false;
    }
    sort(nums.begin(), nums.end());
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] == nums[i - 1]) {
            return true;
        }
    }
    return false;
}

vector<vector<string>> DailyCoding::groupAnagrams(vector<string> &strs) {
    unordered_map<string, vector<string>> mp;
    for (string &str:strs) {
        string key = str;
        sort(key.begin(), key.end());
        mp[key].emplace_back(str);
    }
    vector<vector<string>> ans;
    for (auto it = mp.begin(); it != mp.end(); it++) {
        ans.emplace_back(it->second);
    }
    return ans;
}

int DailyCoding::monotoneIncreasingDigits(int N) {
    // 贪心算法
    string strN = to_string(N);
    int i = 1;
    while (i < strN.length() && strN[i - 1] >= strN[i]) {
        i += 1;
    }
    if (i < strN.length()) {
        while (i > 0 && strN[i - 1] > strN[i]) {
            strN[i - 1] -= 1;
            i -= 1;
        }
        for (i += 1; i < strN.length(); i++) {
            strN[i] = '9';
        }
    }
    return stoi(strN);
}

vector<vector<int>> DailyCoding::zigzagLevelOrder(TreeNode *root) {
    if (root == nullptr) {
        return {};
    }
    vector<vector<int>> res;
    queue<TreeNode *> qNodes;
    qNodes.push(root);
    while (!qNodes.empty()) {
        int currentSize = qNodes.size();
        vector<int> tmpVec;
        for (int i = 0; i < currentSize; i++) {
            TreeNode *currentNode = qNodes.front();
            qNodes.pop();
            tmpVec.push_back(currentNode->val);
            if (currentNode->left != nullptr) {
                qNodes.push(currentNode->left);
            }
            if (currentNode->right != nullptr) {
                qNodes.push(currentNode->right);
            }
        }
        res.push_back(tmpVec);
    }
    bool flag = false;
    for (int i = 0; i < res.size(); i++) {
        if (flag) {
            reverse(res[i].begin(), res[i].end());
            flag = false;
        } else {
            flag = true;
        }
    }
    return res;
}

int DailyCoding::firstUniqChar(string s) {
    vector<int> hash(26);
    for (int i = 0; i < s.length(); i++) {
        hash[s[i] - 'a']++;
    }
    for (int i = 0; i < s.length(); i++) {
        if (hash[s[i] - 'a'] == 1) {
            return i;
        }
    }
    return -1;
}

int DailyCoding::maximalRectangle(vector<vector<char>> &matrix) {
    if (matrix.empty()) {
        return 0;
    }
    int rows = matrix.size(), cols = matrix[0].size();
    int maxArea = 0;
    vector<vector<int>> rect(rows, vector<int>(cols, 0));
    for (int i = 0; i < rows; i++) {
        //针对每一行计算[0,col]能够形成的最大矩形
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == '1') {
                //如果当前是第一个元素需要单独处理
                if (j == 0) {
                    rect[i][j] = 1;
                } else {
                    rect[i][j] = rect[i][j - 1] + 1;
                }
            } else {
                rect[i][j] = 0;
            }
            int minWidth = rect[i][j];
            for (int row = i; row >= 0; row--) {
                if (rect[row][j] == 0) {
                    break;
                }
                int height = i - row + 1;
                minWidth = min(minWidth, rect[row][j]);
                maxArea = max(maxArea, height * minWidth);
            }
        }
    }
    return maxArea;
}

bool DailyCoding::isIsomorphic(string s, string t) {
    if (s.empty() && t.empty()) {
        return true;
    }
    if (s.empty() || t.empty()) {
        return false;
    }
    int m1[256] = {0};
    int m2[256] = {0};
    int n = s.length();
    for (int i = 0; i < n; i++) {
        if (m1[s[i]] != m2[t[i]]) {
            return false;
        }
        m1[s[i]] = i + 1;
        m2[t[i]] = i + 1;
    }
    return true;
}

bool DailyCoding::canPlaceFlowers(vector<int> &flowerbed, int n) {
    int count = 0;
    int m = flowerbed.size();
    int prev = -1;
    for (int i = 0; i < n; i++) {
        if (flowerbed[i] == 1) {
            if (prev < 0) {
                count += i / 2;
            } else {
                count += (i - prev - 2) / 2;
            }
            if (count >= n) {
                return true;
            }
            prev = i;
        }
    }
    if (prev < 0) {
        count += (m + 1) / 2;
    } else {
        count += (m - prev - 1) / 2;
    }
    return count >= n;
}

vector<int> DailyCoding::maxSlidingWindow(vector<int> &nums, int k) {
    int n = nums.size();
    priority_queue<pair<int, int>> q;
    for (int i = 0; i < k; i++) {
        q.emplace(nums[i], i);
    }
    vector<int> res{q.top().first};
    for (int i = k; i < n; i++) {
        q.emplace(nums[i], i);
        while (q.top().second <= i - k) {
            q.pop();
        }
        res.push_back(q.top().first);
    }
    return res;
}

ListNode *DailyCoding::partition(ListNode *head, int x) {
    ListNode *small = new ListNode(0);
    ListNode *small_head = small;
    ListNode *large = new ListNode(0);
    ListNode *large_head = large;
    while (head != nullptr) {
        if (head->val < x) {
            small->next = head;
            small = small->next;
        } else {
            large->next = head;
            large = large->next;
        }
        head = head->next;
    }
    large->next = nullptr;
    small->next = large_head->next;
    return small_head->next;
}

int DailyCoding::fib(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    int left = 0, right = 1, temp;
    for (int i = 2; i <= n; i++) {
        temp = right;
        right += left;
        left = temp;
    }
    return right;
}

vector<vector<int>> DailyCoding::largeGroupPositions(string s) {
    if (s.size() < 3) {
        return {};
    }
    vector<vector<int>> res;
    int i = 0, j = 1, count = 1;
    while (i < s.length() && j < s.length()) {
        if (s[i] != s[j]) {
            if (count > 2) res.push_back({i, j - 1});
            i++;
            count = 0;
        } else j++, count++;
    }
    if (count > 2) res.push_back({i, j - 1});
    return res;
}

int DailyCoding::findCircleNum(vector<vector<int>> &isConnected) {
    int provinces = isConnected.size();
    vector<int> visited(provinces);
    int circles = 0;
    queue<int> Q;
    for (int i = 0; i < provinces; i++) {
        if (!visited[i]) {
            Q.push(i);
            while (!Q.empty()) {
                int j = Q.front();
                Q.pop();
                visited[j] = 1;
                for (int k = 0; k < provinces; k++) {
                    if (isConnected[j][k] == 1 && !visited[k]) {
                        Q.push(k);
                    }
                }
            }
            circles++;
        }
    }
    return circles;
}

void DailyCoding::rotate(vector<int> &nums, int k) {
    k %= nums.size();
    while (k) {
        int tmp = nums.back();
        nums.insert(nums.begin(), tmp);
        nums.pop_back();
        k--;
    }
}

int DailyCoding::maxProfit03(vector<int> &prices) {
    int n = prices.size();
    int buy01 = prices[0], sell01 = 0;
    int buy02 = prices[0], sell02 = 0;
    for (int i = 1; i < n; i++) {
        buy01 = min(buy01, prices[i]);
        sell01 = max(sell01, prices[i] - buy01);
        buy02 = min(buy02, prices[i] - sell01);
        sell02 = max(sell02, prices[i] - buy02);
    }
    return sell02;
}

vector<string> DailyCoding::summaryRanges(vector<int> &nums) {
    vector<string> res;
    int i = 0;
    int n = nums.size();
    while (i < n) {
        int low = i;
        i++;
        while (i < n && nums[i] == nums[i - 1] + 1) {
            i++;
        }
        int high = i - 1;
        string tmp = to_string(nums[low]);
        if (low < high) {
            tmp.append("->");
            tmp.append(to_string(nums[high]));
        }
        res.push_back(move(tmp));
    }
    return res;
}

string DailyCoding::smallestStringWithSwaps(string s, vector<vector<int>> &pairs) {
    int n = s.size();
    vector<char> rs(n);
    Djset ds(n);
    for (const auto &e : pairs) ds.merge(e[0], e[1]);

    //  格式化并查集，即哪些下标可以交换
    unordered_map<int, vector<int> > um;
    for (int i = 0; i < n; i++) um[ds.find(i)].push_back(i);

    // 同一并查集按字典序排序
    for (auto &_kv : um) {
        vector<int> c = _kv.second;
        sort(_kv.second.begin(), _kv.second.end(), [&](int a, int b) {
            return s[a] < s[b];
        });
        for (int i = 0; i < c.size(); i++) rs[c[i]] = s[_kv.second[i]];
    }

    s = "";
    for (const auto &e : rs) s += e;
    return s;
}

vector<int> DailyCoding::sortItems(int n, int m, vector<int> &group, vector<vector<int>> &beforeItems) {
    vector<vector<int>> groupItem(n + m);

    // 组间和组内依赖图
    vector<vector<int>> groupGraph(n + m);
    vector<vector<int>> itemGraph(n);

    // 组间和组内入度数组
    vector<int> groupDegree(n + m, 0);
    vector<int> itemDegree(n, 0);

    vector<int> id;
    for (int i = 0; i < n + m; ++i) {
        id.emplace_back(i);
    }

    int leftId = m;
    // 给未分配的 item 分配一个 groupId
    for (int i = 0; i < n; ++i) {
        if (group[i] == -1) {
            group[i] = leftId;
            leftId += 1;
        }
        groupItem[group[i]].emplace_back(i);
    }
    // 依赖关系建图
    for (int i = 0; i < n; ++i) {
        int curGroupId = group[i];
        for (auto &item: beforeItems[i]) {
            int beforeGroupId = group[item];
            if (beforeGroupId == curGroupId) {
                itemDegree[i] += 1;
                itemGraph[item].emplace_back(i);
            } else {
                groupDegree[curGroupId] += 1;
                groupGraph[beforeGroupId].emplace_back(curGroupId);
            }
        }
    }

    // 组间拓扑关系排序
    vector<int> groupTopSort = topSort(groupDegree, groupGraph, id);
    if (groupTopSort.size() == 0) {
        return vector<int>{};
    }
    vector<int> ans;
    // 组内拓扑关系排序
    for (auto &curGroupId: groupTopSort) {
        int size = groupItem[curGroupId].size();
        if (size == 0) {
            continue;
        }
        vector<int> res = topSort(itemDegree, itemGraph, groupItem[curGroupId]);
        if (res.size() == 0) {
            return vector<int>{};
        }
        for (auto &item: res) {
            ans.emplace_back(item);
        }
    }
    return ans;
}

vector<int> DailyCoding::findRedundantConnection(vector<vector<int>> &edges) {
    int nodeCounts = edges.size();
    vector<int> parent(nodeCounts + 1);
    for (int i = 1; i < nodeCounts + 1; i++) {
        parent[i] = i;
    }
    for (auto &edge:edges) {
        int node01 = edge[0], node02 = edge[1];
        if (find_func(parent, node01) != find_func(parent, node02)) {
            union_func(parent, node01, node02);
        } else return edge;
    }
    return {};
}

vector<bool> DailyCoding::prefixesDivBy5(vector<int> &A) {
    vector<bool> list;
    int prefix = 0;
    int length = A.size();
    for (int i = 0; i < length; i++) {
        prefix = ((prefix << 1) + A[i]) % 5;
        list.emplace_back(prefix == 0);
    }
    return list;
}

int DailyCoding::removeStones(vector<vector<int>> &stones) {
    DisjointSetUnion _dsu;
    for (int i = 0; i < stones.size(); i++) {
        _dsu.unionSet(stones[i][0], stones[i][1] + 10000);
    }
    return stones.size() - _dsu.number_of_connected();
}

vector<int> DailyCoding::hitBricks(vector<vector<int>> &grid, vector<vector<int>> &hits) {
    int h = grid.size(), w = grid[0].size();

    UnionFind uf(h * w + 1);
    vector<vector<int>> status = grid;
    for (int i = 0; i < hits.size(); i++) {
        status[hits[i][0]][hits[i][1]] = 0;
    }
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (status[i][j] == 1) {
                if (i == 0) {
                    uf.merge(h * w, i * w + j);
                }
                if (i > 0 && status[i - 1][j] == 1) {
                    uf.merge(i * w + j, (i - 1) * w + j);
                }
                if (j > 0 && status[i][j - 1] == 1) {
                    uf.merge(i * w + j, i * w + j - 1);
                }
            }
        }
    }
    const vector<pair<int, int>> directions{{0,  1},
                                            {1,  0},
                                            {0,  -1},
                                            {-1, 0}};
    vector<int> ret(hits.size(), 0);
    for (int i = hits.size() - 1; i >= 0; i--) {
        int r = hits[i][0], c = hits[i][1];
        if (grid[r][c] == 0) {
            continue;
        }
        int prev = uf.size(h * w);

        if (r == 0) {
            uf.merge(c, h * w);
        }
        for (const auto _drc: directions) {
            int nr = r + _drc.first, nc = c + _drc.second;

            if (nr >= 0 && nr < h && nc >= 0 && nc < w) {
                if (status[nr][nc] == 1) {
                    uf.merge(r * w + c, nr * w + nc);
                }
            }
        }
        int size = uf.size(h * w);
        ret[i] = max(0, size - prev - 1);
        status[r][c] = 1;
    }
    return ret;
}

bool DailyCoding::checkStraightLine(vector<vector<int>> &coordinates) {
    int n = coordinates.size();
    int x0 = coordinates[0][0], y0 = coordinates[0][1];
    int x = coordinates[1][0] - x0, y = coordinates[1][1] - y0;
    for (int i = 2; i < n; i++) {
        int xi = coordinates[i][0] - x0;
        int yi = coordinates[i][1] - y0;
        if (x * yi - y * xi) return false;
    }
    return true;
}

vector<vector<string>> DailyCoding::accountsMerge(vector<vector<string>> &accounts) {
    map<string, int> emailToIndex;
    map<string, string> emailToName;
    int emailsCount = 0;
    for (auto &account : accounts) {
        string &name = account[0];
        int size = account.size();
        for (int i = 1; i < size; i++) {
            string &email = account[i];
            if (!emailToIndex.count(email)) {
                emailToIndex[email] = emailsCount++;
                emailToName[email] = name;
            }
        }
    }
    UnionFind_accountsMerge uf(emailsCount);
    for (auto &account : accounts) {
        string &firstEmail = account[1];
        int firstIndex = emailToIndex[firstEmail];
        int size = account.size();
        for (int i = 2; i < size; i++) {
            string &nextEmail = account[i];
            int nextIndex = emailToIndex[nextEmail];
            uf.union_set(firstIndex, nextIndex);
        }
    }
    map<int, vector<string>> indexToEmails;
    for (auto &_email_ : emailToIndex) {
        int index = uf.find(emailToIndex[_email_.first]);
        vector<string> &account = indexToEmails[index];
        account.emplace_back(_email_.first);
        indexToEmails[index] = account;
    }
    vector<vector<string>> merged;
    for (auto &__email : indexToEmails) {
        sort(__email.second.begin(), __email.second.end());
        string &name = emailToName[__email.second[0]];
        vector<string> account;
        account.emplace_back(name);
        for (auto &email : __email.second) {
            account.emplace_back(email);
        }
        merged.emplace_back(account);
    }
    return merged;
}

int DailyCoding::maximumProduct(vector<int> &nums) {
    // 最大乘积的结果只有两种可能的情况
    sort(nums.begin(), nums.end());
    int size = nums.size();
    int a = INT32_MIN, b = INT32_MIN;
    if (nums[0] < 0 && nums[1] < 0) a = nums[0] * nums[1] * nums.back();
    b = nums[size - 1] * nums[size - 2] * nums[size - 3];
    return max(a, b);
}

vector<int> DailyCoding::addToArrayForm(vector<int> &A, int K) {
    vector<int> res;
    for (int i = A.size() - 1; i >= 0; i--) {
        int sum = A[i] + K % 10;
        K /= 10;
        if (sum > 9) {
            sum -= 10;
            K++;
        }
        res.push_back(sum);
    }
    while (K) {
        res.push_back(K % 10);
        K /= 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

int DailyCoding::findLengthOfLCIS(vector<int> &nums) {
    if (nums.empty()) return 0;
    if (nums.size() < 2) return 1;
    int res = 0;
    int slow = 0, fast = 1;
    while (fast < nums.size()) {
        if (nums[fast] > nums[fast - 1]) fast++;
        else {
            res = max(res, fast - slow);
            slow = fast++;
        }
    }
    return max(res, fast - slow);
}

int DailyCoding::numEquivDominoPairs(vector<vector<int>> &dominoes) {
    int res = 0;
    vector<int> nums(100);
    for (auto &v:dominoes) {
        int val = v[0] > v[1] ? v[0] * 10 + v[1] : v[1] * 10 + v[0];
        res += nums[val];
        nums[val]++;
    }
    return res;
}

vector<vector<int>> DailyCoding::subsets(vector<int> &nums) {
    vector<vector<int>> res;
    vector<int> tmp;
    backTrack_subsets(res, tmp, nums, 0);
    return res;
}

TreeNode *DailyCoding::lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
    if (root->val > p->val && root->val > q->val) return lowestCommonAncestor(root->left, p, q);
    else if (root->val < p->val && root->val < q->val) return lowestCommonAncestor(root->right, p, q);
    return root;
}

vector<vector<int>> DailyCoding::permuteUnique(vector<int> &nums) {
    vector<bool> used(nums.size(), false);
    vector<int> path;
    vector<vector<int>> res;
    sort(nums.begin(), nums.end());
    dfs_permuteUnique(nums, 0, res, used, path);
    return res;
}

int DailyCoding::pivotIndex(vector<int> &nums) {
    if (nums.empty()) return -1;
    if (nums.size() == 1) return nums[0];
    int res_index = 0;
    int left_sum = 0, right_sum = accumulate(nums.begin() + 1, nums.end(), 0);
    while (left_sum != right_sum && res_index < nums.size() - 1) {
        left_sum += nums[res_index];
        right_sum -= nums[res_index + 1];
        res_index++;
    }
    return left_sum == right_sum ? res_index : -1;
}

int DailyCoding::minimumEffortPath(vector<vector<int>> &heights) {
    if (heights.empty()) return 0;
    vector<vector<int>> directions{{-1, 0},
                                   {1,  0},
                                   {0,  -1},
                                   {0,  1}};
    int m = heights.size(), n = heights[0].size();
    int left = 0, right = 999999, res = 0;
    while (left <= right) {
        int mid = (left + right) / 2;
        queue<pair<int, int>> q;
        q.emplace(0, 0);
        vector<int> seen(m * n);
        seen[0] = 1;
        while (!q.empty()) {
            pair<int, int> x_y = q.front();
//            auto[x, y]=q.front();
            q.pop();
            for (int i = 0; i < 4; i++) {
                int nx = x_y.first + directions[i][0];
                int ny = x_y.second + directions[i][1];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && !seen[nx * n + ny] &&
                    abs(heights[x_y.first][x_y.second] - heights[nx][ny]) <= mid) {
                    q.emplace(nx, ny);
                    seen[nx * n + ny] = 1;
                }
            }
        }
        if (seen[m * n - 1]) {
            res = mid;
            right = mid - 1;
        } else left = mid + 1;
    }
    return res;
}

vector<int> DailyCoding::fairCandySwap(vector<int> &A, vector<int> &B) {
    int sum_a = accumulate(A.begin(), A.end(), 0);
    int sum_b = accumulate(B.begin(), B.end(), 0);
    int delta = (sum_a - sum_b) / 2;
    unordered_set<int> rec(A.begin(), A.end());
    vector<int> res;
    for (auto &y:B) {
        int x = y + delta;
        if (rec.count(x)) {
            res = vector<int>{x, y};
            break;
        }
    }
    return res;
}

int DailyCoding::characterReplacement(string s, int k) {
    vector<int> nums(26);
    int n = s.length();
    int max_num = 0;
    int left = 0, right = 0;
    while (right < n) {
        nums[s[right] - 'A']++;
        max_num = max(max_num, nums[s[right] - 'A']);
        if (right - left + 1 - max_num > k) {
            nums[left - 'A']--;
            left++;
        }
        right++;
    }
    return right - left;
}

double DailyCoding::findMaxAverage(vector<int> &nums, int k) {
    if (k >= nums.size()) return (double) (accumulate(nums.begin(), nums.end(), 0) / (double) nums.size());
    double res = (double) INT32_MIN;
    int left = 0, right = k - 1;
    double curr_sum = accumulate(nums.begin(), nums.begin() + k - 1, 0);
    while (right < nums.size()) {
        curr_sum += nums[right++];
        res = max(res, (double) (curr_sum / (double) k));
        curr_sum -= nums[left++];
    }
    return res;
}

int DailyCoding::equalSubstring(string s, string t, int maxCost) {
    // 要求转换后的字符连续
    vector<int> diff(s.size(), 0);
    for (int i = 0; i < s.size(); i++) diff[i] = abs(s[i] - t[i]);
    int res = 0;
    int start = 0, end = 0;
    int sum = 0;
    while (end < s.size()) {
        sum += diff[end];
        while (sum > maxCost) {
            sum -= diff[start];
            start++;
        }
        res = max(res, end - start + 1);
        end++;
    }
    return res;
}

int DailyCoding::maxScore(vector<int> &cardPoints, int k) {
    int n = cardPoints.size();
    int windows_size = n - k;
    int sum = accumulate(cardPoints.begin(), cardPoints.begin() + windows_size, 0);
    int min_sum = sum;
    for (int i = windows_size; i < n; i++) {
        sum += cardPoints[i] - cardPoints[i - windows_size];
        min_sum = min(min_sum, sum);
    }
    return accumulate(cardPoints.begin(), cardPoints.end(), 0) - min_sum;
}

bool DailyCoding::checkPossibility(vector<int> &nums) {
    if (nums.size() < 3) return true;
    int count = 0;
    for (int i = 0; i < nums.size() - 1; i++) {
        int curr = nums[i], next = nums[i + 1];
        if (curr > next) {
            count++;
            if (count > 1) return false;
            if (i > 0 && next < nums[i - 1]) nums[i + 1] = curr;
        }
    }
    return count < 2;
}

int DailyCoding::maxTurbulenceSize(vector<int> &arr) {
    if (arr.size() < 2) return arr.size();
    int len = arr.size();
    int left = 0, right = 1;
    bool pre = false;
    int res = 1;
    while (right < len) {
        bool curr = arr[right - 1] < arr[right];
        if (pre == curr) left = right - 1;
        if (arr[right - 1] == arr[right]) left = right;
        right++;
        res = max(res, right - left);
        pre = curr;
    }
    return res;
}

bool DailyCoding::checkInclusion(string s1, string s2) {
    // =====  滑动窗口法  =====
    // 由于排列不会改变字符串中每个字符的个数
    // 所以只有当两个字符串每个字符的个数均相等时，一个字符串才是另一个字符串的排列。
    int n = s1.length(), m = s2.length();
    if (n > m) return false;
    vector<int> cnt01(26), cnt02(26);
    for (int i = 0; i < n; i++) {
        ++cnt01[s1[i] - 'a'];
        ++cnt02[s2[i] - 'a'];
    }
    if (cnt01 == cnt02) return true;
    for (int i = n; i < m; i++) {
        ++cnt02[s2[i] - 'a'];
        --cnt02[s2[i - n] - 'a'];
        if (cnt01 == cnt02) return true;
    }
    return false;
}

vector<int> DailyCoding::getRow(int rowIndex) {
    vector<int> all_rows(rowIndex + 1);
    all_rows[0] = 1;
    for (int i = 1; i <= rowIndex; i++) {
        all_rows[i] = 1LL * all_rows[i - 1] * (rowIndex - i + 1) / i;
    }
    return all_rows;
}

vector<int> DailyCoding::findDisappearedNumbers(vector<int> &nums) {
    if (nums.empty()) return nums;
    vector<int> res;
    for (int i = 0; i < nums.size(); ++i) {
        int index = (nums[i] - 1) % nums.size();
        nums[index] += nums.size();
    }
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] <= nums.size()) res.push_back(i + 1);
    }
    return res;
}

vector<vector<int>> DailyCoding::matrixReshape(vector<vector<int>> &nums, int r, int c) {
    int m = nums.size();
    int n = nums[0].size();
    if (m * n != r * c) return nums;

    vector<vector<int>> res(r, vector<int>(c));
    for (int x = 0; x < m * n; ++x) {
        res[x / c][x % c] = nums[x / n][x % n];
    }
    return res;
}

int DailyCoding::longestSubarray(vector<int> &nums, int limit) {
    deque<int> qMax, qMin;
    int n = nums.size();
    int left = 0, right = 0;
    int res = 0;
    while (right < n) {
        while (!qMax.empty() && qMax.back() < nums[right]) qMax.pop_back();
        while (!qMin.empty() && qMin.back() > nums[right]) qMin.pop_back();
        qMax.push_back(nums[right]);
        qMin.push_back(nums[right]);
        while (!qMin.empty() && !qMax.empty() && qMax.front() - qMin.front() > limit) {
            if (nums[left] == qMin.front()) qMin.pop_front();
            if (nums[left] == qMax.front()) qMax.pop_front();
            left++;
        }
        res = max(res, right - left + 1);
        right++;
    }
    return res;
}

vector<vector<int>> DailyCoding::transpose(vector<vector<int>> &matrix) {
    vector<vector<int>> res(matrix[0].size(), vector<int>(matrix.size()));
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            res[j][i] = matrix[i][j];
        }
    }
    return res;
}

int DailyCoding::hammingWeight(uint32_t n) {
    int res = 0;
    while (n) {
        res += (n & 1);
        n >>= 1;
    }
    return res;
}

void DailyCoding::setZeroes(vector<vector<int>> &matrix) {
    if (matrix.empty()) return;
    vector<int> rows, cols;
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] == 0) {
                rows.push_back(i);
                cols.push_back(j);
            }
        }
    }
    rows.erase(unique(rows.begin(), rows.end()), rows.end());
    cols.erase(unique(cols.begin(), cols.end()), cols.end());
    while (!rows.empty()) {
        int curr_row = rows.back();
        rows.pop_back();
        for (int i = 0; i < matrix[0].size(); i++) matrix[curr_row][i] = 0;
    }
    while (!cols.empty()) {
        int curr_col = cols.back();
        cols.pop_back();
        for (int i = 0; i < matrix.size(); i++) matrix[i][curr_col] = 0;
    }
}

int DailyCoding::evalRPN(vector<string> &tokens) {
    if (tokens.size() == 1) return atoi(tokens[0].c_str());
    int res = 0;
    stack<int> nums;
    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/") {
            int first_num = nums.top();
            nums.pop();
            int second_num = nums.top();
            nums.pop();
            int tmp = 0;
            if (tokens[i] == "+") tmp = first_num + second_num;
            else if (tokens[i] == "-") tmp = second_num - first_num;
            else if (tokens[i] == "*") tmp = first_num * second_num;
            else tmp = second_num / first_num;
            nums.push(tmp);
        } else {
            nums.push(atoi(tokens[i].c_str()));
        }
    }
    return nums.top();
}

//bool DailyCoding::find132pattern(vector<int> &nums) {
//    int n = nums.size();
//    stack<int> candidate_k;
//    candidate_k.push(nums[n - 1]);
//    int max_k = INT_MIN;
//
//    for (int i = n - 2; i >= 0; i--) {
//        if (nums[i] < max_k) {
//            return true;
//        }
//        while (!candidate_k.empty() && nums[i] > candidate_k.top()) {
//            max_k = candidate_k.top();
//            candidate_k.pop();
//        }
//        if (nums[i] > max_k) {
//            candidate_k.push(nums[i]);
//        }
//    }
//    return false;
//}

ListNode *DailyCoding::deleteDuplicates(ListNode *head) {
    if (head == nullptr) return head;
    ListNode *dummy = new ListNode(0, head);
    ListNode *currNode = dummy;
    while (currNode->next != nullptr && currNode->next->next != nullptr) {
        if (currNode->next->val == currNode->next->next->val) {
            int dupVal = currNode->next->val;
            while (currNode->next && currNode->next->val == dupVal) currNode->next = currNode->next->next;
        } else currNode = currNode->next;
    }
    return dummy->next;
}

ListNode *DailyCoding::deleteDuplicates01(ListNode *head) {
    if (head == nullptr) return head;
    ListNode *currNode = head;
    while (currNode != nullptr && currNode->next != nullptr) {
        if (currNode->val == currNode->next->val) currNode->next = currNode->next->next;
        else currNode = currNode->next;
    }
    return head;
}

ListNode *DailyCoding::rotateRight(ListNode *head, int k) {
    if (k == 0 || head == nullptr || head->next == nullptr) {
        return head;
    }

    int n = 1;
    ListNode *iter = head;
    while (iter->next != nullptr) {
        iter = iter->next;
        n++;
    }
    int add = n - k % n;
    if (add == n) {
        return head;
    }
    iter->next = head;
    while (add--) {
        iter = iter->next;
    }
    ListNode *ret = iter->next;
    iter->next = nullptr;
    return ret;
}

uint32_t DailyCoding::reverseBits(uint32_t n) {
    uint32_t res = 0;   // 必须初始化
    for (int i = 0; i < 32 && n > 0; i++) {
        res |= (n & 1) << (31 - i);
        n >>= 1;
    }
    return res;
}

bool DailyCoding::searchMatrix(vector<vector<int>> &matrix, int target) {
    int row = matrix.size(), col = matrix[0].size();
    int low = 0, high = row * col - 1;
    while (low < high) {
        int mid = (high - low) / 2 + low;
        int curr = matrix[mid / col][mid % col];    // 准确定位中间元素
        if (curr < target) {
            low = mid + 1;
        } else if (curr > target) {
            high = mid - 1;
        } else return true;
    }
    return false;
}

vector<vector<int>> DailyCoding::subsetsWithDup(vector<int> &nums) {
    vvRes.clear();
    vPath.clear();
    vector<bool> used(nums.size(), false);
    sort(nums.begin(), nums.end());     // 去重全排列要先排序
    backTrack_subsetsWithDup(nums, 0, used);
    return vvRes;
}

int DailyCoding::clumsy(int N) {
    if (N == 1) return 1;
    else if (N == 2) return 2;
    else if (N == 3) return 6;
    else if (N == 4) return 7;

    // 从第五个数字开始变得有规律
    if (N % 4 == 0) return N + 1;
    else if (N % 4 < 3) return N + 2;
    else return N - 1;
}

int DailyCoding::longestCommonSubsequence(string text1, string text2) {
    if (text1.empty() || text2.empty()) return 0;
    int m = text1.size();
    int n = text2.size();
    vector<vector<int>> dpArr(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i < m + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            if (text1[i - 1] == text2[j - 1]) {
                dpArr[i][j] = dpArr[i - 1][j - 1] + 1;
            } else {
                dpArr[i][j] = max(dpArr[i - 1][j], dpArr[i][j - 1]);
            }
        }
    }
    return dpArr[m][n];
}

void DailyCoding::merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
    if (nums2.empty()) return;
    int p1 = m - 1, p2 = n - 1;
    int tail = m + n - 1;
    int curr = 0;
    while (p1 >= 0 || p2 >= 0) {
        if (p1 < 0) curr = nums2[p2--];
        else if (p2 < 0) curr = nums1[p1--];
        else if (nums1[p1] < nums2[p2]) curr = nums2[p2--];
        else curr = nums1[p1--];
        nums1[tail--] = curr;
    }
}

int DailyCoding::removeDuplicates(vector<int> &nums) {
    if (nums.size() < 3) return nums.size();
    int preNum = nums[0];
    int flag = 1;
    auto pIter = nums.begin() + 1;
    while (pIter != nums.end()) {
        if (*pIter == preNum) {
            flag++;
            if (flag > 2) nums.erase(pIter);
            else pIter++;
        } else {
            flag = 1;
            preNum = *pIter;
            pIter++;
        }
    }
    return nums.size();
}

bool DailyCoding::search(vector<int> &nums, int target) {
    if (nums.empty()) return false;
    if (nums.size() == 1) return nums[0] == target;
    int l = 0, r = nums.size() - 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (nums[mid] == target) return true;
        if (nums[l] == nums[mid] && nums[r] == nums[mid]) l++, r--;
        else if (nums[l] <= nums[mid]) {
            if (nums[l] <= target && target < nums[mid]) r = mid - 1;
            else l = mid + 1;
        } else {
            if (nums[mid] < target && target <= nums[nums.size() - 1]) l = mid + 1;
            else r = mid - 1;
        }
    }
    return false;
}

int DailyCoding::findMin(vector<int> &nums) {
    int low = 0, high = nums.size() - 1;
    while (low < high) {
        int pivot = low + (high - low) / 2;
        if (nums[pivot] < nums[high]) high = pivot;
        else low = pivot + 1;
    }
    return nums[low];
}

int DailyCoding::findMin02(vector<int> &nums) {
    // 放弃治疗，实际上这是力扣的困难题
    return *min_element(nums.begin(), nums.end());
}

bool DailyCoding::isUgly(int n) {
    if (n == 0) return false;
    while (n % 2 == 0) n /= 2;
    while (n % 3 == 0) n /= 3;
    while (n % 5 == 0) n /= 5;
    return n == 1;
}

int DailyCoding::nthUglyNumber(int n) {
    vector<int> factor{2, 3, 5};
    unordered_set<long> seen;   // 用于去重
    priority_queue<long, vector<long>, greater<long>> heap;
    seen.insert(1l);    // 最小的丑数
    heap.push(1l);
    int uglyRes = 0;
    for (int i = 0; i < n; i++) {
        long curr = heap.top();
        heap.pop();
        uglyRes = (int) curr;
        for (int fac:factor) {
            long next = fac * curr;
            if (!seen.count(next)) {
                seen.insert(next);
                heap.push(next);
            }
        }
    }
    return uglyRes;
}

string DailyCoding::largestNumber(vector<int> &nums) {
    vector<string> sNums;
    for (int i:nums) sNums.push_back(to_string(i));
    sort(sNums.begin(), sNums.end(), [](string s1, string s2) { return s1 + s2 > s2 + s1; });   // 两个字符串先后组合大小降序排列
    if (sNums[0] == "0") return "0";    // 全是0的情况
    string res;
    for (string s:sNums) res += s;
    return res;
}

int DailyCoding::minDiffInBST(TreeNode *root) {
    if (root == nullptr) return 0;
    int res = 9999999;
    TreeNode *pre = nullptr;
    inorder_minDiffInBST(root, pre, res);
    return res;
}

int DailyCoding::removeDuplicates01(vector<int> &nums) {
    unordered_map<int, int> numCounts;
    vector<int>::iterator pIter = nums.begin();
    while (pIter != nums.end()) {
        int currNum = *pIter;
        if (numCounts[currNum]) nums.erase(pIter);
        else {
            numCounts[currNum]++;
            pIter++;
        }
    }
    return nums.size();
}

int DailyCoding::removElement(vector<int> &nums, int val) {
    vector<int>::iterator pIter = nums.begin();
    while (pIter != nums.end()) {
        int currNum = *pIter;
        if (currNum == val) nums.erase(pIter);
        else pIter++;
    }
    return nums.size();
}

int DailyCoding::strStr(string haystack, string needle) {
    // 理想解法 KMP，=== mark 0420 ===
    return (int) haystack.find(needle);
}

int DailyCoding::numDecodings(string s) {
    if (s[0] == '0') return 0;
    vector<int> dpArr(s.size() + 1);
    dpArr[0] = 1;
    for (int i = 1; i < s.size() + 1; i++) {
        // 两个不同的状态转移方程
        if (s[i - 1] != '0') dpArr[i] += dpArr[i - 1];
        if (i > 1 && s[i - 2] != '0' && ((s[i - 2] - '0') * 10 + s[i - 1] - '0' <= 26)) dpArr[i] += dpArr[i - 2];
    }
    return dpArr.back();
}

int DailyCoding::combinationSum4(vector<int> &nums, int target) {
    vector<int> dpArr(target + 1);
    dpArr[0] = 1;
    for (int i = 1; i <= target; i++) {
        for (int &num:nums) {
            if (num <= i && dpArr[i - num] < INT16_MAX - dpArr[i]) dpArr[i] += dpArr[i - num];
        }
    }
    return dpArr.back();
}

TreeNode *DailyCoding::increasingBST(TreeNode *root) {
    TreeNode *dummyNode = new TreeNode(-1);
    TreeNode *parentHead = dummyNode;
    increasingBST_func(root, parentHead, dummyNode);
    return dummyNode->right;
}

int DailyCoding::shipWithinDays(vector<int> &weights, int D) {
    // ***** 二分查找mark，暂时没看懂 *****
    int left = *max_element(weights.begin(), weights.end()), right = accumulate(weights.begin(), weights.end(), 0);
    while (left < right) {
        int mid = (left + right) / 2;
        // need 为需要运送的天数
        // cur 为当前这一天已经运送的包裹重量之和
        int need = 1, curr = 0;
        for (int &weight:weights) {
            if (curr + weight > mid) {
                ++need;
                curr = 0;
            }
            curr += weight;
        }
        if (need <= D) right = mid;
        else left = mid + 1;
    }
    return left;
}

int DailyCoding::rangeSumBST(TreeNode *root, int low, int high) {
    if (root == nullptr) return 0;
    if (root->val < low) return rangeSumBST(root->right, low, high);
    if (root->val > high) return rangeSumBST(root->left, low, high);
    return root->val + rangeSumBST(root->left, low, high) + rangeSumBST(root->right, low, high);
}

int DailyCoding::singleNumber(vector<int> &nums) {
    if (nums.size() == 1) return nums[0];
    sort(nums.begin(), nums.end());
    int pos = 0;
    while (pos < nums.size() - 1) {
        if (nums[pos] == nums[pos + 1]) pos += 3;
        else return nums[pos];
    }
    return nums.back();
}

int DailyCoding::getImportance(vector<Employee *> employees, int id) {
    int res = 0;
    queue<int> toRead;
    toRead.push(id);    // 用于存储id
    vector<bool> isVisit(2000, false);  // 题目设置了人数最多2000
    map<int, Employee *> allData;  // 用于根据id查询员工信息
    for (auto &init:employees) allData.insert(make_pair(init->id, init));
    while (!toRead.empty()) {
        int curr_id = toRead.front();
        toRead.pop();
        isVisit[curr_id] = true;
        res += allData[curr_id]->importance;
        for (int &i:allData[curr_id]->subordinates) {
            if (!isVisit[i]) toRead.push(i);
        }
    }
    return res;
}

int DailyCoding::leastBricks(vector<vector<int>> &wall) {
    // 穿过的砖块数量加上从边缘经过的砖块数量之和是一个定值，即砖墙的高度。
    // 遍历该哈希表，找到出现次数最多的砖块边缘，这就是垂线经过的砖块边缘，
    // 而该垂线经过的砖块数量即为砖墙的高度减去该垂线经过的砖块边缘的数量。
    int res = 0;
    unordered_map<int, int> cnt;
    for (int i = 0; i < wall.size(); i++) {
        int sum = 0;
        for (int j = 0; j < wall[i].size() - 1; j++) {
            sum += wall[i][j];
            cnt[sum]++; // 统计的是经过边缘
        }
    }
    for (auto &init:cnt) {
        res = max(res, init.second);
    }
    return wall.size() - res;   // 返回经过砖块的数量
}

int DailyCoding::reverseInt(int x) {
    int res = 0;
    while (x != 0) {
        // INT_MIN 与 INT_MAX 默认是32位
        if (res < INT_MIN / 10 || res > INT_MAX / 10) return 0;
        int digit = x % 10;
        x /= 10;
        res = res * 10 + digit;
    }
    return res;
}

vector<int> DailyCoding::decode(vector<int> &encoded, int first) {
    vector<int> res(encoded.size() + 1);
    res[0] = first;
    for (int i = 1; i < res.size(); i++) res[i] = encoded[i - 1] ^ res[i - 1];
    return res;
}

int DailyCoding::xorOperation(int n, int start) {
    int res = 0;
    for (int i = 0; i < n; i++) res ^= (start + 2 * i);
    return res;
}

int DailyCoding::minDays(vector<int> &bloomDay, int m, int k) {
    if (m * k > bloomDay.size()) return -1;
    int maxDay = *max_element(bloomDay.begin(), bloomDay.end());
    int minDay = *min_element(bloomDay.begin(), bloomDay.end());
    while (minDay < maxDay) {
        int days = (maxDay - minDay) / 2 + minDay;
        if (canMake_func(bloomDay, days, m, k)) {
            maxDay = days;  // 更新上限，时间可能更短
        } else minDay = days + 1;   // 更新下限，时间可能需要更长
    }
    return minDay;
}

bool DailyCoding::leafSimilar(TreeNode *root1, TreeNode *root2) {
    vector<int> leafs01, leafs02;
    traverseTree_func(root1, leafs01);
    traverseTree_func(root2, leafs02);
    return leafs01 == leafs02;
}

vector<int> DailyCoding::decode(vector<int> &encoded) {
    // ================== **** 位运算 **** ===================
    int n = encoded.size() + 1;
    int total = 0;
    for (int i = 1; i <= n; i++) {
        total ^= i;
    }
    int odd = 0;
    for (int i = 1; i < n - 1; i += 2) {
        odd ^= encoded[i];
    }
    vector<int> perm(n);
    perm[0] = total ^ odd;
    for (int i = 0; i < n - 1; i++) {
        perm[i + 1] = perm[i] ^ encoded[i];
    }
    return perm;
}

vector<int> DailyCoding::xorQueries(vector<int> &arr, vector<vector<int>> &queries) {
    // ================== **** 位运算 **** ===================
    vector<int> Xors(arr.size() + 1);
    // 缓存部分结果
    for (int i = 0; i < arr.size(); i++)　Xors[i + 1] = Xors[i] ^ arr[i];
    vector<int> res(queries.size());
    for (int i = 0; i < queries.size(); i++) {
        res[i] = Xors[queries[i][0]] ^ Xors[queries[i][1] + 1];
    }
    return res;
}

// 703. 数据流中的第 K 大元素
class KthLargest {
public:
    priority_queue<int, vector<int>, greater<int>> data;    // 维护小根堆
    int k;

    KthLargest(int k, vector<int> &nums) {
        this->k = k;
        for (int &i:nums) add(i);
    }

    int add(int val) {
        data.push(val);
        if (data.size() > k) data.pop();    // 数据中保持k个数
        return data.top();
    }
};

// 208. 实现 Trie (前缀树)
class Trie {
private:
    vector<Trie *> children;
    bool isEnd;

    Trie *searchPrefix(string &prefix) {
        Trie *node = this;
        for (char c:prefix) {
            c -= 'a';
            if (node->children[c] == nullptr) return nullptr;
            node = node->children[c];
        }
        return node;
    }

public:
    /** Initialize your data structure here. */
    Trie() : children(26), isEnd(false) {}

    /** Inserts a word into the trie. */
    void insert(string &word) {
        Trie *node = this;
        for (char ch : word) {
            ch -= 'a';
            if (node->children[ch] == nullptr) {
                node->children[ch] = new Trie();
            }
            node = node->children[ch];
        }
        node->isEnd = true;
    }

    /** Returns if the word is in the trie. */
    bool search(string word) {
        Trie *node = this->searchPrefix(word);
        return node != nullptr && node->isEnd;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        return this->searchPrefix(prefix) != nullptr;
    }
};