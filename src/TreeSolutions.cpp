//
// Created by LaiChao on 2020/11/5.
//

#include "TreeSolutions.h"
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

///// ================================== HELP FUNC ==================================

bool isBSTreeUtil(TreeNode *node, int min, int max) {
    if (node == nullptr) {
        return true;
    }
    if (node->val <= min || node->val >= max) {
        return false;
    }
    return isBSTreeUtil(node->left, min, node->val) && isBSTreeUtil(node->right, node->val, max);
}

///// ================================== CLASS FUNC ==================================

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

vector<int> TreeSolution::postorderTraversal(TreeNode *root) {
    if (root == nullptr) {
        return {};
    }
    vector<int> vRes;
    stack<TreeNode *> sNodes;
    /// 根节点 -> 右节点 -> 左节点 -> 逆序输出
    while (!sNodes.empty() || root != nullptr) {
        if (root != nullptr) {
            sNodes.push(root);
            vRes.push_back(root->val);
            root = root->right;
        }
        root = sNodes.top();
        sNodes.pop();
        root = root->left;
    }
    reverse(vRes.begin(), vRes.end());
    return vRes;
}

TreeNode *TreeSolution::newNode(int data) {
    TreeNode *node = (TreeNode *) malloc(sizeof(TreeNode *));
    node->val = data;
    node->left = node->right = nullptr;
    return node;
}

TreeNode *TreeSolution::insertNode(TreeNode *root, int data) {
    if (root == nullptr) {
        return newNode(data);
    } else {
        if (root->val >= data) {
            root->left = insertNode(root->left, data);
        } else {
            root->right = insertNode(root->right, data);
        }
    }
    return root;
}

TreeNode *TreeSolution::insertNode2(TreeNode *root, int data) {
    TreeNode *node = root;
    TreeNode *addNode = newNode(data);
    if (node == nullptr) {
        return addNode;
    }
    TreeNode *parent = nullptr;
    TreeNode *curr = node;
    while (curr != nullptr) {
        parent = curr;
        if (curr->val >= data) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    if (parent->val >= data) {
        parent->left = addNode;
    } else {
        parent->right = addNode;
    }
    return node;
}

int TreeSolution::sizeTreeNode(TreeNode *root) {
    if (root == nullptr) {
        return 0;
    }
    return sizeTreeNode(root->left) + sizeTreeNode(root->right) + 1;
}

int TreeSolution::maxDepth(TreeNode *root) {
    if (root == nullptr) {
        return 0;
    } else {
        int leftDepth = maxDepth(root->left);
        int rightDepth = maxDepth(root->right);
        return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
    }
}

int TreeSolution::minValue(TreeNode *root) {
    if (root == nullptr) {
        return 0;
    }
    TreeNode *curr = root;
    while (curr != nullptr) {
        curr = curr->left;
    }
    return curr->val;
}

bool TreeSolution::findData(TreeNode *root, int target) {
    if (root == nullptr) {
        return false;
    }
    if (root->val == target) {
        return true;
    } else if (root->val > target) {
        return findData(root->left, target);
    } else {
        return findData(root->right, target);
    }
}

bool TreeSolution::isBSTree(TreeNode *root) {
    return isBSTreeUtil(root, -99999, 99999);
}

bool TreeSolution::hasPathSum(TreeNode *root, int sum) {
    if (root == nullptr) {
        return sum == 0;
    }
    // 递归判断左右子树
    return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
}

void TreeSolution::mirrorTree(TreeNode *root) {
    // 自顶向下完成镜像
    if (root == nullptr) {
        return;
    }
    TreeNode *tmp = root->left;
    root->left = root->right;
    root->right = tmp;
    mirrorTree(root->left);
    mirrorTree(root->right);
}
