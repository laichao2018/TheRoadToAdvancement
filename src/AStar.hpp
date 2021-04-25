#ifndef ___ASTAR_HEADER___
#define ___ASTAR_HEADER___
// AStar_ALGORITHM
#pragma once

#include <vector>
#include <list>
#include <cmath>

using namespace std;

const int kCost01 = 10;     // 上下左右移动消耗
const int kCost02 = 40;     // 斜方向移动消耗

struct Point {
    int x, y;       // 二维算法
    int F, G, H;    // F = G + H
    Point *parent;  // 上一个点，为了拿到路径
    Point(int _x, int _y) : x(_x), y(_y), F(0), G(0), H(0), parent(nullptr) {}
};

class AStar {
public:
    void initAStar(vector<vector<int>> &_maze);

    list<Point *> getPath(Point &startPoint, Point &endPoint, bool isIgnoreCorner);

private:
    Point *findPath(Point &startPoint, Point &endPoint, bool isIgnoreCorner);

    vector<Point *> getSurroundPoints(const Point *point, bool isIgnoreCorner) const;

    // 判断某点是否可以用于下一步判断
    bool isCanReach(const Point *point, const Point *target, bool isIgnoreCorner) const;

    // 判断开启/关闭列表中是否包含某点
    bool isInList(const list<Point *> &list, const Point *point) const;

    // 从开启列表中返回 F 值最小的节点
    Point *getLeastFPoint();

    // 计算F，G，H的值 //
    // G 表示从起点 A 移动到网格上指定方格的移动耗费 (可沿斜方向移动).
    int calG(Point *startPoint, Point *endPoint);

    // H 表示从指定的方格移动到终点 B 的预计耗费 (H 有很多计算方法, 本代码使用简单的欧几里得距离计算方法).
    int calH(Point *point, Point *end);

    // F = G + H
    int calF(Point *point);

private:
    vector<vector<int>> maze;
    list<Point *> openList;     // 开启列表
    list<Point *> closeList;    // 关闭列表
};

////////////////////////////////////////////////////////////////////////////////////////
//                                      定 义 函 数                                    //
////////////////////////////////////////////////////////////////////////////////////////
void AStar::initAStar(vector<vector<int>> &_maze) {
    this->maze = _maze;
}

list<Point *> AStar::getPath(Point &startPoint, Point &endPoint, bool isIgnoreCorner) {

}

int AStar::calG(Point *startPoint, Point *endPoint) {
    // 检查是否斜走
    int extraG = (abs(startPoint.x - endPoint.x) + abs(startPoint.y - endPoint.y)) == 1 ? kCost01 : kCost02;
    // 如果是初始节点，则其父节点是空
    int parentG = endPoint->parent == nullptr ? 0 : endPoint->parent->G;
    return extraG + parentG;
}

int AStar::calH(Point *point, Point *end) {
    // 用简单的欧几里得距离计算H，这个H的计算是关键，还有很多算法****，还可以考虑坡度等因素
    double tmpX = pow((end->x - point->x), 2);
    double tmpY = pow((end->y - point->y), 2);
    return sqrt(tmpX + tmpY) * kCost01;
}

int AStar::calF(Point *point) {
    return point->G + point->H;
}

Point *AStar::getLeastFPoint() {
    if (!openList.empty()) {
        auto resPoint = openList.front();
        for (auto &curr:openList) {
            if (curr->F < resPoint->F) resPoint = curr;
        }
        return resPoint;
    }
    return nullptr;
}

bool AStar::isInList(const list<Point *> &list, const Point *point) const {
    // 判断某个节点是否在列表中，这里不能比较指针，因为每次加入列表是新开辟的节点，只能比较坐标
    for (auto &curr:list) {
        if (curr->x == point->x && curr->y == point->y) return true;
    }
    return false;
}

bool AStar::isCanReach(const Point *point, const Point *target, bool isIgnoreCorner) const {
    // 如果点与当前节点重合、超出地图、是障碍物、或者在关闭列表中，返回false
    if (target->x < 0 || target->x > maze.size() - 1 || target->y < 0 || target->y > maze[0].size() - 1 ||
        maze[target->x][target->y] == 1 || (target->x == point->x && target->y == point->y) ||
        isInList(closeList, target))
        return false;
    // 非斜角可以
    if (abs(point->x - target->x) + abs(point->y - target->y) == 1) return true;
    // 斜对角要判断是否绊住
    if (maze[point->x][target->y] == 0 && maze[target->x][point->y] == 0) return true;
    else return isIgnoreCorner;
}

vector<Point *> AStar::getSurroundPoints(const Point *point, bool isIgnoreCorner) const {
    vector<Point *> surroundPoints;
    for (int x = point->x - 1; x <= point->x + 1; x++) {
        for (int y = point->y - 1; y <= point->y + 1; y++) {
            if (isCanReach(point, new Point(x, y), isIgnoreCorner))
                surroundPoints.push_back(new Point(x, y));
        }
    }
    return surroundPoints;
}

Point *AStar::findPath(Point &startPoint, Point &endPoint, bool isIgnoreCorner) {
    // 置入起点,拷贝开辟一个节点，内外隔离
    openList.push_back(new Point(startPoint.x, startPoint.y));
    while (!openList.empty()) {
        auto currPoint = getLeastFPoint();  // 找到F值最小的点
        openList.remove(currPoint);         // 从开启列表中删除
        closeList.push_back(currPoint);     // 放入关闭列表
        // 1, 找到当前周围八个格中可以通过的格子
        auto surroundPoints = getSurroundPoints(currPoint, isIgnoreCorner);
        for (auto &tmpPoint:surroundPoints) {
            // 2, 对某一个格子，如果它不在开启列表中，加入到开启列表，设置当前格为其父节点，计算F G H
            if (!isInList(openList, tmpPoint)) {
                tmpPoint->parent = currPoint;
                tmpPoint->G=
            }
        }

    }
}

#endif