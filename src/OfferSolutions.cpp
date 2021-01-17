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
#include <algorithm>
#include <deque>

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

int mergeAndCount_func(vector<int> &nums, int left, int mid, int right, vector<int> &helper) {
    for (int i = left; i <= right; i++) {
        helper[i] = nums[i];
    }
    int i = left, j = mid + 1;
    int count = 0;
    for (int k = left; k <= right; k++) {
        if (i == mid + 1) {
            nums[k] = helper[j];
            ++j;
        } else if (j == right + 1) {
            nums[k] = helper[i];
            ++i;
        } else if (helper[i] <= helper[j]) {
            nums[k] = helper[i];
            ++i;
        } else {
            nums[k] = helper[j];
            count += mid - i + 1;
            ++j;
        }
    }
    return count;
}

int reversePairs_func(vector<int> &nums, int left, int right, vector<int> &helper) {
    if (left == right) return 0;
    int mid = left + (right - left) / 2;
    int left_pairs = reversePairs_func(nums, left, mid, helper);
    int right_pairs = reversePairs_func(nums, mid + 1, right, helper);
    if (nums[mid] <= nums[mid + 1]) return left_pairs + right_pairs;
    int cross_pairs = mergeAndCount_func(nums, left, mid, right, helper);
    return left_pairs + cross_pairs + right_pairs;
}

int treeHeight_func(TreeNode *root) {
    if (root == nullptr) return 0;
    if (root->left == nullptr && root->right == nullptr) return 1;
    return max(treeHeight_func(root->left), treeHeight_func(root->right)) + 1;
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

int OfferSolutions::maxSubArray(vector<int> &nums) {
    int res = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i - 1] > 0) {
            nums[i] += nums[i - 1];
        }
        res = max(res, nums[i]);
    }
    return res;
}

int OfferSolutions::countDigitOne(int n) {
    if (n == 0) return 0;
    vector<int> number;
    while (n) number.push_back(n % 10), n /= 10;
    int res = 0;
    for (int i = number.size() - 1; i >= 0; i--) {
        auto left = 0, right = 0, t = 1;
        for (int j = number.size() - 1; j > i; j--) left = left * 10 + number[j];
        for (int j = i - 1; j >= 0; j--) right = right * 10 + number[j], t *= 10;
        res += left * t;
        if (number[i] == 1) res += right + 1;
        else if (number[i] > 1) res += t;
    }
    return res;
}

int OfferSolutions::findNthDigit(int n) {
    // 计算该数字由几位数字组成
    long base = 9, digits = 1;
    while (n - base * digits > 0) {
        n -= base * digits;
        base *= 10;
        digits++;
    }
    // 计算真实代表的数字是多少
    int idx = n % digits;
    if (idx == 0) idx = digits;
    long number = 1;
    for (int i = 1; i < digits; i++) {
        number *= 10;
    }
    number += (idx == digits) ? n / digits - 1 : n / digits;

    // 从真实的数字中找到我们想要的那个数字
    for (int i = idx; i < digits; i++) number /= 10;
    return number % 10;
}

string OfferSolutions::minNumber(vector<int> &nums) {
    if (nums.size() == 1) return to_string(nums[0]);
    vector<string> store;
    string res;
    for (int i:nums) store.push_back(to_string(i));
    sort(store.begin(), store.end(), [](string s1, string s2) { return s1 + s2 < s2 + s1; });
    for (string s:store) res += s;
    return res;
}

int OfferSolutions::translateNum(int num) {
    string s = to_string(num);
    int n = s.length();
    vector<int> dpArr(n + 1, 0);
    dpArr[0] = 1;
    for (int i = 1; i <= n; i++) {
        dpArr[i] = dpArr[i - 1];
        int t = (s[i - 2] - '0') * 10 + s[i - 1] - '0';
        if (t > 9 && t < 26) dpArr[i] += dpArr[i - 2];
    }
    return dpArr[n];
}

int OfferSolutions::maxValue(vector<vector<int>> &grid) {
    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> dpArr(m + 1, vector<int>(n + 1));
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            dpArr[i][j] = max(dpArr[i - 1][j], dpArr[i][j - 1]) + grid[i - 1][j - 1];
    return dpArr[m][n];
}

int OfferSolutions::lengthOfLongestSubstring(string s) {
    int pre = 0;
    int res = 0;
    vector<int> pos(128, -1);
    for (int i = 0; i < s.length(); i++) {
        if (pos[s[i]] >= pre) pre = pos[s[i]] + 1;
        pos[s[i]] = i;  // 记录最后出现的位置
        res = max(res, i - pre + 1);
    }
    return res;
}

int OfferSolutions::nthUglyNumber(int n) {
    int two = 0, three = 0, five = 0;
    vector<int> dpArr(n);
    dpArr[0] = 1;
    for (int i = 1; i < n; i++) {
        int t1 = dpArr[two] * 2, t2 = dpArr[three] * 3, t3 = dpArr[five] * 5;
        dpArr[i] = min(min(t1, t2), t3);
        if (dpArr[i] == t1) two++;
        if (dpArr[i] == t2) three++;
        if (dpArr[i] == t3) five++;
    }
    return dpArr.back();
}

char OfferSolutions::firstUniqChar(string s) {
    vector<int> hash_vec(128, 0);
    for (int i = 0; i < s.length(); i++) {
        hash_vec[s[i]]++;
    }
    for (int i = 0; i < s.length(); i++) {
        if (hash_vec[s[i]] == 1) return s[i];
    }
    return ' ';
}

int OfferSolutions::reversePairs(vector<int> &nums) {
    int len = nums.size();
    if (len < 2) return 0;
    vector<int> helper(len);
    return reversePairs_func(nums, 0, len - 1, helper);
}

ListNode *OfferSolutions::getIntersectionNode(ListNode *headA, ListNode *headB) {
    ListNode *pHead_A = headA, *pHead_B = headB;
    while (pHead_A != pHead_B) {
        pHead_A = pHead_A == nullptr ? headB : pHead_A->next;
        pHead_B = pHead_B == nullptr ? headA : pHead_B->next;
    }
    return pHead_A;
}

int OfferSolutions::search(vector<int> &nums, int target) {
    int res = 0;
    for (int i:nums) {
        if (i == target) res++;
    }
    return res;
}

int OfferSolutions::missingNumber(vector<int> &nums) {
    int flag = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] == flag) flag++;
        else return flag;
    }
    return nums.back() + 1;
}

int OfferSolutions::kthLargest(TreeNode *root, int k) {
    priority_queue<int> qVal;
    queue<TreeNode *> qNodes;
    qNodes.push(root);
    while (!qNodes.empty()) {
        int curr_size = qNodes.size();
        for (int i = 0; i < curr_size; i++) {
            TreeNode *curr_node = qNodes.front();
            qNodes.pop();
            qVal.push(curr_node->val);
            if (curr_node->left != nullptr) qNodes.push(curr_node->left);
            if (curr_node->right != nullptr) qNodes.push(curr_node->right);
        }
    }
    for (int i = 1; i < k; i++) qVal.pop();
    return qVal.top();
}

int OfferSolutions::maxDepth(TreeNode *root) {
    if (root == nullptr) return 0;
    int left_depth = maxDepth(root->left);
    int right_depth = maxDepth(root->right);
    return max(left_depth, right_depth) + 1;
}

bool OfferSolutions::isBalanced(TreeNode *root) {
    if (root == nullptr) return true;
    int left_height = treeHeight_func(root->left);
    int right_height = treeHeight_func(root->right);
    // 保证每一个孩子节点都是平衡二叉树
    return isBalanced(root->left) && isBalanced(root->right) && abs(left_height - right_height) < 2;
}

vector<int> OfferSolutions::singleNumbers(vector<int> &nums) {
    int res = 0;
    for (int i:nums) res ^= i;
    int div = 1;
    while ((div & res) == 0) div <<= 1;
    int a = 0, b = 0;
    for (int i:nums) {
        if (div & i) a ^= i;
        else b ^= i;
    }
    return {a, b};
}

int OfferSolutions::singleNumber(vector<int> &nums) {
    vector<int> binary(32, 0);
    //将 nums 的所有元素转为二进制并加起来
    for (int i:nums) {
        for (int j = 31; j >= 0; j--) {
            binary[j] += i & 1;
            i >>= 1;
        }
    }
    int res = 0;
    //哪一位不能被3整除，就说明目标数字的二进制在那一位是 1
    for (int i = 31; i >= 0; i--) {
        if (binary[i] % 3) res += pow(2, 31 - i);
    }
    return res;
}

vector<int> OfferSolutions::twoSum(vector<int> &nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left < right) {
        if (nums[left] + nums[right] == target) return {nums[left], nums[right]};
        else if (nums[left] + nums[right] < target) left++;
        else right--;
    }
    return {};
}

vector<vector<int>> OfferSolutions::findContinuousSequence(int target) {
    vector<vector<int>> res;
    for (int i = 1; i < target; i++) {
        int curr_sum = i, num = i;
        vector<int> tmp_nums;
        tmp_nums.push_back(i);
        while (curr_sum < target) {
            num++;
            curr_sum += num;
            tmp_nums.push_back(num);
        }
        if (curr_sum == target) {
            res.push_back(tmp_nums);
        }
    }
    return res;
}

string OfferSolutions::reverseWords(string s) {
    vector<string> all_words;
    string tmp_str;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != ' ') tmp_str += s[i];
        else {
            if (tmp_str != "") {
                all_words.push_back(tmp_str);
                tmp_str = "";
            } else continue;
        }
    }
    if (tmp_str != "") all_words.push_back(tmp_str);
    reverse(all_words.begin(), all_words.end());
    string res;
    for (int i = 0; i < all_words.size(); i++) {
        if (i != all_words.size() - 1) res += all_words[i], res += " ";
        else res += all_words[i];
    }
    return res;
}

string OfferSolutions::reverseLeftWords(string s, int n) {
    n %= s.length();
    string tmp_str = s.substr(0, n);
    s = s.substr(n);
    s += tmp_str;
    return s;
}

vector<int> OfferSolutions::maxSlidingWindow(vector<int> &nums, int k) {
    if (nums.empty() || k > nums.size() || k <= 0) return {};

    vector<int> res;
    deque<int> find_max;

    for (int i = 0; i < nums.size(); i++) {
        if (i >= k && !find_max.empty())
            res.push_back(nums[find_max.front()]);
        while (!find_max.empty() && nums[i] >= nums[find_max.back()])
            find_max.pop_back();
        if (!find_max.empty() && i - find_max.front() >= k)
            find_max.pop_front();
        find_max.push_back(i);
    }
    res.push_back(nums[find_max.front()]);
    return res;
}

vector<double> OfferSolutions::dicesProbability(int n) {
    vector<int> dpArr(70);
    for (int i = 1; i <= 6; i++) {
        dpArr[i] = 1;
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 6 * i; j >= i; j--) {
            dpArr[j] = 0;
            for (int cur = 1; cur <= 6; cur++) {
                if (j - cur < i - 1) {
                    break;
                }
                dpArr[j] += dpArr[j - cur];
            }
        }
    }
    int all = pow(6, n);
    vector<double> ret;
    for (int i = n; i <= 6 * n; i++) {
        ret.push_back(dpArr[i] * 1.0 / all);
    }
    return ret;
}

bool OfferSolutions::isStraight(vector<int> &nums) {
    sort(nums.begin(), nums.end());
    int zero_counts = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] == 0) {
            zero_counts++;
            continue;
        }
        int j = i + 1;
        if (j < nums.size()) {
            if (nums[i] == nums[j]) return false;
            int tmp = nums[j] - nums[i];
            while (tmp > 1) {
                if (zero_counts == 0) return false;
                zero_counts--;
                tmp--;
            }
        }
    }
    return true;
}

int OfferSolutions::lastRemaining(int n, int m) {
    int f = 0;
    for (int i = 2; i != n + 1; ++i) {
        f = (m + f) % i;
    }
    return f;
}

int OfferSolutions::maxProfit(vector<int> &prices) {
    if (prices.size() < 2) return 0;
    int min_price = 1e9, max_profit = 0;
    for (int price:prices) {
        max_profit = max(max_profit, price - min_price);
        min_price = min(price, min_price);
    }
    return max_profit;
}

int OfferSolutions::sumNums(int n) {
    // 如果 a 为 false，那计算机会直接返回 a && b = false，而不会再去运行 b 语句了
    n && (n += sumNums(n - 1));
    return n;
}

int OfferSolutions::add(int a, int b) {
    if (a == 0 || b == 0) return a == 0 ? b : a;
    int sum = 0, carry = 0;
    while (b != 0) {
        sum = a ^ b;
        carry = (unsigned int) (a & b) << 1;    // C++ 不允许负数进行左移操作，故要加 unsigned int

        a = sum;
        b = carry;
    }
    return a;
}

vector<int> OfferSolutions::constructArr(vector<int> &a) {
    int len = a.size();
    if (len < 2) return len < 1 ? vector<int>() : vector<int>(1, -10086);
    vector<int> res(len, 1);
    vector<int> left(len, 1), right(len, 1);
    left[0] = 1;
    left[1] = a[0];

    for (int i = 2; i < len; ++i) {
        left[i] = left[i - 1] * a[i - 1]; // 从前往后填充 left 数组
    }

    right[len - 1] = 1; // 初始化
    right[len - 2] = a[len - 1]; // 初始化

    res[len - 1] = left[len - 1] * right[len - 1]; // 填充 b[len - 1]
    res[len - 2] = left[len - 2] * right[len - 2]; // 填充 b[len - 2]

    for (int i = len - 3; i >= 0; --i) {
        right[i] = right[i + 1] * a[i + 1]; // 从后往前填充 right 数组
        res[i] = left[i] * right[i]; // 填充 b[len - 3] 至 b[0]
    }

    return res;
}

int OfferSolutions::strToInt(string str) {
    int i = 0, flag = 1;
    long res = 0; //默认flag = 1，正数
    while (str[i] == ' ') i++;
    if (str[i] == '-') flag = -1;
    if (str[i] == '-' || str[i] == '+') i++;
    for (; i < str.size() && isdigit(str[i]); i++) {
        res = res * 10 + (str[i] - '0');
        if (res >= INT32_MAX && flag == 1) return INT32_MAX;
        if (res > INT32_MAX && flag == -1) return INT32_MIN;
    }
    return flag * res;
}

TreeNode *OfferSolutions::lowestCommonAncestor_search_tree(TreeNode *root, TreeNode *p, TreeNode *q) {
    if (root == nullptr) return nullptr;
    while (root) {
        if (p->val > root->val && q->val > root->val) root = root->right;
        else if (p->val < root->val && q->val < root->val) root = root->left;
        else return root;
    }
    return root;
}

TreeNode *OfferSolutions::lowestCommonAncestor_tree(TreeNode *root, TreeNode *p, TreeNode *q) {
    if (root == nullptr || root == p || root == q) return root;
    TreeNode *left_node = lowestCommonAncestor_tree(root->left, p, q);
    TreeNode *right_node = lowestCommonAncestor_tree(root->right, p, q);
    if (left_node == nullptr) return right_node;
    if (right_node == nullptr) return left_node;
    return root;
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

// *** 剑指 Offer 41. 数据流中的中位数 ***
// 使用两个根堆将数据分成大的那部分和小的那部分
// 求中位数只需要计算两个堆顶元素即可～
class MedianFinder {
public:
    priority_queue<int> max_heap;
    priority_queue<int, vector<int>, greater<int>> min_heap;

    MedianFinder() = default;

    void addNum(int num) {
        max_heap.push(num); // 无条件先放入大根堆
        if (min_heap.size() && max_heap.top() > min_heap.top()) {
            auto maxV = max_heap.top(), minV = min_heap.top();
            max_heap.pop(), min_heap.pop();
            max_heap.push(minV), min_heap.push(maxV);
        }
        if (max_heap.size() > min_heap.size() + 1) {
            min_heap.push(max_heap.top());
            max_heap.pop();
        }
    }

    double findMedian() {
        if (max_heap.size() + min_heap.size() & 1)  // 奇数个数
            return max_heap.top();
        else
            return ((max_heap.top() + min_heap.top()) / 2.0);
    }
};

// 剑指 Offer 59 - II. 队列的最大值
class MaxQueue {
private:
    deque<int> max_num;
    queue<int> all_nums;
public:
    MaxQueue() = default;

    int max_value() {
        return max_num.empty() ? -1 : max_num.front();
    }

    void push_back(int value) {
        all_nums.push(value);
        while (!max_num.empty() && value >= max_num.back()) max_num.pop_back();
        max_num.push_back(value);
    }

    int pop_front() {
        if (all_nums.empty()) return -1;
        int res = all_nums.front();
        all_nums.pop();
        if (res == max_num.front()) max_num.pop_front();
        return res;
    }
};
