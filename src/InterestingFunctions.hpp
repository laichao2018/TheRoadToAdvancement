//
// Created by laichao on 2021/1/9.
//
// 记录一些有意思、实用的小函数

/// =========================== Catalogue ===========================
/// 测量函数执行时间的复用函数
/// 可变参数模板
/// 折半查找
/// 打印一个32(默认)位数的二进制表达形式 (补码)
/// 汉诺塔问题递归求解
/// 哈夫曼编码C++
/// 生成范围随机数
/// 实现String类的写时拷贝
/// 数组全排列问题(递归实现)
/// =================================================================

#ifndef __INTERESTING_FUNCTIONS__
#define __INTERESTING_FUNCTIONS__

#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>
#include <thread>
#include <future>
#include <vector>
#include <mutex>
#include <algorithm>
#include <queue>
#include <map>
#include <string>
#include <cstring>
#include <string.h>
#include "DataStructure/PointCloud.h"

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

// 生成范围随机数
template<typename T>
T getRangeRand(T _min, T _max) {
    T temp;
    if (_min > _max) {
        temp = _max;
        _max = _min;
        _min = temp;
    }
    return rand() / (double) RAND_MAX * (_max - _min) + _min;
}

bool addNoise(string fileName) {
    ifstream plyFile(fileName);
    if (!plyFile.is_open()) return false;
    string tmp;
    vector<string> headStr;
    for (int i = 0; i < 12; i++) {
        getline(plyFile, tmp);
        headStr.push_back(tmp);
    }
    vector<PointCloud> pointData;
    while (getline(plyFile, tmp)) {
        PointCloud currPoint;
        stringstream ss(tmp);
        string splitStr;
        int flag = 0;
        while (ss >> splitStr) {
            if (flag == 0) {
                currPoint.x = atof(splitStr.c_str());
            } else if (flag == 1) {
                currPoint.y = atof(splitStr.c_str());
            } else if (flag == 2) {
                currPoint.z = atof(splitStr.c_str());
            } else if (flag == 3) {
                currPoint.R = atoi(splitStr.c_str());
            } else if (flag == 4) {
                currPoint.G = atoi(splitStr.c_str());
            } else {
                currPoint.B = atoi(splitStr.c_str());
            }
            flag++;
        }
        pointData.push_back(currPoint);
    }
    int pointNums = pointData.size();
    int addPoints = 1000;
    vector<PointCloud> tmpPoints;
    for (int i = 0; i < 20; i++) {
        tmpPoints.push_back(pointData[i]);
    }
    float x_max, x_min, y_max, y_min, z_max, z_min;
    sort(tmpPoints.begin(), tmpPoints.end(), [](PointCloud a, PointCloud b) { return a.x < b.x; });
    x_min = tmpPoints[0].x;
    x_max = tmpPoints.back().x;

    sort(tmpPoints.begin(), tmpPoints.end(), [](PointCloud a, PointCloud b) { return a.y < b.y; });
    y_min = tmpPoints[0].y;
    y_max = tmpPoints.back().y;

    sort(tmpPoints.begin(), tmpPoints.end(), [](PointCloud a, PointCloud b) { return a.z < b.z; });
    z_min = tmpPoints[0].z;
    z_max = tmpPoints.back().z;

    for (int i = 0; i < 2000; i++) {
        PointCloud p;
        p.x = getRangeRand(x_min, x_max);
        p.y = getRangeRand(y_min, y_max);
        p.z = getRangeRand(z_min, z_max);
        p.R = 255;
        p.G = 0;
        p.B = 0;
        pointData.push_back(p);
    }

    ofstream outPlyFile;
    outPlyFile.open("bunny_noise.ply", ios::app);
    if (!outPlyFile.is_open()) return false;
    for (int i = 0; i < headStr.size(); i++) {
        outPlyFile << headStr[i] << endl;
    }
    for (auto p:pointData) {
        outPlyFile << p.x << " " << p.y << " " << p.z << " " << p.R << " " << p.G << " " << p.B << endl;
    }
    outPlyFile.close();

    plyFile.close();
    return true;
}


// 实现String类的写时拷贝
class MyString {
    // 重载<<运算符，这个写法需要记住，需要设置成友元函数，这样就不属于该类，可以直接调用
    friend ostream &operator<<(ostream &_cout, const MyString &_s);

private:
    char *_pStr;

    int &GetCount() {   // 用来得到该对象所属内存空间的引用计数
        return *((int *) (_pStr - 4));
    }

    inline void Release() {
        // 先--引用计数，如果引用计数为0了，表示该内存空间上已经没有对象存在了,就释放这块内存空间
        if (--GetCount() == 0 && _pStr) {
            delete[](_pStr - 4);    // 注意要连引用计数所占的空间一起释放了
        }
    }

public:
    MyString(char *s = "") : _pStr(new char[strlen(s) + 1 + 4]) {
        *((int *) _pStr) = 1;   // 每次新构造一个对象将前4个字节赋值为1，表示新开辟的空间引用计数为1
        _pStr += 4;     // 让_pstr下移int大小的位置，开始用来存放字符串
        strcpy(_pStr, s);
    }

    MyString(const MyString &s) : _pStr(s._pStr) {
        GetCount()++;   // 将该内存空间上的引用计数+1 .... 还可以这样加的？？？
    }

    MyString &operator=(const MyString &s) {
        if (this != &s) {
            Release();
            // 一个对象要对它进行赋值，那么首先，它肯定是已经创建好的
            // 不管它是通过构造函数创建还是拷贝构造函数创建，它的引用计数肯定是大于0的
            // 通过构造函数创建引用计数为1，通过拷贝构造创建引用计数一定大于1
            // 即它自己一个人用一块内存空间或是和别人共用一块内存空间
            // 那么在对它进行赋值的时候，它就不属于原来那份内存空间了，属于一块新的内存空间
            // 这个时候就要对原来的内存空间的引用计数--，对新的内存空间的引用计数++
            _pStr = s._pStr;
            ++GetCount();   // 对新的内存空间的引用计数++
        }
        return *this;
    }

    ~MyString() {
        Release();
    }

    // *** 写时拷贝，要进行写操作的时候再进行拷贝
    // 在对该类对象做下标修改时，会触发写时拷贝
    char &operator[](std::size_t index) {
        if (GetCount() > 1) {
            --GetCount();
            char *pStr = new char[strlen(_pStr) + 1 + 4];
            *((int *) pStr) = 1;    // 下面三步和构造函数的意义相同，将新空间的引用计数置为1
            pStr += 4;
            strcpy(pStr, _pStr);
            _pStr = pStr;
        }
        return *(_pStr + index);
    }
};

ostream &operator<<(ostream &_cout, const MyString &_s) {
    _cout << _s._pStr;
    return _cout;
}
// ================================================================================================

// 打印变量地址的方式
// printf("s2地址：%x\n", (unsigned int)s2.C_str());

// 数组全排列问题(递归实现)
void printArr(vector<int> &arr) {
    for (int &i:arr) cout << i;
    cout << endl;
}

void swapArr(vector<int> &arr, int i, int j) {
    int tmpNum = arr[i];
    arr[i] = arr[j];
    arr[j] = tmpNum;
}

void permutationArr(vector<int> &arr, int index) {
    if (index == arr.size()) {  // 全排列结束
        printArr(arr);      // 自定义操作
    }
    for (int i = index; i < arr.size(); i++) {
        swapArr(arr, index, i);     // 执行数据交换
        permutationArr(arr, index + 1);    // 执行递归
        swapArr(arr, index, i);     // 恢复现场
    }
}

#endif

