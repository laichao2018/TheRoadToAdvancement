//
// Created by LaiChao on 2020/11/7.
//

#include "Important200.h"
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <queue>
#include <list>
#include <unordered_set>
#include <stack>
#include <map>
#include <iostream>
#include <numeric>

using namespace std;

/// ================================== GLOBAL VAR ==================================

vector<string> IpAddressAnswer;
vector<vector<int>> combinationSum_res;
vector<vector<int>> combine_res;

bool IsPalindrome(string s, int i, int j) {
    while (i < j) {
        if (s[i++] != s[j--]) {
            return false;
        }
    }
    return true;
}

bool isSubString(string target, string s) {
    /// 分别从左边开始，检测target是否为s的子列
    int i = 0, j = 0;
    while (i < target.length() && j < s.length()) {
        if (target[i] == s[j]) {
            i++;
        }
        j++;
    }
    return i == target.length();
}

/// 278. 第一个错误的版本-----提供的一个假设的使用接口
bool isBadVersion(int version) {
    return 0;
}

vector<TreeNode *> generateTree(int start, int end) {
    if (start > end) {
        return {nullptr};
    }
    vector<TreeNode *> allTrees;
    // 枚举可行根节点
    for (int i = start; i <= end; i++) {
        // 获得所有可行的左子树集合
        vector<TreeNode *> leftTrees = generateTree(start, i - 1);

        // 获得所有可行的右子树集合
        vector<TreeNode *> rightTrees = generateTree(i + 1, end);

        // 从左子树集合中选出一棵左子树，从右子树集合中选出一棵右子树，拼接到根节点上
        for (auto &left : leftTrees) {
            for (auto &right : rightTrees) {
                TreeNode *currTree = new TreeNode(i);
                currTree->left = left;
                currTree->right = right;
                allTrees.emplace_back(currTree);
            }
        }
    }
    return allTrees;
}

void binaryTreePath(TreeNode *root, vector<string> &res, string path) {
    path += to_string(root->val);
    if (root->left == nullptr && root->right == nullptr) {
        res.push_back(path);
        return;
    }
    if (root->left) {
        binaryTreePath(root->left, res, path + "->");
    }
    if (root->right) {
        binaryTreePath(root->right, res, path + "->");
    }
}

int find__circleNum(int x, vector<int> &pre) {
    return pre[x] == x ? x : pre[x] = find__circleNum(pre[x], pre);    ////“pre[x] = ”这句为路径压缩，直接指向组的根节点，下次查询时就快很多了。
}

/// 判断是否为有效的ip字段
bool isValidIP(const string &ip) {
    int val = stoi(ip.c_str());
    if (val > 255) {
        return false;
    }
    if (ip.length() >= 2 && ip[0] == '0') {
        return false;
    }
    return true;
}

///path存放此时从s[0,...,pos-1]找到的ip子串，size最大值为4
void findIpAddress(const string &s, int pos, vector<string> &path) {
    int maxSize = (4 - path.size()) * 3;    //// 剩余位数的最大长度，最大为12： 3 - 3 - 3 - 3
    /// 若剩余位数大于最大剩余位数长度，可提前终止 (多了)
    if (s.size() - pos > maxSize) {
        return;
    }
    ///ip字串的个数为4并且保证pos已经到s的末尾
    if (path.size() == 4 && pos == s.size()) {    /// Ip地址一共四个位
        //// 这是一个正确的结果，保存
        /// 构造ip
        string str = path[0] + "." + path[1] + "." + path[2] + "." + path[3];
        IpAddressAnswer.push_back(str);
        return;
    }

    //// 这一步开始回溯
    /// i <= pos+2 最多移动三个位置
    for (int i = pos; i < s.size() && i <= pos + 2; i++) {
        string ip = s.substr(pos, i - pos + 1);
        if (isValidIP(ip)) {
            path.push_back(ip);
            findIpAddress(s, i + 1, path);
            path.pop_back(); /// 手动对path进行回溯，找完之后清空
        }
    }
}

bool exist_backtrack(vector<vector<char>> &board, string &word, int wordIndex, int x, int y) {
    if (board[x][y] != word[wordIndex]) {
        return false;
    }
    if (wordIndex == word.size() - 1) {
        return true;
    }

    char tmp = board[x][y];
    board[x][y] = 0;
    wordIndex++;

    if ((x > 0 && exist_backtrack(board, word, wordIndex, x - 1, y)) // 往上走
        || (y > 0 && exist_backtrack(board, word, wordIndex, x, y - 1)) // 往左走
        || (x < board.size() - 1 && exist_backtrack(board, word, wordIndex, x + 1, y)) // 往下走
        || (y < board[0].size() - 1 && exist_backtrack(board, word, wordIndex, x, y + 1))) {    ///右
        return true;
    }

    board[x][y] = tmp;
    return false;
}

void permute_backtrack(vector<vector<int>> &res, vector<int> &output, int first, int len) {
    /// 所有的数字都填充完毕
    if (first == len) {
        res.emplace_back(output);
        return;
    }
    for (int i = first; i < len; i++) {
        swap(output[i], output[first]);    /// 动态维护数组
        permute_backtrack(res, output, first + 1, len);    /// 继续递归找下一个数
        swap(output[i], output[first]);    /// 撤销操作
    }
}

void backtrack_permute(vector<int> &nums, vector<vector<int>> &res, int level) {
    ////// 相较于不检查的重复，本题增加一个枚举过程检查
    if (level == nums.size()) {
        res.push_back(nums);
        return;
    }
    //// 枚举的时候去重，只使用没有排过的
    unordered_set<int> uniq;        ///定义在这
    for (int i = level; i < nums.size(); i++) {
        if (uniq.count(nums[i])) {    /// 存在返回1，不存在返回0
            continue;    /// 已经使用过
        }
        swap(nums[level], nums[i]);
        backtrack_permute(nums, res, level + 1);
        swap(nums[level], nums[i]);
        uniq.insert(nums[i]);
    }
}

void combine_backtrack(int n, int k, int start, vector<int> &path) {
    if (path.size() == k) {
        //// 这个满了
        combine_res.push_back(path);
        return;
    }
    for (int i = start; i <= n; i++) {
        path.push_back(i);
        combine_backtrack(n, k, i + 1, path);
        path.pop_back();
    }
}

void combinationSum_backtrack(vector<int> &candidates, vector<int> &comb, int last, int total, int target) {
    if (total == target) {
        combinationSum_res.push_back(comb);
        return;
    }
    for (int i = last; i < candidates.size(); i++) {
        if (total + candidates[i] > target) {
            continue;
        }
        comb.push_back(candidates[i]);
        combinationSum_backtrack(candidates, comb, i, total + candidates[i], target);
        comb.pop_back();
    }
    return;
}

void combinationSum2_backtrack(vector<int> &candidate, vector<int> &comb, int start, int target) {
    if (target == 0) {
        combinationSum_res.push_back(comb);
        return;
    }
    for (int i = start; i < candidate.size(); i++) {
        if (target - candidate[i] < 0) {
            break;    /// 无解
        }
        /// i > start 是为保证第一次执行函数的时候不出错
        if (i > start && candidate[i] == candidate[i - 1]) {
            continue;    ////相同层数相同数字只可以使用一次
        }
        comb.push_back(candidate[i]);
        combinationSum2_backtrack(candidate, comb, i + 1, target - candidate[i]);
        comb.pop_back();
    }
    return;
}

int __rob__(vector<int> &nums, int pos) {
    if (pos == 0) {
        return nums[0];
    }
    if (pos == 1) {
        return max(nums[0], nums[1]);
    }
    int a = __rob__(nums, pos - 1);
    int b = __rob__(nums, pos - 2) + nums[pos];
    return max(a, b);
}

// 求解最大公约数问题
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

// 求解最小公约数 (最小公倍数为两数的乘积除以最大公约数)
int lcm(int a, int b) {
    return a * b / gcd(a, b);
}

// 120. 三角形最小路径和 === === === === === === 递归解法
int rec_min(vector<vector<int>> &triangle, int floor, int index) {
    if (floor == triangle.size()) {
        return 0;
    }
    if (index == triangle[floor].size()) {
        return 0;
    }
    return triangle[floor][index] + max(rec_min(triangle, floor + 1, index), rec_min(triangle, floor + 1, index + 1));
}

///// ================================== TwoPointer FUNC ==================================
vector<int> TwoPointer::twoSum(vector<int> &nums, int target) {
    /// 暴力解法时间复杂度更高
    /// 选用一遍哈希的方法
    unordered_map<int, int> answer;
    for (int i = 0; i < nums.size(); i++) {
        if (answer.find(target - nums[i]) != answer.end()) {    /// 在answer中已经存在对应的键值
            return {answer[target - nums[i]], i};    /// answer[target-nums[i]]为已经加入map的元素的索引，所以小于本轮循环中的i，放前面
        }
        answer[nums[i]] = i;    /// 添加元素，前者为元素值，后为索引
    }
    return {};    /// 无答案
}

bool TwoPointer::judgeSquareSum(int c) {
    //// 双指针
    //// 最新的测试案例出现了大数，，，所以使用的long long int
    long long int pre_num = 0, beh_num = (int) sqrt(c);
    while (pre_num <= beh_num) {
        long long int curr_sum = pre_num * pre_num + beh_num * beh_num;
        if (curr_sum == c) {
            return true;
        } else if (curr_sum < c) {
            pre_num++;
        } else {
            beh_num--;
        }
    }
    return false;
}

string TwoPointer::reverseVowels(string s) {
    if (s.length() < 2) {
        return s;
    }
    string sAllVowels = "aeiouAEIOU";
    int left = 0, right = s.length() - 1;
    while (left < right) {
        /*while (sAllVowels.find(s[left]) == string::npos && left < right) {
            left++;
        }
        while (sAllVowels.find(s[right]) == string::npos && left < right) {
            right--;
        }
        if (left < right) {
            swap(s[left], s[right]);
            left++, right--;
        }*/
    }
    return s;
}

bool TwoPointer::validPalindrome(string s) {
    for (int i = 0, j = s.length() - 1; i < j; i++, j--) {
        if (s[i] != s[j]) {
            return IsPalindrome(s, i, j - 1) || IsPalindrome(s, i + 1, j);
        }
    }
    return true;
}

void TwoPointer::merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
    int i = nums1.size() - 1;
    m--, n--;
    while (n >= 0) {
        while (m >= 0 && nums1[m] > nums2[n]) {
            swap(nums1[i--], nums1[m--]);
        }
        swap(nums1[i--], nums2[n--]);
    }
}

bool TwoPointer::hasCycle(ListNode *head) {
    /// 判断是否有环，使用快慢两个指针，有环必会相遇
    if (head == nullptr) {
        return false;
    }
    ListNode *fast = head->next, *slow = head;
    while (fast != nullptr && slow != nullptr && fast->next != nullptr) {    //=== fast->next != nullptr
        if (fast == slow) {
            return true;
        }
        fast = fast->next->next;
        slow = slow->next;
    }
    return false;
}

string TwoPointer::findLongestWord(string s, vector<string> &d) {
    if (d.empty()) {
        return "";
    }
    string answer = "";
    for (int i = 0; i < d.size(); i++) {
        int target_len = answer.length();
        int dir_len = d[i].length();
        /// 如果字符串更短或一样但字母顺序更大则跳过
        if (target_len > dir_len || (target_len == dir_len && answer.compare(d[i]) < 0)) {
            continue;
        }
        if (isSubString(answer, s)) {
            answer = d[i];
        }
    }
    return answer;
}

///// ================================== Sort FUNC ==================================

int Sort::findKthLargest(vector<int> &nums, int k) {
    //// 直接用库函数吧，，其他人的快排方法以及分治算法暂时跳过。。。。
    sort(nums.begin(), nums.end(), [](int a, int b) { return a > b; });
    return nums[k - 1];
}

vector<int> Sort::topKFrequent(vector<int> &nums, int k) {
    unordered_map<int, int> numHash;
    for (int i = 0; i < nums.size(); i++) {
        numHash[nums[i]]++;
    }
    vector<pair<int, int>> vNumCounts;
    for (int i = 0; i < nums.size(); i++) {
        if (numHash[nums[i]] != 0) {
            vNumCounts.push_back(make_pair(numHash[nums[i]], nums[i]));  /// 次数，数字
            numHash[nums[i]] = 0;
        }
    }
    sort(vNumCounts.begin(), vNumCounts.end(), [](pair<int, int> a, pair<int, int> b) { return a.first > b.first; });
    vector<int> resVec;
    for (int i = 0; i < k; i++) {
        resVec.push_back(vNumCounts[i].second);
    }
    return resVec;
}

string Sort::frequencySort(string s) {
    string answer;
    unordered_map<char, int> ump;
    for (const auto c : s) {
        ump[c]++;
    }
    /// int,char 用于排序
    //priority_queue<pair<int, char>, vector<pair<char, int>>, less<>>q;	//// 默认也为小根堆
    priority_queue<pair<int, char>> q;
    for (const auto m : ump) {
        q.push({m.second, m.first});
    }
    while (!q.empty()) {
        auto tmp = q.top();
        q.pop();
        answer.append(tmp.first, tmp.second);
    }
    return answer;
}

void Sort::sortColors(vector<int> &nums) {
    /// sort(nums.begin(), nums.end());				// -.-|
    if (nums.size() < 2) {
        return;
    }
    ///我们用三个指针（p0, p2 和curr）来分别追踪0的最右边界，2的最左边界和当前考虑的元素。
    int p0 = 0, curr = 0;
    int p2 = nums.size() - 1;
    while (curr <= p2) {
        if (nums[curr] == 0) {
            swap(nums[curr], nums[p0]);
            curr++, p0++;    ///因为curr左边的值已经扫描过了，所以curr要++继续扫描下一位
        } else if (nums[curr] == 2) {
            swap(nums[curr], nums[p2]);
            p2--;    ///与p2交换的值，curr未扫描，要停下来扫描一下，所以curr不用++。
        } else {
            curr++;
        }
    }
}

///// ================================== GreedyThinking FUNC ==================================

int GreedyThinking::findContentChildren(vector<int> &g, vector<int> &s) {
    if (g.empty() || s.empty()) {
        return 0;
    }
    int answer = 0;
    int child_pos = 0;
    int candy_pos = 0;
    while (child_pos < g.size() && candy_pos < s.size()) {
        if (g[child_pos] <= s[candy_pos]) {
            answer++;
            child_pos++;
            candy_pos++;
        } else {
            candy_pos++;
        }
    }
    return answer;
}

int GreedyThinking::eraseOverlapIntervals(vector<vector<int>> &intervals) {
    if (intervals.empty()) {
        return 0;
    }
    int answer = 0;

    /// 按照区间终结点，从小到大排序
    sort(intervals.begin(), intervals.end(), [](vector<int> a, vector<int> b) { return a[1] < b[1]; });
    /// 获取最小的区间终结点
    int end = intervals[0][1];
    for (int i = 1; i < intervals.size(); i++) {
        /// 如果区间的起点，小于上一个区间的终点，说明有交集，要删除
        if (intervals[i][0] < end) {
            ++answer;
        } else {
            /// 没有，交集更新end
            end = intervals[i][1];
        }
    }
    return answer;
}

int GreedyThinking::findMinArrowShots(vector<vector<int>> &points) {
    if (points.empty()) {
        return 0;
    }
    int answer = 1;
    sort(points.begin(), points.end(), [](const vector<int> &a, const vector<int> &b) { return a[1] < b[1]; });
    int xStart, xEnd, firstEnd = points[0][1];
    for (auto p : points) {
        xStart = p[0];
        xEnd = p[1];
        if (firstEnd < xStart) {
            firstEnd = xEnd;
            answer++;
        }
    }
    return answer;
}

vector<vector<int>> GreedyThinking::reconstructQueue(vector<vector<int>> &people) {
    if (people.empty()) {
        return {};
    }

    /// 首先根据身高进行排序，如果身高一样就按照第二个元素从小到大排序
    sort(people.begin(), people.end(),
         [](vector<int> &a, vector<int> &b) { return a[0] == b[0] ? a[1] < b[1] : a[0] > b[0]; });

    /// 排序后： [7,0], [7,1], [6,1], [5,0], [5,2], [4,4]
    // 再一个一个插入。
    // [7,0]
    // [7,0], [7,1]
    // [7,0], [6,1], [7,1]
    // [5,0], [7,0], [6,1], [7,1]
    // [5,0], [7,0], [5,2], [6,1], [7,1]
    // [5,0], [7,0], [5,2], [6,1], [4,4], [7,1]

    list<vector<int>> k;    //// 因为会进行许多插入操作，使用list速度更快
    for (int i = 0; i < people.size(); i++) {
        auto pos = k.begin();
        advance(pos, people[i][1]);
        k.insert(pos, people[i]);
    }
    return vector<vector<int>>(k.begin(), k.end());
}

int GreedyThinking::maxProfit(vector<int> &prices) {
    if (prices.empty()) {
        return 0;
    }
    int max_profit = 0;
    int buy_in = prices[0];
    for (auto p : prices) {
        if (p < buy_in) {
            buy_in = p;
        } else {
            max_profit = max(max_profit, (p - buy_in));
        }
    }
    return max_profit;
}

int GreedyThinking::maxProfit2(vector<int> &prices) {
    /// 这次可以进行多次交易
    if (prices.empty()) {
        return 0;
    }
    ///该方法有点奇淫巧计的意味，但是一旦想通便很快就可以完成，且只需要一次遍历。其主要想法是逢低便买入，逢高便卖出，即只要前一天的价格小于后一天的价格，那么就可以在前一天买入后一天卖出。
    int max_profit = 0;
    for (int i = 1; i < prices.size(); i++) {
        if (prices[i] > prices[i - 1]) {
            max_profit += (prices[i] - prices[i - 1]);
        }
    }
    return max_profit;
}

vector<vector<int>> GreedyThinking::findSubsequences(vector<int> &nums) {
    if (nums.size() < 2) {
        return {};
    }
    sort(nums.begin(), nums.end());
    vector<vector<int>> subNums;
    for (int i = 0; i < nums.size() - 1; i++) {
        vector<int> tmpVec;
        for (int j = i + 1; j < nums.size(); j++) {
            tmpVec.push_back(nums[j]);
            subNums.push_back(tmpVec);
        }
    }
    return subNums;
}

bool GreedyThinking::canPlaceFlowers(vector<int> &flowerbed, int n) {
    if (n == 0) {
        return true;
    }
    /// 实际就是判断多少个连续零的问题
    /// 首位插入0
    int count = 0;
    flowerbed.insert(flowerbed.begin(), 0);
    flowerbed.insert(flowerbed.end(), 0);
    for (int i = 1; i < flowerbed.size() - 1; i++) {
        if (flowerbed[i] == 0 && flowerbed[i - 1] == 0 && flowerbed[i + 1] == 0) {
            count++;
            flowerbed[i] = 1;    /// 这个位置种上花
        }
    }
    return count >= n;
}

bool GreedyThinking::isSubsequence(string s, string t) {
    /// 自己的方法解答的，居然双百，哈哈哈
    if (s.empty()) {
        return true;
    }
    s.insert(s.end(), '.');
    int s_pos = 0, t_pos = 0;
    while (s_pos < s.length() && t_pos < t.length()) {
        char s_curr_char = s[s_pos];
        if (s_curr_char == t[t_pos]) {
            s_pos++, t_pos++;
        } else {
            t_pos++;
        }
    }
    return s_pos == s.length() - 1;
}

bool GreedyThinking::checkPossibility(vector<int> &nums) {
    int count = 0;    /// 要修改的个数
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i - 1] > nums[i]) {
            if (i - 2 >= 0 && nums[i - 2] > nums[i]) {
                nums[i] = nums[i -
                               1];    //一般不修改nums[i]的值，比较特别的情况就是 nums[i] < nums[i - 2]，修改 nums[i - 1] = nums[i] 不能使数组成为非递减数组，只能修改 nums[i] = nums[i - 1]
            } else {
                nums[i - 1] = nums[i];
            }
            count++;
        }
    }
    return count < 2;
}

int GreedyThinking::maxSubArray(vector<int> &nums) {
    if (nums.empty()) {
        return 0;
    }
    int curr_sum = nums[0];
    int max_sum = curr_sum;
    for (int i = 1; i < nums.size(); i++) {
        curr_sum = curr_sum > 0 ? curr_sum + nums[i] : nums[i];        ///只有当之前的和大于0的时候才加上，不然就为现在的值，，，，
        max_sum = max(curr_sum, max_sum);
    }
    return max_sum;
}

vector<int> GreedyThinking::partitionLabels(string S) {
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

///// ================================== BinarySearch FUNC ==================================

int BinarySearch::mySqrt(int x) {
    /// 使用二分查找
    if (x == 1 || x == 0) {
        return x;
    }
    int left = 0, right = x;
    while (right - left != 1) {
        int mid = (right + left) / 2;    /// 中值还有一种计算方法，可以防止加法溢出 mid = left + (right - left) / 2;
        if (mid == x / mid) {
            return mid;    /// 查找到结果
        } else if (mid > x / mid) {
            right = mid;
        } else {
            left = mid;
        }
    }
    return left;    /// 最后返回值为什么是left不是right?  ===> 就像要输入8结果是2.82...结果要向下取整，所以选择较小的left
}

char BinarySearch::nextGreatestLetter(vector<char> &letters, char target) {
    int left = 0, right = letters.size() - 1;
    if (target >= letters[right] || target < letters[left]) {
        return letters[0];    /// 不在范围内的话，直接返回第一个字符
    }
    while (right - left > 1) {
        int mid = left + (right - left) / 2;
        if (letters[mid] > target) {    /// 表示结果在左边
            right = mid;
        } else {
            left = mid;
        }
    }
    return letters[right];    /// 因为是要找到比target大的，所以是right，如果是要找到target就是left
}

int BinarySearch::singleNonDuplicate(vector<int> &nums) {
    /*/// 暴力解法
    if (nums.empty() || nums.size() % 2 == 0) {
        return {};
    }
    if (nums.size() == 1) {
        return nums[0];
    }
    for (int i = 0; i < nums.size() - 1; i += 2) {
        int curr_num = nums[i];
        if (nums[i] != nums[i + 1]) {
            return nums[i];
        }
    }
    return nums.back();	/// 这种情况就是在最后一个位置*/

    /// 二分查找法
    int low = 0, high = nums.size() - 1;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (mid % 2 == 1) {        /// 需要确保 mid 是偶数，如果为奇数，则将其减 1
            mid--;
        }
        if (nums[mid] == nums[mid + 1]) {    /// 偶数索引必须是两个数字的开始那一个
            low = mid + 2;    /// mid 不是单个元素。且单个元素在 mid 之后。则我们将 low 设置为 mid + 2
        } else {
            high = mid;        /// 单个元素位于 mid，或者在 mid 之前
        }
    }
    return nums[low];        /// 当前搜索空间为 1 个元素，那么该元素为单个元素，我们将返回它
}

int BinarySearch::firstBadVersion(int n) {
    /// 肯定是选择使用二分查找
    int low = 0, high = n;
    while (high > low) {
        int mid = low + (high - low) / 2;
        if (isBadVersion(mid)) {    /// mid错了，则错在前
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    return low;
}

int BinarySearch::findMin(vector<int> &nums) {
    int low = 0, high = nums.size() - 1;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] > nums[high]) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    return nums[low];
}

vector<int> BinarySearch::searchRange(vector<int> &nums, int target) {
    vector<int> answer{-1, -1};
    if (nums.size() < 1) {
        return answer;
    }
    int left = 0, right = nums.size();
    while (left < right) {
        int mid = (right + left) / 2;
        nums[mid] < target ? left = mid + 1 : right = mid;
    }
    if (left == nums.size()) {
        return answer;
    }
    if (nums[left] == target) {
        answer[0] = left;
    } else {
        return answer;
    }

    right = nums.size();
    while (left < right) {
        int mid = (left + right) / 2;
        target < nums[mid] ? right = mid : left + mid + 1;
    }
    answer[1] = left - 1;
    return answer;
}

///// ================================== DivideConquerAlgorithm FUNC ==================================

vector<int> DivideConquerAlgorithm::diffWaysToCompute(string input) {
    vector<int> answer;
    for (int i = 0; i < input.size(); i++) {
        char curr_char = input[i];
        if (curr_char == '+' || curr_char == '-' || curr_char == '*') {
            auto res01 = diffWaysToCompute(input.substr(0, i));
            auto res02 = diffWaysToCompute(input.substr(i + 1));
            for (auto _i : res01) {
                for (auto _j : res02) {
                    if (curr_char == '+') {
                        answer.push_back(_i + _j);
                    }
                    if (curr_char == '-') {
                        answer.push_back(_i - _j);
                    }
                    if (curr_char == '*') {
                        answer.push_back(_i * _j);
                    }
                }
            }
        }
    }
    if (answer.empty()) {
        return {stoi(input)};
    }
    return answer;
}

vector<TreeNode *> DivideConquerAlgorithm::generateTrees(int n) {
    if (n == 0) {
        return {};
    }
    vector<TreeNode *> answer;
    answer = generateTree(1, n);
    return answer;
}

///// ================================== Search FUNC ==================================

int Search::shortestPathBinaryMatrix(vector<vector<int>> &grid) {
    vector<vector<int>> step{{0,  1},
                             {0,  -1},
                             {1,  0},
                             {-1, 0},
                             {1,  1},
                             {1,  -1},
                             {-1, 1},
                             {-1, -1}};
    int n = grid.size();
    if (grid[0][0] || grid[n - 1][n - 1]) {
        return -1;        /// 首尾被堵塞
    }
    int answer = 1;        /// 开始位置算进去了
    queue<pair<int, int>> q;
    q.push(make_pair(0, 0));
    grid[0][0] = 2;
    while (!q.empty()) {
        int curr_size = q.size();
        for (int i = 0; i < curr_size; i++) {
            int curr_x = q.front().first;
            int curr_y = q.front().second;
            q.pop();
            if (curr_x == n - 1 && curr_y == n - 1) {
                return answer;
            }
            for (int j = 0; j < 8; j++) {
                int x1 = curr_x + step[j][0];
                int y1 = curr_y + step[j][1];
                if (x1 < 0 || y1 < 0 || x1 >= n || y1 >= n || grid[x1][y1]) {
                    continue;    /// 越界或者已经被访问过
                }
                grid[x1][y1] = 2;
                q.push(make_pair(x1, y1));
            }
        }
        answer++;
    }
    return -1;
}

int Search::numSquares(int n) {
    /*
1，对于正整数N, 所有的解都是 N = 一个整数的平方 + 另一个整数; 直白点, N = AxA + B
2, 而B又是由 "一个整数的平方 + 另一个整数" 组成的; 那么, B = CxC + D
3，总结下就是：N = IxI + N' 而 N' = IxI + N''

4, 本题要解的问题：正整数N最少由多个平方数相加;
5, 那么，N的最优解 = 1 + （N’的最优解）。而N'肯定小于N。
6, 所以本题的思路就是，对每一个N，观察1到N-1中，谁的解最小，那么N的解就是它+1.

7, 但是我们没必要1到N+1中的每一个数都去观察，因为有些组合不满足N = IxI + N'，譬如12 = 2+N'是不需要的，因为2不是某个数的平方。所以我们观察的范围要大大减小。

拿12举例,我们只能观察：
12 = 1 + 11
12 = 4 + 8
12 = 9 + 3
我们要得出3，8，11中谁的解最优，那么12的解就是它+1。

8, 我们从1到N计算, 2的解从1里找，3的解从[2,1]里找，4的解从[3,2,1]里找，依次类推，最后算到N的解即可。
    */
    vector<int> result(n + 1, 0x7FFFFFFF);    /// 每个数的最优解存在result数组
    result[0] = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 1; i - j * j >= 0; j++) {
            result[i] = min(result[i], result[i - j * j] + 1);
        }
    }
    return result.back();
}

int Search::ladderLength(string beginWord, string endWord, vector<string> &wordList) {
    unordered_set<string> s;
    for (auto &i : wordList) {
        s.insert(i);
    }
    queue<pair<string, int>> q;
    q.push({beginWord, 1});

    string tmp;        ///每个节点的字符
    int step;        ///抵达该节点的step
    while (!q.empty()) {
        if (q.front().first == endWord) {
            return q.front().second;
        }
        tmp = q.front().first;
        step = q.front().second;
        q.pop();

        /// 开始寻找下一个单词
        char ch;
        for (int i = 0; i < tmp.length(); i++) {
            ch = tmp[i];
            for (char c = 'a'; c <= 'z'; c++) {
                /// a-z尝试一遍
                if (ch == c) {
                    continue;
                }
                tmp[i] = c;
                /// 如果找的到
                /*
                按个遍历当前单词的每个字母，然后对他进行替换'a'-'z'，如果单词替换之后，能够在我们的节点中找到下一个词，那么就将哪个词加入队列中，同时把该节点移除候选节点。
                */
                if (s.find(tmp) != s.end()) {
                    q.push({tmp, step + 1});    /// 加入队列
                    s.erase(tmp);    /// 删除该节点，防止回退
                }
                tmp[i] = ch;    ///复原
            }
        }
    }
    return 0;
}

int Search::maxAreaOfIsland(vector<vector<int>> &grid) {
    vector<int> dx{0, 1, 0, -1};
    vector<int> dy{-1, 0, 1, 0};
    int answer = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            int curr = 0;
            stack<int> stkI;
            stack<int> stkJ;
            stkI.push(i);
            stkJ.push(j);
            while (!stkI.empty()) {
                int currX = stkI.top(), currY = stkJ.top();
                stkI.pop(), stkJ.pop();
                if (currX < 0 || currY < 0 || currX >= grid.size() || currY >= grid[0].size() ||
                    grid[currX][currY] != 1) {
                    continue;
                }
                ++curr;
                grid[currX][currY] = 0;    /// 可以省略使用bool数组
                for (int k = 0; k < 4; k++) {
                    stkI.push(currX + dx[k]);
                    stkJ.push(currY + dy[k]);
                }
            }
            answer = max(curr, answer);
        }
    }
    return answer;
}

int Search::numIslands(vector<vector<char>> &grid) {
    int answer = 0;
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {-1, 0, 1, 0};
    if (grid.empty()) {
        return answer;
    }
    stack<pair<int, int>> all_pos;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == '1') {
                answer++;
                all_pos.push(make_pair(i, j));
                while (!all_pos.empty()) {
                    int currX = all_pos.top().first;
                    int currY = all_pos.top().second;
                    all_pos.pop();
                    for (int k = 0; k < 4; k++) {
                        int moveX = currX + dx[k];
                        int moveY = currY + dy[k];
                        if (moveX < 0 || moveY < 0 || moveX >= grid.size() || moveY >= grid[0].size() ||
                            grid[moveX][moveY] == '0') {
                            continue;
                        }
                        if (grid[moveX][moveY] == '1') {
                            grid[moveX][moveY] = '0';
                            all_pos.push(make_pair(moveX, moveY));
                        }
                    }
                }
            }
        }
    }
    return answer;
}

int Search::findCircleNum(vector<vector<int>> &M) {
    /// 并查集
    if (M.empty()) {
        return 0;
    }
    vector<int> pre(M.size());
    for (int i = 0; i < M.size(); i++) {
        pre[i] = i;    ///先各自为组，组名也为自己的序号
    }
    int group = M.size();    //一开始有多少人就有多少个朋友圈，当每出现一对朋友时就减1，最后就是总的朋友圈数量了
    for (int i = 0; i < M.size(); i++) {
        for (int j = 0; j < M.size(); j++) {
            if (i != j && M[i][j] == 1) {
                int x1 = find__circleNum(i, pre);    //x1为i所属的组
                int x2 = find__circleNum(j, pre);    //x2为j所属的组
                if (x1 != x2) {
                    //如果不属于同个朋友圈的话就把i归为j的组
                    pre[x1] = x2;
                    group--;
                }
            }
        }
    }
    return group;
}

void Search::solve(vector<vector<char>> &board) {
    if (board.empty()) {
        return;
    }
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {-1, 0, 1, 0};
    vector<vector<bool>> visitPos(board.size(), vector<bool>(board[0].size(), false));
    //// 先找到所有的边界O(如果有的话)
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if ((i == 0 || i == board.size() - 1 || j == 0 || j == board[i].size() - 1) && board[i][j] == 'O' &&
                !visitPos[i][j]) {
                stack<pair<int, int>> tmp_pos;    /// x, y
                tmp_pos.push(make_pair(i, j));
                visitPos[i][j] = true;
                /// 往内延申
                while (!tmp_pos.empty()) {
                    int currX = tmp_pos.top().first;
                    int currY = tmp_pos.top().second;
                    tmp_pos.pop();
                    for (int k = 0; k < 4; k++) {
                        int moveX = currX + dx[k];
                        int moveY = currY + dy[k];
                        if (moveX < 0 || moveX >= board.size() || moveY < 0 || moveY >= board[i].size()) {
                            continue;
                        }
                        if (!visitPos[moveX][moveY] && board[moveX][moveY] == 'O') {
                            tmp_pos.push(make_pair(moveX, moveY));
                            visitPos[moveX][moveY] = true;
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] == 'O' && !visitPos[i][j]) {
                board[i][j] = 'X';
            }
        }
    }
    return;
}

vector<vector<int>> Search::pacificAtlantic(vector<vector<int>> &matrix) {
    vector<vector<int>> answer;
    int m = matrix.size();
    if (matrix.empty()) {
        return {};
    }
    int n = matrix[0].size();
    //声明pacific和atlantic两个二维数组，记录可流到两大洋的位置
    vector<vector<int>> pacific(m, vector<int>(n, 0));
    vector<vector<int>> atlantic(m, vector<int>(n, 0));
    ///得到位置的方法直接用 =BFS= 从一定可以流到的位置开始扩散，直到找不到新的位置时，即得到了所有可能的位置。
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {-1, 0, 1, 0};
    /// 找太平洋
    queue<pair<int, int>> Q;
    for (int i = 0; i < m; i++) {
        pacific[i][0] = 1;    ///一定可以流入太平洋，保存可以流入的位置
        Q.push(make_pair(i, 0));
    }
    for (int i = 0; i < n; i++) {
        pacific[0][i] = 1;    /// 可以流入的话标记为1
        Q.push(make_pair(0, i));
    }
    while (!Q.empty()) {
        auto pos = Q.front();
        Q.pop();

        for (int d = 0; d < 4; d++) {
            int ii = pos.first + dx[d];
            int jj = pos.second + dy[d];
            if (ii < 0 || jj < 0 || ii > m - 1 || jj > n - 1) {
                continue;
            }
            if (pacific[ii][jj]) {    ///已经遍历过了
                continue;
            }
            /// 如果新的位置比原来的大或者相等，那么一定可以流回去，并流入太平洋
            if (matrix[ii][jj] >= matrix[pos.first][pos.second]) {
                pacific[ii][jj] = 1;
                Q.push(make_pair(ii, jj));
            }
        }
    }

    for (int i = 0; i < m; i++) {
        atlantic[i][n - 1] = 1;
        Q.push(make_pair(i, n - 1));
    }
    for (int i = 0; i < n; i++) {
        atlantic[m - 1][i] = 1;
        Q.push(make_pair(m - 1, i));
    }
    while (!Q.empty()) {
        auto pos = Q.front();
        Q.pop();

        for (int k = 0; k < 4; k++) {
            int ii = pos.first + dx[k];
            int jj = pos.second + dy[k];
            if (ii < 0 || jj < 0 || ii > m - 1 || jj > n - 1) {
                continue;
            }
            if (atlantic[ii][jj] == 1) {
                continue;
            }
            if (matrix[ii][jj] >= matrix[pos.first][pos.second]) {
                atlantic[ii][jj] = 1;
                Q.push(make_pair(ii, jj));
            }
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (atlantic[i][j] && pacific[i][j]) {
                answer.push_back(vector<int>{i, j});
            }
        }
    }
    return answer;
}

vector<string> Search::letterCombinations(string digits) {
    //  1.建立一个map哈希表；
    //	2.新建一个队列；
    //	3.将第一个字符串所对应的码表逐步进入到队列中；
    //	4.出队操作，存储当前出队的string；
    //	5.将此string与后一个字符串所对应的码表中每一个值相加并逐步进入到队列中；
    //	6.最终队列中存储的即为所有情况的string
    vector<string> answer;
    map<char, string> m = {{'2', "abc"},
                           {'3', "def"},
                           {'4', "ghi"},
                           {'5', "jkl"},
                           {'6', "mno"},
                           {'7', "pqrs"},
                           {'8', "tuv"},
                           {'9', "wxyz"}};//映射map哈希表
    int size = digits.size();    /// 输入字符串的长度
    queue<string> que;    ///新建队列

    ///将第一个元素对应的码表入列
    for (int i = 0; i < m[digits[0]].size(); i++) {
        string str;
        str.push_back(m[digits[0]][i]);    ///char -> string
        que.push(str);    ///string入队
    }

    string s;    ///用于存储队头元素
    for (int i = 1; i < size; i++) {
        int length = que.size();    //当前队列的长度
        while (length--) {
            for (int j = 0; j < m[digits[i]].size(); j++) {
                s = que.front();
                s += m[digits[i]][j];    ///队头元素加上新元素
                que.push(s);
            }
            que.pop();    ///队头出队
        }
    }

    while (!que.empty()) {
        answer.push_back(que.front());
        que.pop();
    }

    return answer;
}

vector<string> Search::restoreIpAddresses(string s) {
    if (s.length() < 4) {
        return {};
    }
    vector<string> path;
    findIpAddress(s, 0, path);

    return IpAddressAnswer;
}

bool Search::exist(vector<vector<char>> &board, string word) {
    ////回溯法
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (exist_backtrack(board, word, 0, i, j)) {
                return true;    //从表格的每一个位置出发
            }
        }
    }
    return false;
}

vector<string> Search::binaryTreePaths(TreeNode *root) {
    if (root == nullptr) {
        return {};
    }
    vector<string> res;
    binaryTreePath(root, res, "");
    return res;
}

vector<vector<int>> Search::permute(vector<int> &nums) {
    vector<vector<int>> res;
    permute_backtrack(res, nums, 0, (int) nums.size());
    return res;
}

vector<vector<int>> Search::permuteUnique(vector<int> &nums) {
    vector<vector<int>> res;
    backtrack_permute(nums, res, 0);
    return res;
}

vector<vector<int>> Search::combine(int n, int k) {
    vector<int> path;
    combine_backtrack(n, k, 1, path);    //// 从第1个开始抽离
    return combine_res;
}

vector<vector<int>> Search::combinationSum(vector<int> &candidates, int target) {
    vector<int> comb;
    sort(candidates.begin(), candidates.end(), [](int a, int b) { return a < b; });
    if (candidates.empty()) {
        return {};
    }
    combinationSum_backtrack(candidates, comb, 0, 0, target);
    return combinationSum_res;
}

vector<vector<int>> Search::combinationSum2(vector<int> &candidates, int target) {
    if (candidates.empty()) {
        return {};
    }
    vector<int> comb;
    sort(candidates.begin(), candidates.end(), [](int a, int b) { return a < b; });
    combinationSum2_backtrack(candidates, comb, 0, target);
    return combinationSum_res;
}

///// ================================== DynamicProgramming FUNC ==================================

int DynamicProgramming::climbStairs(int n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    if (n == 2) {
        return 2;
    }
    return climbStairs(n - 1) + climbStairs(n - 2);
}

int DynamicProgramming::climbStairs_dp(int n) {
    if (n == 1) {
        return 1;
    }
    if (n == 2) {
        return 2;
    }
    //// 以空间换时间
    vector<int> dpArr(n + 1, 0);
    dpArr[0] = 0;
    dpArr[1] = 1;
    dpArr[2] = 2;
    for (int i = 3; i <= n; i++) {
        dpArr[i] = dpArr[i - 1] + dpArr[i - 2];
    }

    return dpArr[n];
}

bool DynamicProgramming::isTarget(vector<int> &arr, int pos, int target) {
    if (target == 0) {
        return false;
    }
    if (pos == 0) {
        return target == arr[0];
    }
    if (target < arr[pos]) {
        return isTarget(arr, pos - 1, target);    //// 只有全是正整数的情况
    }
    bool a = isTarget(arr, pos - 1, target);
    bool b = isTarget(arr, pos - 1, target - arr[pos]);
    return a || b;
}

int DynamicProgramming::addMaxSum_rec(vector<int> &arr, int pos) {
    if (pos == 0) {
        return arr[pos];
    }
    if (pos == 1) {
        return max(arr[0], arr[1]);
    }
    int a = addMaxSum_rec(arr, pos - 2) + arr[pos];
    int b = addMaxSum_rec(arr, pos - 1);
    return max(a, b);
}

int DynamicProgramming::addMaxSum_dp(vector<int> &arr, int pos) {
    vector<int> dpArr(arr.size(), 0);
    dpArr[0] = arr[0];
    dpArr[1] = max(arr[0], arr[1]);
    for (int i = 2; i < arr.size(); i++) {
        int a = arr[i] + dpArr[i - 2];
        int b = dpArr[i - 1];
        dpArr[i] = max(a, b);
    }
    return dpArr.back();
}

int DynamicProgramming::rob_rec(vector<int> &nums) {
    if (nums.empty()) {
        return 0;
    }
    return __rob__(nums, nums.size() - 1);
}

int DynamicProgramming::rob_dp(vector<int> &nums) {
    if (nums.empty()) {
        return 0;
    }
    if (nums.size() == 1) {
        return nums[0];
    }
    if (nums.size() == 2) {
        return max(nums[0], nums[1]);
    }
    vector<int> dpArr(nums.size(), 0);
    dpArr[0] = nums[0];
    dpArr[1] = max(nums[0], nums[1]);
    for (int i = 2; i < nums.size(); i++) {
        int a = dpArr[i - 1];
        int b = nums[i] + dpArr[i - 2];
        dpArr[i] = max(a, b);
    }
    return dpArr.back();
}

int DynamicProgramming::rob_circle(vector<int> &nums) {
    if (nums.empty()) {
        return 0;
    }
    if (nums.size() == 1) {
        return nums[0];
    }
    if (nums.size() == 2) {
        return max(nums[0], nums[1]);
    }
    int fir_pre1 = 0, fir_pre2 = 0;
    for (int i = 0; i < nums.size() - 1; i++) {
        int curr = max(fir_pre1, fir_pre2 + nums[i]);
        fir_pre2 = fir_pre1;
        fir_pre1 = curr;
    }
    int sec_pre1 = 0, sec_pre2 = 0;
    for (int i = 1; i < nums.size(); i++) {
        int curr = max(sec_pre1, sec_pre2 + nums[i]);
        sec_pre2 = sec_pre1;
        sec_pre1 = curr;
    }
    return max(fir_pre1, sec_pre1);
}

int DynamicProgramming::minPathSum(vector<vector<int>> &grid) {
    if (grid.empty() || grid[0].empty()) {
        return 0;
    }
    for (int i = 1; i < grid.size(); i++) {
        grid[i][0] = grid[i - 1][0] + grid[i][0];
    }
    for (int i = 1; i < grid[0].size(); i++) {
        grid[0][i] = grid[0][i - 1] + grid[0][i];
    }
    for (int i = 1; i < grid.size(); i++) {
        for (int j = 1; j < grid[0].size(); j++) {
            grid[i][j] = min(grid[i - 1][j], grid[i][j - 1]) + grid[i][j];
        }
    }
    return grid[grid.size() - 1][grid[0].size() - 1];
}

int DynamicProgramming::uniquePaths(int m, int n) {
    if (m == 0 || n == 0) {
        return 0;
    }
    vector<vector<int>> dpArr(m, vector<int>(n, 0));
    dpArr[0][0] = 0;
    for (int i = 1; i < m; i++) {
        dpArr[i][0] = 1;
    }
    for (int i = 0; i < n; i++) {
        dpArr[0][i] = 1;
    }
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dpArr[i][j] = dpArr[i - 1][j] + dpArr[i][j - 1];
        }
    }
    return dpArr[m - 1][n - 1];
}

int DynamicProgramming::numberOfArithmeticSlices(vector<int> &A) {
    if (A.size() < 3) {
        return 0;
    }
    vector<int> dpArr(A.size(), 0);
    for (int i = 2; i < A.size(); i++) {
        dpArr[i] = (A[i] - A[i - 1]) == (A[i - 1] - A[i - 2]) ? dpArr[i - 1] + 1 : 0;
    }
    return accumulate(dpArr.begin(), dpArr.end(), 0);
}

int DynamicProgramming::integerBreak(int n) {
    // 由于每个正整数对应的最大乘积取决于比它小的正整数对应的最大乘积，因此可以使用动态规划求解。
    if (n < 2) {
        return 0;
    }
    vector<int> dpArr(n + 1);
    for (int i = 2; i < n + 1; i++) {
        int currMAX = 0;
        for (int j = 1; j < i; j++) {    // 拆成 0 没有意义
            int a = j * (i - j);            // (i-j)将不被继续拆分
            int b = j * dpArr[i - j];        // (i-j)将继续拆分，并取最大值
            currMAX = max(currMAX, max(a, b));
        }
        dpArr[i] = currMAX;
    }
    return dpArr.back();
}

int DynamicProgramming::numSquares(int n) {
    // 给定正整数 n，找到若干个完全平方数（比如 1, 4, 9, 16, ...）使得它们的和等于 n。你需要让组成和的完全平方数的个数最少。
    vector<int> dpArr(n + 1, n);
    dpArr[0] = 0;
    for (int i = 1; i < n + 1; i++) {
        for (int j = sqrt(i); j > 0; j--) {
            dpArr[i] = min(dpArr[i], dpArr[i - j * j] + 1);
        }
    }
    return dpArr.back();
}

int DynamicProgramming::numDecodings(string s) {
    if (s[0] == '0') {
        return 0;
    }
    int pre = 1, curr = 1;
    for (int i = 1; i < s.size(); i++) {
        int tmp = curr;
        if (s[i] == '0') {
            if (s[i - 1] == '1' || s[i - 1] == '2') {
                curr = pre;
            } else {
                return 0;
            }
        } else if (s[i - 1] == '1' || s[i - 1] == '2' && (s[i] >= 1 && s[i] <= '6')) {
            curr += pre;
        }
        pre = tmp;
    }
    return curr;
}

int DynamicProgramming::minimumTotal(vector<vector<int>> &triangle) {
    if (triangle.empty()) {
        return 0;
    }
    vector<vector<int>> dpArr(triangle.size(), vector<int>(triangle.back().size(), 0));
    dpArr[0][0] = triangle[0][0];
    int index = 0;
    for (int i = 1; i < triangle.size(); i++) {
        dpArr[i][0] = (dpArr[i - 1][0] + triangle[i][0]);
    }
    for (int i = 1; i < triangle.size(); i++) {
        for (int j = 1; j < triangle[i].size(); j++) {
            int a = triangle[i][j] + dpArr[i - 1][j - 1];
            int b = INT64_MAX;
            if (j < triangle[i - 1].size()) {
                b = triangle[i][j] + dpArr[i - 1][j];
            }
            dpArr[i][j] = min(a, b);
        }
    }
    int res = INT64_MAX;
    for (int i = 0; i < dpArr.back().size(); i++) {
        res = min(res, dpArr.back()[i]);
    }
    return res;
}

int DynamicProgramming::robotDP() {
    int n = 0, C = 0;    // n 表示动作数，C 表示电量
    cin >> n >> C;
    vector<float> ci;    // 每个动作的电量
    vector<int> wi;        // 每个动作的愉悦度
    for (int i = 0; i < n; i++) {
        float tmp_ci = 0;
        int tmp_wi = 0;
        cin >> tmp_ci >> tmp_wi;
        ci.push_back(tmp_ci);
        wi.push_back(tmp_wi);
    }    //// 题目隐含了浮点型数据
    vector<vector<int>> dpArr(ci.size() + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= C; j++) {
            int no_choose = dpArr[i - 1][j];
            int choose = 0;
            if (j >= ci[i - 1]) {
                int left_elec = j - ci[i - 1];
                choose = (wi[i - 1] + dpArr[i - 1][left_elec]);
            }
            dpArr[i][j] = max(choose, no_choose);
        }
    }
    // cout << fixed << setprecision(2) << dpArr.back()[C] << endl;
    return dpArr.back()[C];
}

///// ================================== MathSolution FUNC ==================================

int Math::countPrimes(int n) {
    //厄拉多塞筛法
    if (n == 0 || n == 1 || n == 2) {
        return 0;
    }
    int count = 0;
    vector<int> signs(n, false);
    for (int i = 2; i < n; i++) {
        if (signs[i]) {
            continue;
        } else {
            count++;
            for (long j = i * i; j < n; j += i) {
                signs[(int) j] = true;
            }
        }
    }
    return count;
}

int Math::__gcd(int a, int b) {
    if (a < b) {
        return __gcd(b, a);
    }
    if (b == 0) {
        return a;
    }
    bool is_a_even = !(a % 2 != 0);
    bool is_b_even = !(b % 2 != 0);
    if (is_a_even && is_b_even) {
        return 2 * __gcd(a >> 1, b >> 1);
    } else if (is_a_even && !is_b_even) {
        return __gcd(a >> 1, b);
    } else if (!is_a_even && is_b_even) {
        return __gcd(a, b >> 1);
    } else {
        return __gcd(b, a - b);
    }
}

string Math::convertToBase7(int num) {
    if (num == 0) {
        return "0";
    }
    string sevenNumber;
    if (num < 0) {
        // num = abs(num);
        num = (-num);
        sevenNumber += "-";
    }
    vector<int> divisionNumber;
    while (num) {
        divisionNumber.push_back(num % 7);
        num /= 7;
    }
    reverse(divisionNumber.begin(), divisionNumber.end());
    for (auto __init : divisionNumber) {
        sevenNumber += to_string(__init);
    }
    return sevenNumber;
}

///// ================================== BitOperation FUNC ==================================

int BitOperation::hammingDistance(int x, int y) {
    // 先对 x, y 进行异或，不同位得1，同位得0
    int n = x ^y;
    int counts = 0;
    while (n > 0) {
        if ((n & 1) == 1) {
            counts++;
        }
        n >>= 1;
    }
    return counts;
}

int BitOperation::singleNumber(vector<int> &nums) {
    int res = 0;
    for (int &ii : nums) {
        res ^= ii;
    }
    return res;
}

int BitOperation::missingNumber(vector<int> &nums) {
    int res = nums.size();
    for (int i = 0; i < nums.size(); i++) {
        res = res ^ i ^ nums[i];
    }
    return res;
}

vector<int> BitOperation::singleNumber2(vector<int> &nums) {
    int bitMask = 0;
    for (auto ii : nums) {
        bitMask ^= ii;
    }
    int diff = bitMask & (-bitMask);

    int x = 0;
    for (int num : nums) {
        if ((num & diff) != 0) {
            x ^= num;
        }
    }
    return {x, bitMask ^ x};
}