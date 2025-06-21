// rrt_star.h
#pragma once

#include <vector>
#include "Point.h"

// RRT*를 위한 실수 기반 좌표 구조체
struct PointF {
    double x, y;
};

// 함수 반환 타입을 PointF의 벡터로 변경
std::vector<PointF> rrt_star(
    const Point& start,
    const Point& goal,
    int width,
    int height,
    const std::vector<std::vector<int>>& grid,
    int max_iter,
    double step_size
);