#include "DailyCoding.h"
#include "ModuleSolutions.h"
#include "SortSolutions.h"
#include "DynamicProgramming.h"
#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <mutex>

using namespace std;

std::mutex mtx;

/// 测量函数执行时间的复用函数
template<typename T>
void measured_function(T &&func) {
    using namespace std::chrono;
    auto start = system_clock::now();                           // 获取当前时间
    func();
    duration<double> diff = system_clock::now() - start;        // 时间差值
    cout << "elapsed " << diff.count() << " seconds" << endl;   // 执行时间
}


class posStr {
public:
    string gjName;        // 工井名
    string mxName;        // 模型名
    string jmName;        // 截面名
    string KongHao;        // 孔号
    string syPoint;        // 示意点
};

vector<posStr> analysisData(vector<string> &data) {
    vector<posStr> vRes;
    for (string str : data) {
        posStr pp;
        auto p1 = str.find("-MX");
        pp.gjName = str.substr(0, p1);

        auto p2 = str.find("-JM");
        pp.mxName = str.substr(p1 + 1, p2 - p1 - 1);

        string jmBeh = str.substr(p2 + 1);
        auto pp1 = jmBeh.find("-");
        pp.jmName = jmBeh.substr(0, pp1);

        auto pp2 = jmBeh.find_last_of("-");
        pp.KongHao = jmBeh.substr(pp1 + 1, pp2 - pp1 - 1);


        auto p3 = str.find_last_of("SY");
        pp.syPoint = str.substr(p3 - 1);

        vRes.push_back(pp);
    }
    return vRes;
}

// 可变参数模板
template<typename ...T>
void func(T ... args) {
    //sizeof...（sizeof后面有3个小点）计算变参个数
    cout << sizeof...(args) << endl;
}

int main() {
    vector<int> nums{1, 15, 12, 6, 16, 87, 36};
    SortSolution::radixSort(nums);

    return 0;
}