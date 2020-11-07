#include "../include/DailyCoding.h"
#include "../include/SortSolutions.h"
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    vector<int> aa{10, 100, 1000, 10000};
    auto res = DailyCoding::sortByBits(aa);
    for (int ii:res) {
        cout << ii << "  ";
    }
    cout << endl;

    return 0;
}