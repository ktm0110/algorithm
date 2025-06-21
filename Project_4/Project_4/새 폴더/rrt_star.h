// rrt_star.h
#pragma once

#include <vector>
#include "Point.h"

// RRT*�� ���� �Ǽ� ��� ��ǥ ����ü
struct PointF {
    double x, y;
};

// �Լ� ��ȯ Ÿ���� PointF�� ���ͷ� ����
std::vector<PointF> rrt_star(
    const Point& start,
    const Point& goal,
    int width,
    int height,
    const std::vector<std::vector<int>>& grid,
    int max_iter,
    double step_size
);