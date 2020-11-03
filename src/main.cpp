#include "../include/DailyCoding.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    DailyCoding pD;
    vector<int> aa{0, 3, 2, 1};;
    cout << pD.validMountainArray(aa) << endl;

    return 0;
}