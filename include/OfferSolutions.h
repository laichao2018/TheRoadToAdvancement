//
// Created by LaiChao on 2020/11/5.
//

#ifndef THEROADTOADVANCEMENT_OFFERSOLUTIONS_H
#define THEROADTOADVANCEMENT_OFFERSOLUTIONS_H
/// ============== 剑指Offer上的题目 ==============

#include "./__OSJudge.h"
#include "./DataStructure/Tree.h"
#include "./DataStructure/List.h"
#include <vector>

using namespace std;


class OfferSolutions {
public:
    //// Easy mode.....
    static int TreeDepth(TreeNode *pRoot);          // 剑指 Offer 38. 二叉树的深度
    static int numWays(int );                       // 剑指 Offer 10- II. 青蛙跳台阶问题
    static vector<int> multiply(const vector<int> &A);          // 剑指 Offer 51. 构建乘积数组
    static int Add(int num1, int num2);             // 剑指 Offer 48. 不用加减乘除做加法
    static void Mirror(TreeNode *pRoot);            // 剑指 Offer 18. 二叉树的镜像
    static vector<int> twoSum(vector<int> &nums, int target);   // 剑指 Offer 57. 和为s的两个数字
    static vector<int> exchange(vector<int> &nums);             // 剑指 Offer 21. 调整数组顺序使奇数位于偶数前面
    static vector<int> exchange2(vector<int> &nums);            // 剑指 Offer 21. 调整数组顺序使奇数位于偶数前面(改进)

    //// Medium mode.....
    static bool findNumberIn2DArray(vector<vector<int>> &matrix, int target);       // 剑指 Offer 04. 二维数组中的查找
    static int minArray(vector<int> &numbers);                  // 剑指 Offer 11. 旋转数组的最小数字
    static int Sum_Solution(int n);                             // 剑指 Offer 47. 求1+2+3+...+n
    static int FindGreatestSumOfSubArray(vector<int> array);    // 剑指 Offer 30. 连续子数组的最大和
    static int jumpFloor(int number);                           // 剑指 Offer 8. 跳台阶
    static bool IsBalanced_Solution(TreeNode *pRoot);           // 剑指 Offer 39. 平衡二叉树
    static void FindNumsAppearOnce(vector<int> data, int *num1, int *num2);         // 剑指 Offer 40. 数组中只出现一次的数字
    static int NumberOf1Between1AndN_Solution(int n);           // 剑指 Offer 31. 整数中1出现的次数
    static ListNode *FindFirstCommonNode(ListNode *pHead1, ListNode *pHead2);       // 剑指 Offer 36. 两个链表的第一个公共结点
    static ListNode *EntryNodeOfLoop(ListNode *pHead);          // 剑指 Offer 55. 链表中环的入口结点
    static int cutRope(int number);                             // 剑指 Offer 67. 剪绳子
};

#endif //THEROADTOADVANCEMENT_OFFERSOLUTIONS_H
