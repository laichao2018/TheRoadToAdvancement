#include "DailyCoding.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int main() {
    vector<int> nums{4, 14, 2};
    cout << DailyCoding::totalHammingDistance(nums);

    return 0;
}