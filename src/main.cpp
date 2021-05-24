#include "ModuleSolutions.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int main() {
    vector<string> words{"hello", "leetcode"};
    string order = "hlabcdefgijkmnopqrstuvwxyz";
    cout << EasySolutions::isAlienSorted(words, order);

    return 0;
}