//
// Created by LaiChao on 2020/11/5.
//

#ifndef THEROADTOADVANCEMENT_OFFERSOLUTIONS_H
#define THEROADTOADVANCEMENT_OFFERSOLUTIONS_H
/// ============== 剑指Offer题目 ==============

#include "./__OSJudge.h"
#include "./DataStructure/Tree.h"
#include "./DataStructure/List.h"
#include <vector>
#include <string>

using namespace std;


class OfferSolutions {
public:
    static int findRepeatNumber(vector<int> &nums);         // 剑指 Offer 03. 数组中重复的数字
    static bool findNumberIn2DArray(vector<vector<int>> &matrix, int target);       // 剑指 Offer 04. 二维数组中的查找
    static string replaceSpace(string s);           // 剑指 Offer 05. 替换空格
    static vector<int> reversePrint(ListNode *head);        // 剑指 Offer 06. 从尾到头打印链表
    static TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder);        // *** 剑指 Offer 07. 重建二叉树 ***
    static int fib(int n);          // 剑指 Offer 10- I. 斐波那契数列
    static int numWays(int n);      // 剑指 Offer 10- II. 青蛙跳台阶问题
    static int minArray(vector<int> &numbers);      // 剑指 Offer 11. 旋转数组的最小数字
    static bool exist(vector<vector<char>> &board, string word);        // *** 剑指 Offer 12. 矩阵中的路径 ***
    static int movingCount(int m, int n, int k);        // *** 剑指 Offer 13. 机器人的运动范围 ***
    static int movingCount_bfs(int m, int n, int k);    // *** 剑指 Offer 13. 机器人的运动范围(广度优先方法) ***
    static int cuttingRope(int n);      // *** 剑指 Offer 14- I. 剪绳子 ***
    static int cuttingRope02(int n);    // 剑指 Offer 14- II. 剪绳子 II
    static int hammingWeight(uint32_t n);       // 剑指 Offer 15. 二进制中1的个数
    static double myPow(double x, int n);       // 剑指 Offer 16. 数值的整数次方
    static vector<int> printNumbers(int n);     // 剑指 Offer 17. 打印从1到最大的n位数
    static ListNode *deleteNode(ListNode *head, int val);       // 剑指 Offer 18. 删除链表的节点
    static bool isMatch(string s, string p);    // *** 剑指 Offer 19. 正则表达式匹配 ***
    static bool isNumber(string s);     // 剑指 Offer 20. 表示数值的字符串
    static vector<int> exchange(vector<int> &nums);     // 剑指 Offer 21. 调整数组顺序使奇数位于偶数前面
    static ListNode *getKthFromEnd(ListNode *head, int k);      // 剑指 Offer 22. 链表中倒数第k个节点
    static ListNode *reverseList(ListNode *head);       // *** 剑指 Offer 24. 反转链表 ***
    static ListNode *mergeTwoLists(ListNode *l1, ListNode *l2); // 剑指 Offer 25. 合并两个排序的链表
    static bool isSubStructure(TreeNode *A, TreeNode *B);       // 剑指 Offer 26. 树的子结构
    static TreeNode *mirrorTree(TreeNode *root);        // *** 剑指 Offer 27. 二叉树的镜像 ***
    static TreeNode *mirrorTree02(TreeNode *root);      // *** 剑指 Offer 27. 二叉树的镜像(非递归) ***
    static bool isSymmetric(TreeNode *root);            // *** 剑指 Offer 28. 对称的二叉树 ***
    static vector<int> spiralOrder(vector<vector<int>> &matrix);    // 剑指 Offer 29. 顺时针打印矩阵
    static bool validateStackSequences(vector<int> &pushed, vector<int> &popped);   // 剑指 Offer 31. 栈的压入、弹出序列
    static vector<int> levelOrder(TreeNode *root);      // 剑指 Offer 32 - I. 从上到下打印二叉树
    static vector<vector<int>> levelOrder02(TreeNode *root);        // 剑指 Offer 32 - II. 从上到下打印二叉树 II
    static vector<vector<int>> levelOrder03(TreeNode *root);        // 剑指 Offer 32 - III. 从上到下打印二叉树 III
    static bool verifyPostorder(vector<int> &postorder);    // *** 剑指 Offer 33. 二叉搜索树的后序遍历序列 ***
    static vector<vector<int>> pathSum(TreeNode *root, int sum);    // *** 剑指 Offer 34. 二叉树中和为某一值的路径 ***
    static RandomNode *copyRandomList(RandomNode *head);            // ??? 剑指 Offer 35. 复杂链表的复制 ???
    static searchNode *treeToDoublyList(searchNode *root);          // *** 剑指 Offer 36. 二叉搜索树与双向链表 ***
    static vector<string> permutation(string s);        // *** 剑指 Offer 38. 字符串的排列 ***
    static int majorityElement(vector<int> &nums);      // 剑指 Offer 39. 数组中出现次数超过一半的数字
    static vector<int> getLeastNumbers(vector<int> &arr, int k);    // 剑指 Offer 40. 最小的k个数
    static int maxSubArray(vector<int> &nums);          // 剑指 Offer 42. 连续子数组的最大和
    static int countDigitOne(int n);            // ??? 剑指 Offer 43. 1～n 整数中 1 出现的次数 ???
    static int findNthDigit(int n);             // ??? 剑指 Offer 44. 数字序列中某一位的数字 ???
    static string minNumber(vector<int> &nums);         // 剑指 Offer 45. 把数组排成最小的数
    static int translateNum(int num);           // 剑指 Offer 46. 把数字翻译成字符串
};

#endif //THEROADTOADVANCEMENT_OFFERSOLUTIONS_H
