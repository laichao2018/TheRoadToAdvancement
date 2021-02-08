// 用于代码测试
#include "DailyCoding.h"
#include "DynamicProgramming.h"
#include "OfferSolutions.h"
#include "SortSolutions.h"

using namespace std;

int main() {
    vector<int> nums{9, 4, 2, 10, 7, 8, 8, 1, 9};
    cout << DailyCoding::maxTurbulenceSize(nums);

    return 0;
}