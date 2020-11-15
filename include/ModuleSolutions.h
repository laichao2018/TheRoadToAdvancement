//
// Created by LaiChao on 2020/11/15.
//

#ifndef THEROADTOADVANCEMENT_MODULESOLUTIONS_H
#define THEROADTOADVANCEMENT_MODULESOLUTIONS_H

#include ".//DataStructure//Tree.h"
#include ".//DataStructure//List.h"
#include <vector>
#include <string>

using namespace std;

class EasySolutions {
public:
    static int cakeNumber(int n);                                      // NC-12
    static long long IncreasingArray(vector<int> &array);              // NC-31
    static vector<int> runningSum(vector<int> &nums);                  // Leetcode-easy 1480
    static int numIdenticalPairs(vector<int> &nums);                   // Leetcode-easy 1512
    static int maxDepth(TreeNode *root);                               // Leetcode-easy 104
    static vector<int> shuffle(vector<int> &nums, int n);              // Leetcode-easy 1470
    static int xorOperation(int n, int start);                         // Leetcode-easy 1486
    static vector<bool> kidsWithCandies(vector<int> &candies, int extraCandies);    // Leetcode-easy 1431
    static string restoreString(string s, vector<int> &indices);       // Leetcode-easy 1528
    static int busyStudent(vector<int> &startTime, vector<int> &endTime, int queryTime);    // Leetcode-easy 1450
    static int maxProduct(vector<int> &nums);                          // Leetcode-easy 1464
    static string destCity(vector<vector<string>> &paths);            // Leetcode-easy 1436
    static bool canMakeArithmeticProgression(vector<int> &arr);        // Leetcode-easy 1502
    static bool canBeEqual(vector<int> &target, vector<int> &arr);     // Leetcode-easy 1460
    static vector<int> finalPrices(vector<int> &prices);               // Leetcode-easy 1475
    static string generateTheString(int n);                            // Leetcode-easy 1374
    static int findMagicIndex(vector<int> &nums);

    static int numTeams(vector<int> &rating);

    static TreeNode *getTargetCopy(TreeNode *original, TreeNode *cloned, TreeNode *target);

    static ListNode *removeDuplicateNodes(ListNode *head);

    static int numWaterBottles(int numBottles, int numExchange);

    static vector<int> minSubsequence(vector<int> &nums);

    static int islandPerimeter(vector<vector<int>> &grid);

    static int repeatedNTimes(vector<int> &A);

    static vector<string> letterCasePermutation(string S);

    static string addStrings(string num1, string num2);                    //415. 字符串相加
    static int countGoodTriplets(vector<int> &arr, int a, int b, int c);   //1534. 统计好三元组
    static vector<int> numberOfLines(vector<int> &widths, string S);       //806. 写字符串需要的行数
    static vector<int> nextGreaterElement(vector<int> &nums1, vector<int> &nums2);        //496. 下一个更大元素 I
    static int sumRootToLeaf(TreeNode *root);                              //1022. 从根到叶的二进制数之和
    static int numWays(int n, vector<vector<int>> &relation, int k);      // LCP 07. 传递信息
    static vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int newColor);    //733. 图像渲染
    static bool isBalanced(TreeNode *root);                                // 110. 平衡二叉树
    static vector<vector<int>> subsetsWithDup(vector<int> &nums);         // 90. 子集 II
    static double average(vector<int> &salary);                            // 1491. 去掉最低工资和最高工资后的工资平均值
    static int calPoints(vector<string> &ops);                            // 682. 棒球比赛
    static int removePalindromeSub(string s);                              // 1332. 删除回文子序列
    static vector<string> buildArray(vector<int> &target, int n);         // 1441. 用栈操作构建数组
    static string getPermutation(int n, int k);                            // 60. 第k个排列
    static bool threeConsecutiveOdds(vector<int> &arr);        // 1550. 存在连续三个奇数的数组
    static int isPrefixOfWord(string sentence, string searchWord);        // 1455. 检查单词是否为句中其他单词的前缀
    static int numUniqueEmails(vector<string> &emails);       // 929. 独特的电子邮件地址
    static vector<string> findOcurrences(string text, string first, string second);    // 1078. Bigram 分词
    static uint32_t reverseBits(uint32_t n);           // 190. 颠倒二进制位
    static int calculate(string s);                    // LCP 17. 速算机器人
    static TreeNode *mergeTrees(TreeNode *t1, TreeNode *t2);       // 617. 合并二叉树
    static vector<int> findMode(TreeNode *root);                   // 501. 二叉搜索树中的众数
    static int numSpecial(vector<vector<int>> &mat);              // 1582. 二进制矩阵中的特殊位置
    static vector<int> fraction(vector<int> &cont);                // LCP 02. 分式化简
    static Node *connect(Node *root);                  // 117. 填充每个节点的下一个右侧节点指针 II
    static vector<vector<int>> allCellsDistOrder(int R, int C, int r0, int c0);    // 1030. 距离顺序排列矩阵单元格
    static TreeNode *insertIntoBST(TreeNode *root, int val);    // 701. 二叉搜索树中的插入操作
    static vector<string> fizzBuzz(int n);            // 412. Fizz Buzz
    static int maxNumberOfBalloons(string text);       // 1189. “气球” 的最大数量
    static vector<string> uncommonFromSentences(string A, string B);    // 884. 两句话中的不常见单词
    static bool leafSimilar(TreeNode *root1, TreeNode *root2);        // 872. 叶子相似的树
    static int countBinarySubstrings(string s);        // 696. 计数二进制子串
    static double largestTriangleArea(vector<vector<int>> &points);    // 812. 最大三角形面积
    static int lengthOfLastWord(string s);              // 58. 最后一个单词的长度
    static bool isSameTree(TreeNode *p, TreeNode *q);   // 100. 相同的树
    static bool isSameTree2(TreeNode *p, TreeNode *q);   // 100. 相同的树(非递归方法)
};

class MeduimSolutions {
public:
    static int minOperations(int n);                    // 1551. 使数组中所有元素相等的最小操作数
    static int maxCoins(vector<int> &piles);            // 1561. 你可以获得的最大硬币数目 *****
    static vector<int> processQueries(vector<int> &queries, int m);         // 1409. 查询带键的排列
    static vector<int> deckRevealedIncreasing(vector<int> &deck);           // 950. 按递增顺序显示卡牌
    static int matrixScore(vector<vector<int>> &A);        // 861. 翻转矩阵后的得分 *****
    static int countBattleships(vector<vector<char>> &board);               // 419. 甲板上的战舰
    static int numTilePossibilities(string tiles);        // 1079. 活字印刷  *****  全排序（穷举）(=== 78. 子集 ===)
    static vector<int> lexicalOrder(int n);                // 386. 字典序排数
    static vector<vector<int>> combinationSum3(int k, int n);               // 216. 组合总和 III
    static bool exist(vector<vector<char>> &board, string word);            // 79. 单词搜索
    static vector<vector<int>> combinationSum(vector<int> &candidates, int target);        // 39. 组合总和
    static vector<vector<int>> combinationSum2(vector<int> &candidates, int target);    // 40. 组合总和 II
};

#endif //THEROADTOADVANCEMENT_MODULESOLUTIONS_H
