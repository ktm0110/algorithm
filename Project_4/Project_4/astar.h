// astar.h
#pragma once

#include <vector>
#include "Point.h"
using namespace std;

vector<Point> astar(
    const Point& start,
    const Point& goal,
    int width,
    int height,
    const vector<vector<int>>& grid
);