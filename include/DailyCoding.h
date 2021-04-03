//
// Created by LaiChao on 2020/10/31.
// +++++++ LeetCode 每日一题 +++++++
//

#ifndef THEROADTOADVANCEMENT_DAILYCODING_H
#define THEROADTOADVANCEMENT_DAILYCODING_H

#include "./__OSJudge.h"
#include "../DataStructure/Tree.h"
#include "../DataStructure//List.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class DailyCoding {
public:
    static int minDepth(TreeNode *root);        // 111. 二叉树的最小深度(Leetcode每日一题 20200821)
    static vector<vector<int>> findSubsequences(vector<int> &nums); // 491. 递增子序列
    static vector<string> letterCombinations(string digits);        // 17. 电话号码的字母组合
    static vector<string> findItinerary(vector<vector<string>> &tickets);        // 332. 重新安排行程*****
    static bool judgeCircle(string moves);              // 657. 机器人能否返回原点
    static string shortestPalindrome(string s);         // 214. 最短回文串***** KMP ***** 官方题解（困难）
    static string reverseWords(string s);               // 557. 反转字符串中的单词 III
    static bool canVisitAllRooms(vector<vector<int>> &rooms);       // 841. 钥匙和房间
    static bool PredictTheWinner(vector<int> &nums);                // 486. 预测赢家   ***** 动态规划 *****
    static bool PredictTheWinner2(vector<int> &nums);               // 486. 预测赢家	 ***** 零和博弈 *****
    static bool isNumber(string s);    // 剑指 Offer 20. 表示数值的字符串
    static vector<vector<string>> solveNQueens(int n);              // 51. N 皇后 ***** 困难 *****
    static vector<string> binaryTreePaths(TreeNode *root);          // 257. 二叉树的所有路径 (深度优先遍历--递归)
    static vector<vector<int>> levelOrderBottom(TreeNode *root);    // 107. 二叉树的层次遍历 II
    static vector<int> topKFrequent(vector<int> &nums, int k);      // 347. 前 K 个高频元素
    static vector<vector<int>> combine(int n, int k);        // ??? 77. 组合 ???
    static vector<vector<int>> combinationSum2(vector<int> &candidates, int target);    // 40. 组合总和 II
    static vector<vector<int>> combinationSum3(int k, int n);       // 216. 组合总和 III
    static vector<vector<int>> permuteUnique(vector<int> &nums);    // *** 47. 全排列 II ***
    static int sumOfLeftLeaves(TreeNode *root);        // 404. 左叶子之和
    static int sumOfLeftLeaves2(TreeNode *root);        // 404. 左叶子之和(递归方法)
    static vector<vector<int>> subsets(vector<int> &nums);        // 78. 子集
    static TreeNode *convertBST(TreeNode *root);        // 538. 把二叉搜索树转换为累加树
    static TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder);    // 106. 从中序与后序遍历序列构造二叉树
    static TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q);    // *** 235. 二叉搜索树的最近公共祖先 ***
    static int numJewelsInStones(string J, string S);           // 771. 宝石与石头
    static vector<int> twoSum(vector<int> &nums, int target);   // 1. 两数之和
    static void sortColors(vector<int> &nums);          // 75. 颜色分类
    static void reverseString(vector<char> &s);         // 344. 反转字符串
    static char findTheDifference(string s, string t);        // 389. 找不同
    static bool hasCycle(ListNode *head);               // 141. 环形链表
    static bool canPartition(vector<int> &nums);        // 416. 分割等和子集
    static int getMinimumDifference(TreeNode *root);    // 530. 二叉搜索树的最小绝对差
    static ListNode *swapPairs(ListNode *head);         // 24. 两两交换链表中的节点
    static vector<string> commonChars(vector<string> &A);    // 1002. 查找常用字符
    static Node *connect(Node *root);                   // 116. 填充每个节点的下一个右侧节点指针
    static vector<int> sortedSquares(vector<int> &A);        // 977. 有序数组的平方
    static int totalNQueens(int n);    // ??? 52. N皇后 II ???
    static ListNode *removeNthFromEnd(ListNode *head, int n);    // 19. 删除链表的倒数第N个节点
    static ListNode *removeNthFromEnd2(ListNode *head, int n);    // 19. 删除链表的倒数第N个节点(版本2)
    static bool backspaceCompare(string S, string T);        // 844. 比较含退格的字符串
    static void reorderList(ListNode *head);    // 143. 重排链表
    static bool isLongPressedName(string name, string typed);        // 925. 长按键入
    static vector<int> partitionLabels(string S);           // 763. 划分字母区间
    static bool isPalindrome(ListNode *head);               // 234. 回文链表
    static int videoStitching(vector<vector<int>> &clips, int T);        // 1024. 视频拼接
    static int longestMountain(vector<int> &A);             // 845. 数组中的最长山脉
    static vector<int> smallerNumbersThanCurrent(vector<int> &nums);    // 1365. 有多少小于当前数字的数字
    static vector<int> preorderTraversal(TreeNode *root);   // 144. 二叉树的前序遍历(不用递归)
    static bool uniqueOccurrences(vector<int> &arr);        // 1207. 独一无二的出现次数
    static int sumNumbers(TreeNode *root);          // 129. 求根到叶子节点数字之和
    static int sumNumbers2(TreeNode *root);         // 129. 求根到叶子节点数字之和 (BFS)
    static bool validMountainArray(vector<int> &A);         // 941. 有效的山脉数组
    static vector<int> sortByBits(vector<int> &arr);        // 1356. 根据数字二进制下 1 的数目排序
    static vector<int> relativeSortArray(vector<int> &arr1, vector<int> &arr2);         // 1122. 数组的相对排序
    static string removeKdigits(string num, int k);         // 402. 移掉K位数字
    static vector<vector<int>> reconstructQueue(vector<vector<int>> &people);           // ***406. 根据身高重建队列
    static vector<vector<int>> allCellsDistOrder(int R, int C, int r0, int c0);         // 1030. 距离顺序排列矩阵单元格
    static ListNode *oddEvenList(ListNode *head);           // 328. 奇偶链表
    static void moveZeroes(vector<int> &nums);              // 283. 移动零
    static ListNode *insertionSortList(ListNode *head);     // 147. 对链表进行插入排序
    static ListNode *sortList(ListNode *head);              // 148. 排序链表
    static bool isAnagram(string s, string t);              // 242. 有效的字母异位词
    static int findMinArrowShots(vector<vector<int>> &points);          // 452. 用最少数量的箭引爆气球
    static int countNodes(TreeNode *root);          // 222. 完全二叉树的节点个数
    static string sortString(string s);             // 1370. 上升下降字符串
    static int maximumGap(vector<int> &nums);       // 164. 最大间距
    static int fourSumCount(vector<int> &A, vector<int> &B, vector<int> &C, vector<int> &D);    // 454. 四数相加 II
    static int reversePairs(vector<int> &nums);     // 493. 翻转对
    static int largestPerimeter(vector<int> &A);    // 976. 三角形的最大周长
    static vector<int> searchRange(vector<int> &nums, int target);      // 34. 在排序数组中查找元素的第一个和最后一个位置
    static int maxProfit02(vector<int> &oprices);     // 122. 买卖股票的最佳时机 II
    static vector<vector<int>> insert(vector<vector<int>> &intervals, vector<int> &newInterval);        // 57. 插入区间
    static bool isPossible(vector<int> &nums);      // 659. 分割数组为连续子序列
    static int countPrimes(int n);                  // 204. 计数质数
    static int leastInterval(vector<char> &tasks, int n);               // 621. 任务调度器
    static vector<vector<int>> generate(int numRows);                   // 118. 杨辉三角
    static int matrixScore(vector<vector<int>> &A);                     // 861. 翻转矩阵后的得分
    static int uniquePaths(int m, int n);           // 62. 不同路径
    static bool lemonadeChange(vector<int> &bills);                     // 860. 柠檬水找零
    static int wiggleMaxLength(vector<int> &nums);                      // 376. 摆动序列
    static bool containsDuplicate(vector<int> &nums);                   // 217. 存在重复元素
    static vector<vector<string>> groupAnagrams(vector<string> &strs);  // 49. 字母异位词分组
    static int monotoneIncreasingDigits(int N);            // 738. 单调递增的数字
    static vector<vector<int>> zigzagLevelOrder(TreeNode *root);        // 103. 二叉树的锯齿形层序遍历
    static int firstUniqChar(string s);             // 387. 字符串中的第一个唯一字符
    static int maximalRectangle(vector<vector<char>> &matrix);          // 85. 最大矩形
    static bool isIsomorphic(string s, string t);   // 205. 同构字符串
    static bool canPlaceFlowers(vector<int> &flowerbed, int n);         // 605. 种花问题
    static vector<int> maxSlidingWindow(vector<int> &nums, int k);      // 239. 滑动窗口最大值
    static ListNode *partition(ListNode *head, int x);      // 86. 分隔链表
    static int fib(int n);      // 509. 斐波那契数
    static vector<vector<int>> largeGroupPositions(string s);           // 830. 较大分组的位置
    static int findCircleNum(vector<vector<int>> &isConnected);         // 547. 省份数量
    static void rotate(vector<int> &nums, int k);           // 189. 旋转数组
    static int maxProfit03(vector<int> &prices);            // *** 123. 买卖股票的最佳时机 III ***
    static vector<string> summaryRanges(vector<int> &nums);             // 228. 汇总区间
    static string smallestStringWithSwaps(string s, vector<vector<int>> &pairs);        // ??? 1202. 交换字符串中的元素 ???
    static vector<int>
    sortItems(int n, int m, vector<int> &group, vector<vector<int>> &beforeItems);      // ??? 1203. 项目管理 ???
    static vector<int> findRedundantConnection(vector<vector<int>> &edges);             // *** 684. 冗余连接 ***(并查集)
    static vector<bool> prefixesDivBy5(vector<int> &A);     // 018. 可被 5 整除的二进制前缀
    static int removeStones(vector<vector<int>> &stones);   // *** 947. 移除最多的同行或同列石头 ***(并查集)
    static vector<int> hitBricks(vector<vector<int>> &grid, vector<vector<int>> &hits);     // 803. 打砖块
    static bool checkStraightLine(vector<vector<int>> &coordinates);        // 1232. 缀点成线
    static vector<vector<string>> accountsMerge(vector<vector<string>> &accounts);          // 721. 账户合并
    static int maximumProduct(vector<int> &nums);           // 628. 三个数的最大乘积
    static vector<int> addToArrayForm(vector<int> &A, int K);               // 989. 数组形式的整数加法
    static int findLengthOfLCIS(vector<int> &nums);         // 674. 最长连续递增序列
    static int numEquivDominoPairs(vector<vector<int>> &dominoes);          // 1128. 等价多米诺骨牌对的数量
    static int pivotIndex(vector<int> &nums);               // 724. 寻找数组的中心索引
    static int minimumEffortPath(vector<vector<int>> &heights);             // *** 1631. 最小体力消耗路径 ***
    static vector<int> fairCandySwap(vector<int> &A, vector<int> &B);       // 888. 公平的糖果棒交换
    static int characterReplacement(string s, int k);       // *** 424. 替换后的最长重复字符 ***
    static double findMaxAverage(vector<int> &nums, int k); // 643. 子数组最大平均数 I
    static int equalSubstring(string s, string t, int maxCost);             // 1208. 尽可能使字符串相等
    static int maxScore(vector<int> &cardPoints, int k);    // 1423. 可获得的最大点数
    static bool checkPossibility(vector<int> &nums);        // 665. 非递减数列
    static int maxTurbulenceSize(vector<int> &arr);         // 978. 最长湍流子数组
    static bool checkInclusion(string s1, string s2);       // 567. 字符串的排列
    static vector<int> getRow(int rowIndex);                // 119. 杨辉三角 II
    static vector<int> findDisappearedNumbers(vector<int> &nums);           // 448. 找到所有数组中消失的数字
    static vector<vector<int>> matrixReshape(vector<vector<int>> &nums, int r, int c);      // 566. 重塑矩阵
    static int longestSubarray(vector<int> &nums, int limit);               // 1438. 绝对差不超过限制的最长连续子数组
    static vector<vector<int>> transpose(vector<vector<int>> &matrix);      // 867. 转置矩阵
    static int evalRPN(vector<string> &tokens);             // 150. 逆波兰表达式求值
    static void setZeroes(vector<vector<int>> &matrix);     // 矩阵置零
    static int hammingWeight(uint32_t n);                   // 191. 位1的个数
    static bool find132pattern(vector<int> &nums);          // 456. 132模式
    static ListNode *deleteDuplicates(ListNode *head);      // 82. 删除排序链表中的重复元素 II
    static ListNode *deleteDuplicates01(ListNode *head);    // 83. 删除排序链表中的重复元素
    static ListNode *rotateRight(ListNode *head, int k);    // *** 61. 旋转链表 ***
    static uint32_t reverseBits(uint32_t n);                // 190. 颠倒二进制位
    static bool searchMatrix(vector<vector<int>> &matrix, int target);      // 74. 搜索二维矩阵
    static vector<vector<int>> subsetsWithDup(vector<int> &nums);           // 90. 子集 II
    static int clumsy(int N);           // 1006. 笨阶乘
    static int longestCommonSubsequence(string text1, string text2);        // 1143. 最长公共子序列
};

#endif //THEROADTOADVANCEMENT_DAILYCODING_H
