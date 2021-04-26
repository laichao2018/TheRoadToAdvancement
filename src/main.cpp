#include "DailyCoding.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> weights{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << DailyCoding::shipWithinDays(weights, 5) << endl;

    return 0;
}