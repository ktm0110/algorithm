// dijkstra.h
#pragma once

#include <vector>
#include "Point.h"

std::vector<Point> dijkstra(
    const Point& start,
    const Point& goal,
    int width,
    int height,
    const std::vector<std::vector<int>>& grid
);