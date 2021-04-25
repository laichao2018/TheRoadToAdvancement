#include <iostream>
#include <vector>
#include "AStar.hpp"

using namespace std;

int main() {
    vector<vector<int>> maze = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1},
            {1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1},
            {1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1},
            {1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    AStar pStar;
    pStar.initAStar(maze);
    Point start(1, 1);
    Point end(6, 10);
    list<Point *> path = pStar.getPath(start, end, false);
    for (auto &p:path) cout << p->x << ", " << p->y << endl;

    return 0;
}