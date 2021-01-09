// 用于代码测试
#include "DailyCoding.h"
#include "InterestingFunctions.hpp"
#include "ModuleSolutions.h"
#include "SortSolutions.h"
#include "DynamicProgramming.h"
#include "TreeSolutions.h"
#include "OfferSolutions.h"
#include <iostream>
#include <numeric>
#include <thread>
#include <future>
#include <vector>
#include <mutex>
#include <algorithm>

using namespace std;

int main() {
//    vector<int> nums{4, 2, 4, 5, 6};
    // 1, 1, 2, 3, 5, 8
    // 0 1 1 2 3 5
    int a = -1;
    dis_to_bin(a);
    auto res = DailyCoding::largeGroupPositions("abcdddeeeeaabbbcd");
    return 0;
}