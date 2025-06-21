// rrt_star.h
#pragma once

#include <vector>
#include "Point.h"
using namespace std;

struct PointF {
    double x, y;
};

vector<PointF> rrt_star(
    const Point& start,
    const Point& goal,
    int width,
    int height,
    const vector<vector<int>>& grid,
    int max_iter,
    double step_size
);