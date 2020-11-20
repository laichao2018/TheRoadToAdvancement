//
// Created by LaiChao on 2020/11/5.
//

#ifndef THEROADTOADVANCEMENT_TREESOLUTIONS_H
#define THEROADTOADVANCEMENT_TREESOLUTIONS_H

#include "./__OSJudge.h"
#include "./DataStructure/Tree.h"
#include <vector>

using namespace std;

class TreeSolution {
public:
    static int deepestLeavesSum(TreeNode *root);                // 1302. 层数最深叶子节点的和
    static int sumEvenGrandparent(TreeNode *root);              // 1315. 祖父节点值为偶数的节点和

    ////// 二叉树的非递归遍历
    static vector<int> preorderTraversal(TreeNode *root);       // 前序遍历（非递归）
    static vector<int> inorderTraversal(TreeNode *root);        // 中序遍历（非递归）
    static vector<int> postorderTraversal(TreeNode *root);      // 后序遍历（非递归）
    static vector<int> levelTraversal(TreeNode *root);          // 层次遍历（非递归）
};


#endif //THEROADTOADVANCEMENT_TREESOLUTIONS_H
