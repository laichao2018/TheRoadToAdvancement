//
// Created by LaiChao on 2020/11/5.
//

#include "OfferSolutions.h"
#include <queue>
#include <vector>

using namespace std;

int OfferSolutions::TreeDepth(TreeNode *pRoot) {
    if (pRoot == nullptr) {
        return 0;
    }
    int res = 0;
    queue<TreeNode *> qNodes;
    qNodes.push(pRoot);
    while (!qNodes.empty()) {
        int currSize = qNodes.size();
        for (int i = 0; i < currSize; i++) {
            res++;
            TreeNode *currNode = qNodes.front();
            qNodes.pop();
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

int OfferSolutions::numWays(int n) {
    vector<int> dpArr(n + 1, 0);
    dpArr[0] = 1;
    dpArr[1] = 1;
    dpArr[2] = 2;
    for (int i = 3; i <= n; i++) {
        dpArr[i] = (dpArr[i - 1] + dpArr[i - 2]) % 1000000007;
    }
    return dpArr[n];
}
