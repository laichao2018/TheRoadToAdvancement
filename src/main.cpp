#include "DailyCoding.h"
#include "ModuleSolutions.h"
#include "SortSolutions.h"
#include "DynamicProgramming.h"
#include "TreeSolutions.h"
#include <iostream>
#include <numeric>
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
    vector<int> nums{78, 5, 25, 31, 2};
    // cout << DailyCoding::lemonadeChange(nums) << endl;
    // sort(nums.begin(), nums.end(), [](int a, int b) -> bool { return a > b; });
    // for_each(nums.cbegin(), nums.cend(), [=](int a) { cout << a << " "; });

    int a = accumulate(nums.begin(), nums.end(), 0);
    cout << a << endl;
    //  int a = 100;
    //    auto fun = [&a]() { cout << ++a << endl; };
    //    a = 101;
    //    fun();

    return 0;
}