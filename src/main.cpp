// 用于代码测试
#include "DailyCoding.h"
#include "InterestingFunctions.hpp"
#include "ModuleSolutions.h"
#include "SortSolutions.h"
#include "DynamicProgramming.h"
#include "TreeSolutions.h"
#include "OfferSolutions.h"

using namespace std;

int main() {
    vector<int> nums{7, 5, 6, 4};
    cout << OfferSolutions::reversePairs(nums);
    return 0;
}