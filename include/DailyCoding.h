//
// Created by LaiChao on 2020/10/31.
//

#ifndef THEROADTOADVANCEMENT_DAILYCODING_H
#define THEROADTOADVANCEMENT_DAILYCODING_H

#include "../DataStructure/Tree.h"
#include "../DataStructure//List.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class DailyCoding {
public:
    static int minDepth(TreeNode *root);        // 111. 二叉树的最小深度(Leetcode每日一题 20200821)
    static vector<vector<int>> findSubsequences(vector<int> &nums);    // 491. 递增子序列
    static vector<string> letterCombinations(string digits);            // 17. 电话号码的字母组合
    static vector<string> findItinerary(vector<vector<string>> &tickets);        // 332. 重新安排行程*****
    static bool judgeCircle(string moves);            // 657. 机器人能否返回原点
    static string shortestPalindrome(string s);    // 214. 最短回文串***** KMP ***** 官方题解（困难）
    static string reverseWords(string s);            // 557. 反转字符串中的单词 III
    static bool canVisitAllRooms(vector<vector<int>> &rooms);        // 841. 钥匙和房间
    static bool PredictTheWinner(vector<int> &nums);    // 486. 预测赢家   ***** 动态规划 *****
    static bool PredictTheWinner2(vector<int> &nums);    // 486. 预测赢家	 ***** 零和博弈 *****
    static bool isNumber(string s);    // 剑指 Offer 20. 表示数值的字符串
    static vector<vector<string>> solveNQueens(int n);        // 51. N 皇后 ***** 困难 *****
    static vector<string> binaryTreePaths(TreeNode *root);        // 257. 二叉树的所有路径 (深度优先遍历--递归)
    static vector<vector<int>> levelOrderBottom(TreeNode *root);    // 107. 二叉树的层次遍历 II
    static vector<int> topKFrequent(vector<int> &nums, int k);        // 347. 前 K 个高频元素
    static vector<vector<int>> combine(int n, int k);        // 77. 组合
    static vector<vector<int>> combinationSum2(vector<int> &candidates, int target);    // 40. 组合总和 II
    static vector<vector<int>> combinationSum3(int k, int n);        // 216. 组合总和 III
    static vector<vector<int>> permuteUnique(vector<int> &nums);    // 47. 全排列 II
    static int sumOfLeftLeaves(TreeNode *root);        // 404. 左叶子之和
    static int sumOfLeftLeaves2(TreeNode *root);        // 404. 左叶子之和(递归方法)
    static vector<vector<int>> subsets(vector<int> &nums);        // 78. 子集
    static TreeNode *convertBST(TreeNode *root);        // 538. 把二叉搜索树转换为累加树
    static int minCameraCover(TreeNode *root);            // 968. 监控二叉树
    static TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder);    // 106. 从中序与后序遍历序列构造二叉树
    static TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q);    // 235. 二叉搜索树的最近公共祖先
    static int numJewelsInStones(string J, string S);        // 771. 宝石与石头
    static vector<int> twoSum(vector<int> &nums, int target);    // 1. 两数之和
    static void sortColors(vector<int> &nums);        // 75. 颜色分类
    static void reverseString(vector<char> &s);    // 344. 反转字符串
    static char findTheDifference(string s, string t);        // 389. 找不同
    static bool hasCycle(ListNode *head);        // 141. 环形链表
    static bool canPartition(vector<int> &nums);    // 416. 分割等和子集
    static int getMinimumDifference(TreeNode *root);    // 530. 二叉搜索树的最小绝对差
    static ListNode *swapPairs(ListNode *head);    // 24. 两两交换链表中的节点
    static vector<string> commonChars(vector<string> &A);    // 1002. 查找常用字符
    static Node *connect(Node *root);        // 116. 填充每个节点的下一个右侧节点指针
    static vector<int> sortedSquares(vector<int> &A);        // 977. 有序数组的平方
    static int totalNQueens(int n);    // 52. N皇后 II ***
    static ListNode *removeNthFromEnd(ListNode *head, int n);    // 19. 删除链表的倒数第N个节点
    static ListNode *removeNthFromEnd2(ListNode *head, int n);    // 19. 删除链表的倒数第N个节点(版本2)
    static bool backspaceCompare(string S, string T);        // 844. 比较含退格的字符串
    static void reorderList(ListNode *head);    // 143. 重排链表
    static bool isLongPressedName(string name, string typed);        // 925. 长按键入
    static vector<int> partitionLabels(string S);        // 763. 划分字母区间
    static bool isPalindrome(ListNode *head);        // 234. 回文链表
    static int videoStitching(vector<vector<int>> &clips, int T);        // 1024. 视频拼接
    static int longestMountain(vector<int> &A);    // 845. 数组中的最长山脉
    static vector<int> smallerNumbersThanCurrent(vector<int> &nums);    // 1365. 有多少小于当前数字的数字
    static vector<int> preorderTraversal(TreeNode *root);    // 144. 二叉树的前序遍历(不用递归)
    static bool uniqueOccurrences(vector<int> &arr);        // 1207. 独一无二的出现次数
    static int sumNumbers(TreeNode *root);          // 129. 求根到叶子节点数字之和
    static int sumNumbers2(TreeNode *root);         // 129. 求根到叶子节点数字之和 (BFS)
    static bool validMountainArray(vector<int>& A);        // 941. 有效的山脉数组
    static vector<int> sortByBits(vector<int>& arr);       // 1356. 根据数字二进制下 1 的数目排序
    static vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2);     // 1122. 数组的相对排序
    static string removeKdigits(string num, int k);        // 402. 移掉K位数字
};

#endif //THEROADTOADVANCEMENT_DAILYCODING_H
