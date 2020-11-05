#include "../include/DailyCoding.h"
#include "../include/SortSolutions.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> aa{0, 3, 10, 5, 11, 6, 14, 2, 1};;
    SortSolution::bubleSort(aa);
    for (int &init:aa) {
        cout << init << "  ";
    }
    cout << endl;


    return 0;
}