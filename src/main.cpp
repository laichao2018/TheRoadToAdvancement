// 用于代码测试
#include "DailyCoding.h"
#include "DynamicProgramming.h"
#include "OfferSolutions.h"
#include "SortSolutions.h"

using namespace std;

int main() {
    vector<int> nums{7, 10, -1, 0, 5, 6, 4};
    SortSolution::shellSort(nums);
    for (int i:nums) cout << i << " ";
    cout << endl;
    return 0;
}