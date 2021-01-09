//
// Created by LaiChao on 2020/11/5.
// 最优解答方案
//

#include "OfferSolutions.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <stack>
#include <queue>
#include <cmath>
#include <unordered_map>

using namespace std;

/// ================================== GLOBAL VAR ==================================
int gIndex = 0;    // 剑指 Offer 07 - buildTree
int gRows = 0, gCols = 0;   // 剑指 Offer 12 - exist
vector<vector<int>> gPathSumRes;    // 剑指 Offer 34 - pathSum
vector<int> gTempPathSum;           // 剑指 Offer 34 - pathSum
searchNode *gHead, *gTail;          // 剑指 Offer 36 - treeToDoublyList
vector<string> gPermutationRes;     // 剑指 Offer 38 - permutation

///// ================================== HELP FUNC ==================================
TreeNode *rebuild_func(vector<int> &preOrder, vector<int> &inOrder, int left, int right) {
    if (gIndex == preOrder.size() || left == right) {
        return nullptr;
    }
    TreeNode *head = nullptr;
    for (int i = left; i < right; i++) {
        if (preOrder[gIndex] == inOrder[i]) {  // 找到分界条件
            head = new TreeNode(preOrder[gIndex]);
            gIndex++;   // 前序遍历的index往后移
            head->left = rebuild_func(preOrder, inOrder, left, i);      // 切分左子树（左闭右开）
            head->right = rebuild_func(preOrder, inOrder, i + 1, right);    // 切分右子树
            break;
        }
    }
    return head;
}

bool dfs_exist_func(vector<vector<char>> &board, string &word, int i, int j, int k) {
    if (i < 0 || i > gRows - 1 || j < 0 || j > gCols - 1 || board[i][j] != word[k]) {
        return false;
    }
    if (k == word.size() - 1) {
        return true;
    }
    board[i][j] = '\0';
    bool res = dfs_exist_func(board, word, i + 1, j, k + 1) || dfs_exist_func(board, word, i - 1, j, k + 1) ||
               dfs_exist_func(board, word, i, j + 1, k + 1) || dfs_exist_func(board, word, i, j - 1, k + 1);
    board[i][j] = word[k];  // 回退
    return res;
}

int dfs_movingCount_func(int i, int j, int si, int sj, vector<vector<bool>> &isVisited, int m, int n, int k) {
    if (i > m - 1 || j > n - 1 || si + sj > k || isVisited[i][j]) {
        return 0;
    }
    isVisited[i][j] = true;
    return 1 + dfs_movingCount_func(i + 1, j, ((i + 1) % 10) == 0 ? si - 8 : si + 1, sj, isVisited, m, n, k) +
           dfs_movingCount_func(i, j + 1, si, ((j + 1) % 10) == 0 ? sj - 8 : sj + 1, isVisited, m, n, k);
}

int split_number(int n) {
    int res = 0;
    while (n) {
        res += (n % 10);
        n /= 10;
    }
    return res;
}

bool isPart_func(TreeNode *t1, TreeNode *t2) {
    if (t2 == nullptr) return true;
    if (t1 == nullptr || t1->val != t2->val) return false;
    return isPart_func(t1->left, t2->left) && isPart_func(t1->right, t2->right);
}

bool isSymmetric_func(TreeNode *left, TreeNode *right) {
    if (left == nullptr && right == nullptr) return true;
    if (left == nullptr || right == nullptr) return false;
    return (left->val == right->val) && isSymmetric_func(left->left, right->right) &&
           isSymmetric_func(left->right, right->left);
}

bool verifyPostorder_func(vector<int> &postOrder, int i, int j) {
    if (i >= j) return true;
    int p = i;
    while (postOrder[p] < postOrder[j]) p++;
    int m = p;
    while (postOrder[p] > postOrder[j]) p++;
    return p == j && verifyPostorder_func(postOrder, i, m - 1) && verifyPostorder_func(postOrder, m, j - 1);
}

void pathSum_func(TreeNode *root, int sum) {
    if (root == nullptr) return;
    gTempPathSum.push_back(root->val);
    sum -= root->val;
    if (sum == 0 && root->left == nullptr && root->right == nullptr) {
        gPathSumRes.push_back(gTempPathSum);
    }
    pathSum_func(root->left, sum);
    pathSum_func(root->right, sum);
    gTempPathSum.pop_back();
}

void treeToDoublyList_func(searchNode *root) {
    // 中序遍历的方法
    if (root == nullptr) return;
    treeToDoublyList_func(root->left);
    if (!gTail) gHead = root;   // 当tail还不存在，也就是root此时在整个BST的最左边的节点，这个节点就是head
    else gTail->right = root, root->left = gTail;   // 前一个节点的right是当前节点, 当前节点的left是前一个节点
    gTail = root;  // 将前一个节点更新为当前节点（所以到最后，tail就会挪到整个BST的最右边的节点，这个节点就是链表的尾节点）
    treeToDoublyList_func(root->right);
}

void permutation_func(string s, string &path, vector<bool> &used) {
    if (path.size() == s.size()) {
        gPermutationRes.push_back(path);
        return;
    }
    for (int i = 0; i < s.length(); i++) {
        if (!used[i]) {
            if (i > 0 && s[i - 1] == s[i] && !used[i - 1]) {
                continue;
            }
            path.push_back(s[i]);
            used[i] = true;
            permutation_func(s, path, used);
            used[i] = false;
            path.pop_back();
        }
    }
}

///// ================================== CLASS FUNC ==================================
int OfferSolutions::findRepeatNumber(vector<int> &nums) {
    if (nums.empty()) {
        return -1;
    }
    // 每次把一个正确的数放在正确的位置上，如果在放的时候发现已经重复了，则返回
    int len = nums.size();
    for (int i = 0; i < len; i++) {
        while (nums[i] != i) {
            if (nums[i] == nums[nums[i]]) {
                return nums[i];
            }
            swap(nums[i], nums[nums[i]]);
        }
    }
    return -1;
}

bool OfferSolutions::findNumberIn2DArray(vector<vector<int>> &matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) {
        return false;
    }
    if (target < matrix[0][0] || target > matrix[matrix.size() - 1][matrix[0].size()] - 1) {
        return false;
    }
    int r = 0, c = matrix[0].size() - 1;
    while (r < matrix.size() && c >= 0) {
        if (matrix[r][c] == target) {
            return true;
        } else if (matrix[r][c] > target) {
            c--;
        } else {
            r++;
        }
    }
    return false;
}

string OfferSolutions::replaceSpace(string s) {
    if (s.empty()) {
        return nullptr;
    }
    string res;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != ' ') {
            res += s[i];
        } else {
            res += "%20";
        }
    }
    return res;
}

vector<int> OfferSolutions::reversePrint(ListNode *head) {
    // 使用stack后比使用reverse算法，速度更快一些
    vector<int> res;
    if (head == nullptr) {
        return res;
    }
    ListNode *tmpNode = head;
    stack<int> sNumbers;
    while (tmpNode != nullptr) {
        sNumbers.push(tmpNode->val);
        tmpNode = tmpNode->next;
    }
    while (!sNumbers.empty()) {
        res.push_back(sNumbers.top());
        sNumbers.pop();
    }
//    reverse(res.begin(), res.end());
    return res;
}

TreeNode *OfferSolutions::buildTree(vector<int> &preorder, vector<int> &inorder) {
    TreeNode *head;
    int left = 0;
    int right = inorder.size();   // 起始条件
    return rebuild_func(preorder, inorder, left, right);
}

int OfferSolutions::fib(int n) {
    if (n < 2) {
        return n;
    }
    unsigned long long x = 0, y = 1, m = 1;
    while (m++ < n) {
        unsigned long long t = y;
        y = (x + y) % 1000000007L;
        x = t;
    }
    return y % 1000000007;
}

int OfferSolutions::numWays(int n) {
    if (n == 0) {
        return 1;
    }
    if (n < 3) {
        return n;
    }
    vector<int> dpArr(n + 1, 0);
    dpArr[1] = 1;
    dpArr[2] = 2;
    for (int i = 3; i <= n; i++) {
        dpArr[i] = (dpArr[i - 1] + dpArr[i - 2]) % 1000000007;
    }
    return dpArr[n];
}

int OfferSolutions::minArray(vector<int> &numbers) {
    int left = 0, right = numbers.size() - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (numbers[mid] > numbers[right]) {
            left = mid + 1; // 如果中间值大于最右边的值，说明旋转之后最小的数字肯定在mid的右边，
        } else if (numbers[mid] < numbers[right]) {
            right = mid;
        } else {
            right--;
        }
    }
    return numbers[left];
}

bool OfferSolutions::exist(vector<vector<char>> &board, string word) {
    gRows = board.size();
    gCols = board[0].size();
    for (int i = 0; i < gRows; i++) {
        for (int j = 0; j < gCols; j++) {
            if (dfs_exist_func(board, word, i, j, 0)) {
                return true;
            }
        }
    }
    return false;
}

int OfferSolutions::movingCount(int m, int n, int k) {
    vector<vector<bool>> isVisited(m, vector<bool>(n, false));
    return dfs_movingCount_func(0, 0, 0, 0, isVisited, m, n, k);
}

int OfferSolutions::movingCount_bfs(int m, int n, int k) {
    if (!k) {
        return 1;
    }
    queue<pair<int, int>> q;
    // 向右和向下
    int dx[2] = {1, 0};
    int dy[2] = {0, 1};
    vector<vector<int>> isVisited(m, vector<int>(n, 0));
    q.push(make_pair(0, 0));
    isVisited[0][0] = 1;
    int res = 1;
    while (!q.empty()) {
        auto[x, y]=q.front();
        q.pop();
        for (int i = 0; i < 2; i++) {
            int tx = x + dx[i];
            int ty = y + dy[i];
            if (tx > m - 1 || ty > n - 1 || isVisited[tx][ty] || split_number(tx) + split_number(ty) > k) {
                continue;
            }
            q.push(make_pair(tx, ty));
            isVisited[tx][ty] = 1;
            res++;
        }
    }
    return res;
}

int OfferSolutions::cuttingRope(int n) {
    if (n <= 3) {
        return 1 * (n - 1);
    }
    int res = 1;
    if (n % 3 == 1) {   // 拆出来一个 4, 因为肯定不会拆出来 1
        res *= 4;
        n -= 4;
    }
    if (n % 3 == 2) {   // 拆出来一个 2
        res *= 2;
        n -= 2;
    }
    while (n) {     // 通过上面两个if保证现在 n 可以整除 3
        res *= 3;
        n -= 3;
    }
    return res;
}

int OfferSolutions::cuttingRope02(int n) {
    if (n <= 3) {
        return 1 * (n - 1);
    }
    long long res = 1;
    if (n % 3 == 1) {
        res *= 4, n -= 4;
    }
    if (n % 3 == 2) {
        res *= 2, n -= 2;
    }
    while (n) {
        res = res * 3 % 1000000007;
        n -= 3;
    }
    return res;
}

int OfferSolutions::hammingWeight(uint32_t n) {
    int res = 0;
    while (n) {
        res += (n & 1);
        n >>= 1;
    }
    return res;
}

double OfferSolutions::myPow(double x, int n) {
    double res = 1.;
    bool flag = n < 0;
    while (n) {
        if (n & 1) {
            res *= x;
        }
        x *= x;
        n /= 2;     // 不能是 n>>=1 因为负数的情况会出现死循环
    }
    return flag ? 1. / res : res;
}

vector<int> OfferSolutions::printNumbers(int n) {
    vector<int> res;
    int max_num = pow(10, n);
    for (int i = 1; i < max_num; i++) {
        res.push_back(i);
    }
    return res;
}

ListNode *OfferSolutions::deleteNode(ListNode *head, int val) {
    if (head == nullptr) {
        return nullptr;
    }
    if (head->val == val) {
        ListNode *node = head->next;
        return node;
    }
    ListNode *fast = head->next, *slow = head;
    while (fast != nullptr && slow != nullptr) {
        if (fast->val == val) {
            break;
        }
        fast = fast->next;
        slow = slow->next;
    }
    slow->next = fast->next;
    fast->next = nullptr;
    return head;
}

bool OfferSolutions::isMatch(string s, string p) {
/// =============================================================================
///       ～～～～～～～ 不 会 做 ～～～～～～～～ 我 抄 的 ～～～～～～～～
/// =============================================================================
    int m = s.size();
    int n = p.size();

    auto matches = [&](int i, int j) -> bool {
        if (i == 0) {
            return false;
        }
        if (p[j - 1] == '.') {
            return true;
        }
        return s[i - 1] == p[j - 1];
    };

    vector<vector<int>> dpArr(m + 1, vector<int>(n + 1, 0));
    dpArr[0][0] = true;
    for (int i = 0; i < m + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            if (p[j - 1] == '*') {
                dpArr[i][j] |= dpArr[i][j - 2];
                if (matches(i, j - 1)) {
                    dpArr[i][j] |= dpArr[i - 1][j];
                }
            } else {
                if (matches(i, j)) {
                    dpArr[i][j] |= dpArr[i - 1][j - 1];
                }
            }
        }
    }
    return dpArr[m][n];
/// =============================================================================
}

bool OfferSolutions::isNumber(string s) {
    int n = s.size();
    int index = -1;
    bool hasDot = false, hasE = false, hasOp = false, hasNum = false;
    while (index < n && s[++index] == ' ');
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

vector<int> OfferSolutions::exchange(vector<int> &nums) {
    if (nums.size() < 2) {
        return nums;
    }
    int odd = 0, tmp = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] % 2) {
            if (i != odd) {
                tmp = nums[i];
                nums[i] = nums[odd];
                nums[odd] = tmp;
            }
            odd++;
        }
    }
    return nums;
}

ListNode *OfferSolutions::getKthFromEnd(ListNode *head, int k) {
    ListNode *fast = head, *slow = head;
    while (k) {
        fast = fast->next;
        k--;
    }
    while (fast != nullptr) {
        fast = fast->next;
        slow = slow->next;
    }
    return slow;
}

ListNode *OfferSolutions::reverseList(ListNode *head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    ListNode *curr = nullptr, *pre = head;
    while (pre != nullptr) {
        ListNode *tmp = pre->next;
        pre->next = curr;
        curr = pre;
        pre = tmp;
    }
    return curr;
}

ListNode *OfferSolutions::mergeTwoLists(ListNode *l1, ListNode *l2) {
    if (l1 == nullptr) return l2;
    if (l2 == nullptr) return l1;
    ListNode *tmp = new ListNode(0);
    ListNode *head = tmp;
    while (l1 != nullptr && l2 != nullptr) {
        if (l1->val < l2->val) {
            tmp->next = l1;
            l1 = l1->next;
        } else {
            tmp->next = l2;
            l2 = l2->next;
        }
        tmp = tmp->next;
    }
    if (l1 == nullptr) tmp->next = l2;
    if (l2 == nullptr) tmp->next = l1;
    return head->next;
}

bool OfferSolutions::isSubStructure(TreeNode *A, TreeNode *B) {
    if (A == nullptr || B == nullptr) return false;
    if (isPart_func(A, B)) return true;
    return isSubStructure(A->left, B) || isSubStructure(A->right, B);
}

TreeNode *OfferSolutions::mirrorTree(TreeNode *root) {
    if (root == nullptr) return root;
    TreeNode *left, *right;
    left = mirrorTree(root->left);
    right = mirrorTree(root->right);
    root->left = right, root->right = left;
    return root;
}

TreeNode *OfferSolutions::mirrorTree02(TreeNode *root) {
    if (root == nullptr) return root;
    stack<TreeNode *> sNodes;
    sNodes.push(root);
    while (!sNodes.empty()) {
        TreeNode *tmpNode = sNodes.top();
        sNodes.pop();
        swap(tmpNode->left, tmpNode->right);
        if (tmpNode->left != nullptr) sNodes.push(tmpNode->left);
        if (tmpNode->right != nullptr) sNodes.push(tmpNode->right);
    }
    return root;
}

bool OfferSolutions::isSymmetric(TreeNode *root) {
    if (root == nullptr) return true;
    return isSymmetric_func(root->left, root->right);
}

vector<int> OfferSolutions::spiralOrder(vector<vector<int>> &matrix) {
    vector<int> res;
    int m = matrix.size();
    if (!m) return res;
    int n = matrix[0].size();
    int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
    int x = 0, y = 0, d = 0;
    vector<vector<bool>> isVisited(m, vector<bool>(n, false));
    for (int i = 0; i < m * n; i++) {
        res.push_back(matrix[x][y]);
        isVisited[x][y] = true;
        int a = x + dx[d], b = y + dy[d];
        if (a < 0 || a > m - 1 || b < 0 || b > n - 1 || isVisited[a][b]) {
            d = (d + 1) % 4;
            a = x + dx[d], b = y + dy[d];
        }
        x = a, y = b;
    }
    return res;
}

bool OfferSolutions::validateStackSequences(vector<int> &pushed, vector<int> &popped) {
    stack<int> sta;
    int k = 0;
    for (int i:pushed) {
        sta.push(i);
        while (!sta.empty() && sta.top() == popped[k]) {
            sta.pop();
            k++;
        }
    }
    return sta.empty();
}

vector<int> OfferSolutions::levelOrder(TreeNode *root) {
    if (root == nullptr) return {};
    vector<int> res;
    queue<TreeNode *> qNodes;
    qNodes.push(root);
    while (!qNodes.empty()) {
        int curr_size = qNodes.size();
        for (int i = 0; i < curr_size; i++) {
            TreeNode *tmpNode = qNodes.front();
            qNodes.pop();
            res.push_back(tmpNode->val);
            if (tmpNode->left != nullptr) qNodes.push(tmpNode->left);
            if (tmpNode->right != nullptr) qNodes.push(tmpNode->right);
        }
    }
    return res;
}

vector<vector<int>> OfferSolutions::levelOrder02(TreeNode *root) {
    if (root == nullptr) return {};
    vector<vector<int>> res;
    queue<TreeNode *> qNodes;
    qNodes.push(root);
    while (!qNodes.empty()) {
        int curr_size = qNodes.size();
        vector<int> tmp_vec;
        for (int i = 0; i < curr_size; i++) {
            TreeNode *tmp_node = qNodes.front();
            qNodes.pop();
            tmp_vec.push_back(tmp_node->val);
            if (tmp_node->left != nullptr) qNodes.push(tmp_node->left);
            if (tmp_node->right != nullptr) qNodes.push(tmp_node->right);
        }
        res.push_back(tmp_vec);
    }
    return res;
}

vector<vector<int>> OfferSolutions::levelOrder03(TreeNode *root) {
    if (root == nullptr) return {};
    vector<vector<int>> res;
    queue<TreeNode *> qNodes;
    qNodes.push(root);
    bool flag = false;
    while (!qNodes.empty()) {
        int curr_size = qNodes.size();
        vector<int> tmp_vec;
        for (int i = 0; i < curr_size; i++) {
            TreeNode *tmp_node = qNodes.front();
            qNodes.pop();
            tmp_vec.push_back(tmp_node->val);
            if (tmp_node->left != nullptr) qNodes.push(tmp_node->left);
            if (tmp_node->right != nullptr) qNodes.push(tmp_node->right);
        }
        if (flag) {
            reverse(tmp_vec.begin(), tmp_vec.end());
        }
        flag = !flag;
        res.push_back(tmp_vec);
    }
    return res;
}

bool OfferSolutions::verifyPostorder(vector<int> &postorder) {
    // 分治算法
    return verifyPostorder_func(postorder, 0, postorder.size() - 1);
}

vector<vector<int>> OfferSolutions::pathSum(TreeNode *root, int sum) {
    // 经典的 DFS 问题
    pathSum_func(root, sum);
    return gPathSumRes;
}

RandomNode *OfferSolutions::copyRandomList(RandomNode *head) {
    if (head == nullptr) return head;
    RandomNode *curr = head;
    unordered_map<RandomNode *, RandomNode *> mapNode;
    while (curr != nullptr) {
        mapNode[curr] = new RandomNode(curr->val);
        curr = curr->next;
    }
    curr = head;
    while (curr != nullptr) {
        mapNode[curr]->next = mapNode[curr->next];
        mapNode[curr]->random = mapNode[curr->random];
        curr = curr->next;
    }
    return mapNode[head];
}

searchNode *OfferSolutions::treeToDoublyList(searchNode *root) {
    if (root == nullptr) return root;
    treeToDoublyList_func(root);
    gHead->left = gTail;
    gTail->right = gHead;
    return gHead;
}

vector<string> OfferSolutions::permutation(string s) {
    if (s.empty()) {
        return {};
    }
    string tmp = "";
    sort(s.begin(), s.end());
    vector<bool> used(s.length());
    permutation_func(s, tmp, used);
    return gPermutationRes;
}

int OfferSolutions::majorityElement(vector<int> &nums) {
    int val = -1, cnt = 0;
    for (int i:nums) {
        if (!cnt)
            val = i, cnt = 1;
        else {
            if (i == val) cnt++;
            else cnt--;
        }
    }
    return val;
}

vector<int> OfferSolutions::getLeastNumbers(vector<int> &arr, int k) {
    if (k == 0) return {};
    if (k == arr.size())
        return arr;
    vector<int> res;
    priority_queue<int> q;
    for (int i = 0; i < k; i++)
        q.push(arr[i]);
    for (int i = k; i < arr.size(); i++) {
        if (arr[i] < q.top()) {
            q.pop();
            q.push(arr[i]);
        }
    }
    for (int i = 0; i < k; i++) {
        res.push_back(q.top());
        q.pop();
    }
    return res;
}

/// ================================== SPECIAL CASE ==================================
// 剑指 Offer 09. 用两个栈实现队列
class CQueue {
public:
    CQueue() {
        while (!sta01.empty()) {
            sta01.pop();
        }
        while (!sta02.empty()) {
            sta02.pop();
        }
    }

    void appendTail(int value) {
        sta01.push(value);
    }

    int deleteHead() {
        if (sta02.empty()) {
            while (!sta01.empty()) {
                sta02.push(sta01.top());
                sta01.pop();
            }
        }
        if (sta02.empty()) {
            return -1;
        } else {
            int delNumber = sta02.top();
            sta02.pop();
            return delNumber;
        }
    }

private:
    stack<int> sta01;
    stack<int> sta02;
};

// 剑指 Offer 30. 包含min函数的栈
class MinStack {
public:
    MinStack() {
        while (!s.empty()) s.pop();
        while (!m.empty()) m.pop();
    }

    void push(int x) {
        s.push(x);
        if (m.empty() || x <= m.top()) m.push(x);
    }

    void pop() {
        if (s.top() == m.top()) m.pop();
        s.pop();
    }

    int top() {
        return s.top();
    }

    int min() {
        return m.top();
    }

private:
    stack<int> s, m;
};

// 剑指 Offer 37. 序列化二叉树
class SerializeTreeNode {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode *root) {
        if (root == nullptr)
            return "";
        ostringstream out;
        serialize(root, out);
        return out.str();
    }

    // Decodes your encoded data to tree.
    TreeNode *deserialize(string data) {
        if (data.empty())
            return nullptr;
        istringstream in(data);
        return deserialize(in);
    }

private:
    void serialize(TreeNode *root, ostringstream &out) {
        if (root == nullptr) {
            out << "# ";
            return;
        }
        out << to_string(root->val) << " ";
        serialize(root->left, out);
        serialize(root->right, out);
    }

    TreeNode *deserialize(istringstream &in) {
        string val;
        in >> val;
        if (val == "#")
            return nullptr;
        auto root = new TreeNode(atoi(val.c_str()));
        root->left = deserialize(in);
        root->right = deserialize(in);
        return root;
    }
};
