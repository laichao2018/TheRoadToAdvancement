#include <iostream>

using namespace std;

typedef struct Node
{
    Node *left;
    Node *right;

    int key;
} Node, *pNode;

class BinaryTree
{
public:
    Node *root;

public:
    // 求节点1和2的最短距离
    int Dist(int, int);

    // 找到最小的共同节点
    Node *findLCA(pNode node, int key1, int key2);

    // 求节点1相对于节点2的深度
    int FindDepth(pNode, int);

    // 打印（先序遍历打印）
    void Print();

    // 先序遍历
    void PreOrder(pNode);

    // 创建模拟的完全二叉树
    static BinaryTree *CreatSimulationTree(const int SIZE);

};

int BinaryTree::Dist(int key1, int key2)
{
    pNode node = this->findLCA(this->root, key1, key2);

    int d1 = FindDepth(node, key1);
    int d2 = FindDepth(node, key2);

    return d1 + d2;
}

Node *BinaryTree::findLCA(pNode lcaRoot, int key1, int key2)
{
    if (!lcaRoot)
    {
        return NULL;
    }

    // 找到其中一个节点即返回
    if (lcaRoot->key == key1 || lcaRoot->key == key2)
    {
        return lcaRoot;
    }

    // 分别在左子树与右子树种查找
    pNode left_lca = findLCA(lcaRoot->left, key1, key2);
    pNode right_lca = findLCA(lcaRoot->right, key1, key2);

    // 如果左右分别有值，则说明两个节点分别在左子树与右子树中，那么此节点即为LAC节点
    if (left_lca && right_lca)
    {
        return lcaRoot;
    }

    // 如果只找到其中一个节点，则另一个节点必然在其子节点内（不讨论节点不存在的情况）
    return left_lca ? left_lca : right_lca;
}

int BinaryTree::FindDepth(pNode lcaRoot, int key)
{
    int depth = 0;

    if (!lcaRoot)
    {
        return -1;
    }

    if (lcaRoot->key == key) {
        return 0;
    }

    // 在左子树中查找
    depth = FindDepth(lcaRoot->left, key);

    // 左子树中没有则在右子树中查找
    if (depth == -1)
    {
        depth = FindDepth(lcaRoot->right, key);
    }

    // 如果depth1=-1，则说明在root节点下找到了节点键为key的节点
    if (depth != -1)
    {
        return depth += 1;
    }

    return -1;
}

void BinaryTree::Print()
{
    cout << "perorder:";
    this->PreOrder(this->root);
    cout << endl;
}

void BinaryTree::PreOrder(pNode node)
{
    if (node != NULL)
    {
        cout << node->key << "  ";

        PreOrder(node->left);
        PreOrder(node->right);
    }

}

BinaryTree *BinaryTree::CreatSimulationTree(const int SIZE)
{
    BinaryTree *bt = new BinaryTree;

    pNode nodeArr[SIZE];

    for (int n = 0; n < SIZE; n ++)
    {
        nodeArr[n] = new Node;
        nodeArr[n]->key = n + 1;
    }

    // 循环设置各节点之间的关系
    for (int n = 0; n < SIZE; n ++) {
        int leftKey = 2 * n + 1;
        int rightKey = 2 * n + 2;

        if (leftKey < SIZE)
        {
            nodeArr[n]->left = nodeArr[leftKey];
        } else {
            nodeArr[n]->left = NULL;
        }

        if (rightKey < SIZE)
        {
            nodeArr[n]->right = nodeArr[rightKey];
        } else {
            nodeArr[n]->right = NULL;
        }
    }

    bt->root = nodeArr[0];

    return bt;
}

int main()
{
    BinaryTree *bt = BinaryTree::CreatSimulationTree(15);

    bt->Print();

    cout << "Dist(9, 11) = " << bt->Dist(9, 11) << endl;
    cout << "Dist(8, 12) = " << bt->Dist(8, 12) << endl;
    cout << "Dist(8, 2) = " << bt->Dist(8, 2) << endl;

    return 0;
}

