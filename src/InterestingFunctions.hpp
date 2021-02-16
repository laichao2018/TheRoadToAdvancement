//
// Created by laichao on 2021/1/9.
//
// 记录一些有意思、实用的小函数

#ifndef __INTERESTING_FUNCTIONS__
#define __INTERESTING_FUNCTIONS__

#include <iostream>
#include <numeric>
#include <thread>
#include <future>
#include <vector>
#include <mutex>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

/// 测量函数执行时间的复用函数
template<typename T>
void measured_function(T &&func) {
    using namespace std::chrono;
    auto start = system_clock::now();                           // 获取当前时间
    func();
    duration<double> diff = system_clock::now() - start;        // 时间差值
    cout << "elapsed " << diff.count() << " seconds" << endl;   // 执行时间
}

// 可变参数模板
template<typename ...T>
void func(T ... args) {
    //sizeof...（sizeof后面有3个小点）计算变参个数
    cout << sizeof...(args) << endl;
}

// 折半查找
template<typename T>
int binarySearch(vector<T> &a, const T &x) {
    int left = 0, right = a.size();
    while (left <= right) {
        int middle = (left + right) / 2;
        if (x == a[middle]) {
            return middle;
        }
        if (x > a[middle]) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }
    return -1;  // 没有找到
}

// 打印一个32(默认)位数的二进制表达形式 (补码)
// 打印数字的真实存储
void dis_to_bin(int data, int i = 32) {
    while (i--) {
        if (data & (1 << i)) printf("1");
        else printf("0");

        if (i % 4 == 0)
            if (i % 8 == 0)
                printf(" ");
            else
                printf("-");
    }
}

// 汉诺塔问题递归求解
void hanoi(int n, char _a, char _b, char _c) {
    if (n == 1) {
        std::cout << ":  " << _a << "  --->  " << _c << endl;
        return;
    }
    hanoi(n - 1, _a, _c, _b);
    std::cout << ":  " << _a << "  --->  " << _c << endl;
    hanoi(n - 1, _b, _a, _c);
}

// 哈夫曼编码C++
// ================================================================================================
// Link:  https://blog.csdn.net/shuangshuang37278752/article/details/11477289
class HuffmanNode {
public:
    char c;         // 表示字符
    int frequency;  // 表示该字符出现的次数或频率
    HuffmanNode *left;
    HuffmanNode *right;

    HuffmanNode(char _c, int _f, HuffmanNode *l = nullptr, HuffmanNode *r = nullptr) : c(_c), frequency(_f), left(l),
                                                                                       right(r) {}

    bool operator<(const HuffmanNode &node) const {
        return this->frequency > node.frequency;
    }
};

void initNode(priority_queue<HuffmanNode> &q, int nodeNum) {
    char c;
    int frequency;
    for (int i = 0; i < nodeNum; i++) {
        cout << "输入字符和结点出现的次数: ";
        cin >> c >> frequency;
        HuffmanNode node(c, frequency);
        q.push(node);
    }
}

void showNode(priority_queue<HuffmanNode> q) {
    while (!q.empty()) {
        HuffmanNode node = q.top();
        q.pop();
        cout << node.c << ", " << node.frequency << endl;
    }
}

// 构造哈夫曼树
void huffmanTree(priority_queue<HuffmanNode> &q) {
    while (!q.empty()) {
        HuffmanNode *left_node = new HuffmanNode(q.top());
        q.pop();
        HuffmanNode *right_node = new HuffmanNode(q.top());
        q.pop();

        HuffmanNode node('R', left_node->frequency + right_node->frequency, left_node, right_node);
        q.push(node);
    }
}

// 打印哈夫曼树
void huffmanCode(HuffmanNode *root, string &prefix, map<char, string> &result) {
    string m_prefix = prefix;
    if (root->left == nullptr) return;

    // 处理左子树
    prefix += "0";
    // 如果是叶子结点则输出,否则递归打印左子树
    if (root->left->left == nullptr) result[root->left->c] = prefix;
    else huffmanCode(root->left, prefix, result);

    // 还原原来的路径,回溯
    prefix = m_prefix;

    // 处理右子树
    prefix += "1";
    //如果是叶子结点，则输出, 否则递归打印右子树
    if (root->right->right == nullptr) result[root->right->c] = prefix;
    else huffmanCode(root->right, prefix, result);
}

void testResult(map<char, string> &result) {
    map<char, string>::const_iterator iter = result.begin();
    while (iter != result.end()) {
        cout << iter->first << " : " << iter->second << endl;
        ++iter;
    }
}

//int main() {
//    priority_queue<HuffmanNode> q;
//    int nodeNum;
//
//    //初始化字符信息
//    cout << "请输入结点个数: ";
//    cin >> nodeNum;
//    initNode(q, nodeNum);
//    //showNode(q);
//
//    //构造哈夫曼树
//    huffmanTree(q);
//
//    //构造哈夫曼编码
//    HuffmanNode root = q.top();
//    string prefix = "";
//    map<char, string> result;
//    huffmanCode(&root, prefix, result);
//
//    //检验结果是否正确
//    testResult(result);
//    return 0;
//}

// ================================================================================================

#endif

