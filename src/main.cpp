#include "DailyCoding.h"
#include "ModuleSolutions.h"
#include "SortSolutions.h"
#include "DynamicProgramming.h"
#include "TreeSolutions.h"
#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <mutex>
#include <algorithm>

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

// 可变参数模板
template<typename ...T>
void func(T ... args) {
    //sizeof...（sizeof后面有3个小点）计算变参个数
    cout << sizeof...(args) << endl;
}

//    cout << upper_bound(nums.begin(), nums.end(), 2) - nums.begin() << endl;

int main() {
    vector<int> nums{5, 5, 5, 10, 20};
    cout << DailyCoding::lemonadeChange(nums) << endl;

    return 0;
}