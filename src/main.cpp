// 用于代码测试
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include "DailyCoding.h"
//#include "DynamicProgramming.h"
//#include "OfferSolutions.h"
//#include "SortSolutions.h"
#include "./InterestingFunctions.hpp"
#include "ModuleSolutions.h"

using namespace std;

int main() {
    string s1 = "abc", s2 = "defg";
    cout << EasySolutions::mergeAlternately(s1, s2) << endl;

    return 0;
}