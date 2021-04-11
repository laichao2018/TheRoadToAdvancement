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
#include <unordered_map>
#include <unordered_set>

using namespace std;

int main() {
    vector<string> s01{"Shogun", "Tapioca Express", "Burger King", "KFC"};
    vector<string> s02{"KFC", "Shogun", "Burger King"};
    auto res = EasySolutions::findRestaurant(s01, s02);

    return 0;
}