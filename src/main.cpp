// 用于代码测试
#include "DailyCoding.h"
#include "DynamicProgramming.h"
#include "OfferSolutions.h"
#include "SortSolutions.h"

using namespace std;

int main() {
//    vector<int> nums{0, 1, 1, 3, 3};
    string s = "krrgw";
    string t = "zjxss";
    cout << DailyCoding::equalSubstring(s, t, 19);
    return 0;
}