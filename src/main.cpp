// 用于代码测试
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include "DailyCoding.h"
//#include "DynamicProgramming.h"
//#include "OfferSolutions.h"
//#include "SortSolutions.h"
#include "./InterestingFunctions.hpp"

using namespace std;

int main() {
    vector<int> data{1, 1, 1, 2, 2, 3, 3, 3, 3};
    cout << DailyCoding::removeDuplicates(data) << endl;

    return 0;
}