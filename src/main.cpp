// 用于代码测试
#include "DailyCoding.h"
#include "DynamicProgramming.h"
#include "OfferSolutions.h"
#include "SortSolutions.h"

using namespace std;

int main() {
    vector<int> nums{0, 1, 1, 3, 3};
    cout << DailyCoding::findMaxAverage(nums, 4);
    return 0;
}