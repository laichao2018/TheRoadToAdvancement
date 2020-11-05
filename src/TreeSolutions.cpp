//
// Created by LaiChao on 2020/11/5.
//

#include "TreeSolutions.h"
#include <queue>
#include <stack>

using namespace std;

int TreeSolution::deepestLeavesSum(TreeNode *root) {
    if (root == nullptr) {
        return 0;
    }
    vector<int> levelSum;
    queue<TreeNode *> qNodes;
    qNodes.push(root);
    while (!qNodes.empty()) {
        int currSize = qNodes.size();
        int tmpLevelSum = 0;
        for (int i = 0; i < currSize; i++) {
            TreeNode *currNode = qNodes.front();
            qNodes.pop();
            tmpLevelSum += currNode->val;
            if (currNode->left != nullptr) {
                qNodes.push(currNode->left);
            }
            if (currNode->right != nullptr) {
                qNodes.push(currNode->right);
            }
        }
        levelSum.push_back(tmpLevelSum);
    }
    return levelSum.back();
}

int TreeSolution::sumEvenGrandparent(TreeNode *root) {
    if (root == nullptr) {
        return 0;
    }
    int res = 0;
    queue<TreeNode *> qNodes;
    qNodes.push(root);
    while (!qNodes.empty()) {
        int currSize = qNodes.size();
        for (int i = 0; i < currSize; i++) {
            TreeNode *currNode = qNodes.front();
            qNodes.pop();
            if (currNode->val % 2 == 0) {
                if (currNode->left != nullptr) {
                    if (currNode->left->left != nullptr) {
                        res += currNode->left->left->val;
                    }
                    if (currNode->left->right != nullptr) {
                        res += currNode->left->right->val;
                    }
                }
                if (currNode->right != nullptr) {
                    if (currNode->right->left != nullptr) {
                        res += currNode->right->left->val;
                    }
                    if (currNode->right->right != nullptr) {
                        res += currNode->right->right->val;
                    }
                }
            }

            if (currNode->left != nullptr) {
                qNodes.push(currNode->left);
            }
            if (currNode->right != nullptr) {
                qNodes.push(currNode->right);
            }
        }
    }
    return res;
}

vector<int> TreeSolution::levelTraversal(TreeNode *root) {
    if (root == nullptr) {
        return {};
    }
    vector<int> vRes;
    queue<TreeNode *> qNodes;
    qNodes.push(root);
    while (!qNodes.empty()) {
        int currSize = qNodes.size();
        int tmpSum = 0;
        for (int i = 0; i < currSize; i++) {
            TreeNode *currNode = qNodes.front();
            qNodes.pop();
            tmpSum += currNode->val;
            if (currNode->left != nullptr) {
                qNodes.push(currNode->left);
            }
            if (currNode->right != nullptr) {
                qNodes.push(currNode->right);
            }
        }
        vRes.push_back(tmpSum);
    }
    return vRes;
}

vector<int> TreeSolution::preorderTraversal(TreeNode *root) {
    if (root == nullptr) {
        return {};
    }
    vector<int> vRes;
    stack<TreeNode *> sNodes;
    sNodes.push(root);
    while (!sNodes.empty()) {
        TreeNode *currNode = sNodes.top();
        sNodes.pop();
        vRes.push_back(currNode->val);
        if (currNode->right != nullptr) {   // 先将右子树入栈
            sNodes.push(currNode->right);
        }
        if (currNode->left != nullptr) {
            sNodes.push(currNode->left);
        }
    }
    return vRes;
}

vector<int> TreeSolution::inorderTraversal(TreeNode *root) {
    if (root == nullptr) {
        return {};
    }
    vector<int> vRes;
    stack<TreeNode *> sNodes;
    while (!sNodes.empty() || root != nullptr) {
        if (root != nullptr) {
            sNodes.push(root);
            root = root->left;
        } else {
            TreeNode *currNode = sNodes.top();
            sNodes.pop();
            vRes.push_back(currNode->val);
            root = currNode->right;         // 更新root值，如果为空，将会接着执行出栈
        }
    }
    return vRes;
}










