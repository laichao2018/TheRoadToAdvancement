//
// Created by LaiChao on 2020/11/7.
// GitHub项目网址：https://github.com/CyC2018/CS-Notes/blob/master/notes/Leetcode%20%E9%A2%98%E8%A7%A3%20-%20%E7%9B%AE%E5%BD%95.md
//

#ifndef THEROADTOADVANCEMENT_IMPORTANT200_H
#define THEROADTOADVANCEMENT_IMPORTANT200_H

#include "./__OSJudge.h"
#include "./DataStructure/List.h"
#include "./DataStructure/Tree.h"
#include <vector>
#include <string>

using namespace std;

/// 双指针
class TwoPointer {
public:
    static vector<int> twoSum(vector<int> &nums, int target);    ///1. 两数之和
    static bool judgeSquareSum(int c);        ///633. 平方数之和
    static string reverseVowels(string s);        //345. 反转字符串中的元音字母
    static bool validPalindrome(string s);        //680. 验证回文字符串 Ⅱ
    static void merge(vector<int> &nums1, int m, vector<int> &nums2, int n);    //88. 合并两个有序数组
    static bool hasCycle(ListNode *head);        //141. 环形链表
    static string findLongestWord(string s, vector<string> &d);    //524. 通过删除字母匹配到字典里最长单词
};

/// 排序
class Sort {
public:
    static int findKthLargest(vector<int> &nums, int k);    //215. 数组中的第K个最大元素
    static vector<int> topKFrequent(vector<int> &nums, int k);        //347. 前 K 个高频元素 ***
    static string frequencySort(string s);        //451. 根据字符出现频率排序
    static void sortColors(vector<int> &nums);        //75. 颜色分类
};

/// 贪心思想
class GreedyThinking {
public:
    static int findContentChildren(vector<int> &g, vector<int> &s);        //455. 分发饼干
    static int eraseOverlapIntervals(vector<vector<int>> &intervals);    //435. 无重叠区间
    static int findMinArrowShots(vector<vector<int>> &points);            //452. 用最少数量的箭引爆气球
    static vector<vector<int>> reconstructQueue(vector<vector<int>> &people);    //406. 根据身高重建队列
    static int maxProfit(vector<int> &prices);        //121. 买卖股票的最佳时机
    static int maxProfit2(vector<int> &prices);        //122. 买卖股票的最佳时机 II
    static int maxProfit3(vector<int> &prices);        // 123. 买卖股票的最佳时机 III	*****
    static vector<vector<int>> findSubsequences(vector<int> &nums);    // 491. 递增子序列
    static bool canPlaceFlowers(vector<int> &flowerbed, int n);        //605. 种花问题
    static bool isSubsequence(string s, string t);        //392. 判断子序列
    static bool checkPossibility(vector<int> &nums);    //665. 非递减数列
    static int maxSubArray(vector<int> &nums);        //53. 最大子序和
    static vector<int> partitionLabels(string S);    //763. 划分字母区间
};

/// 二分查找
class BinarySearch {
public:
    static int mySqrt(int x);                //69. x 的平方根
    static char nextGreatestLetter(vector<char> &letters, char target);    //744. 寻找比目标字母大的最小字母
    static int singleNonDuplicate(vector<int> &nums);    //540. 有序数组中的单一元素
    static int firstBadVersion(int n);        //278. 第一个错误的版本
    static int findMin(vector<int> &nums);    //153. 寻找旋转排序数组中的最小值
    static vector<int> searchRange(vector<int> &nums, int target);            //34. 在排序数组中查找元素的第一个和最后一个位置
};

/// 分治（***）
class DivideConquerAlgorithm {
public:
    static vector<int> diffWaysToCompute(string input);        //241. 为运算表达式设计优先级
    static vector<TreeNode *> generateTrees(int n);
};

/// 搜索
class Search {
public:
    /// BFS
    static int shortestPathBinaryMatrix(vector<vector<int>> &grid);    //1091. 二进制矩阵中的最短路径
    static int numSquares(int n);        //279. 完全平方数
    static int ladderLength(string beginWord, string endWord, vector<string> &wordList);    //127. 单词接龙
    /// DFS
    static int maxAreaOfIsland(vector<vector<int>> &grid);      //695. 岛屿的最大面积
    static int numIslands(vector<vector<char>> &grid);          //200. 岛屿数量
    static int findCircleNum(vector<vector<int>> &M);           //547. 朋友圈
    static void solve(vector<vector<char>> &board);             //130. 被围绕的区域
    static vector<vector<int>> pacificAtlantic(vector<vector<int>> &matrix);    //417. 太平洋大西洋水流问题
    /// Backtracking
    static vector<string> letterCombinations(string digits);        //17. 电话号码的字母组合
    static vector<string> restoreIpAddresses(string s);             //93. 复原IP地址
    static bool exist(vector<vector<char>> &board, string word);    //79. 单词搜索
    static vector<string> binaryTreePaths(TreeNode *root);          //257. 二叉树的所有路径
    static vector<vector<int>> permute(vector<int> &nums);          //46. 全排列
    static vector<vector<int>> permuteUnique(vector<int> &nums);    //47. 全排列 II
    static vector<vector<int>> combine(int n, int k);               //77. 组合
    static vector<vector<int>> combinationSum(vector<int> &candidates, int target);    //39. 组合总和
    static vector<vector<int>> combinationSum2(vector<int> &candidates, int target);    //40. 组合总和 II
};

/// 动态规划
class DynamicProgramming {
public:
    static int climbStairs(int n);		// 70.爬楼梯
    static int climbStairs_dp(int n);	// 70.爬楼梯 (非递归)
    static bool isTarget(vector<int>&arr, int pos, int target);
    static int addMaxSum_rec(vector<int>&arr, int pos);	    // 递归版本
    static int addMaxSum_dp(vector<int>&arr, int pos);		// 非递归版本
    static int rob_rec(vector<int>& nums);		// 198. 强盗抢劫（递归方法）
    static int rob_dp(vector<int>& nums);
    static int rob_circle(vector<int>& nums);	// 213. 强盗在环形街区抢劫（非递归方法）
    static int minPathSum(vector<vector<int>>& grid);	//64. 最小路径和
    static int uniquePaths(int m, int n);		        // 62. 不同路径
    static int numberOfArithmeticSlices(vector<int>& A);	// 413. 等差数列划分
    static int integerBreak(int n);	    //343. 整数拆分
    static int numSquares(int n);		// 279. 完全平方数
    static int numDecodings(string s);	//91. 解码方法 *********
    static int minimumTotal(vector<vector<int>>& triangle);	// 120. 三角形最小路径和
    static bool canPartition(vector<int>& nums);		    // 416. 分割等和子集

    static int robotDP();	/// 广联达面试编程第三题
};

/// 数学
class Math {
public:
    static int countPrimes(int n);		    //204. 计数质数
    static int __gcd(int a, int b);		    // 编程之美：2.7 使用位操作和减法求解最大公约数
    static string convertToBase7(int num);	// 504. 七进制数
    static string toHex(int num);		    // 405. 数字转换为十六进制数
};

/// 位操作
class BitOperation {
public:
    static int hammingDistance(int x, int y);		        // 461. 汉明距离
    static int singleNumber(vector<int>& nums);	            // 136. 只出现一次的数字
    static int missingNumber(vector<int>& nums);	        // 268. 缺失数字
    static vector<int> singleNumber2(vector<int>& nums);	// 260. 只出现一次的数字 III
};

#endif //THEROADTOADVANCEMENT_IMPORTANT200_H
