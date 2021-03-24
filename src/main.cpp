// 用于代码测试
#include "DailyCoding.h"
#include "DynamicProgramming.h"
#include "OfferSolutions.h"
#include "SortSolutions.h"

using namespace std;

int main() {
    vector<int> nums{3, 1, 4, 2};
    cout << DailyCoding::find132pattern(nums) << endl;

    return 0;
}