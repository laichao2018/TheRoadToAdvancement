// 用于代码测试
#include "DailyCoding.h"
#include "DynamicProgramming.h"
#include "OfferSolutions.h"
#include "SortSolutions.h"

using namespace std;

int main() {
    vector<int> nums{-1, -1, -1, 1, 1, -1};
    cout << DailyCoding::pivotIndex(nums);
    return 0;
}