// 用于代码测试
#include "DailyCoding.h"
#include "DynamicProgramming.h"
#include "OfferSolutions.h"
#include "SortSolutions.h"

using namespace std;

int main() {
    vector<int> nums{4, 3, 2, 7, 8, 2, 3, 1};
    auto res = DailyCoding::findDisappearedNumbers(nums);
    for (int i:res) cout << i << " ";
    cout << endl;

    return 0;
}