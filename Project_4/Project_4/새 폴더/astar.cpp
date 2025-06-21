// astar.cpp
#include "astar.h"
#include "priorityqueue.h"
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>

double heuristic(const Point& a, const Point& b) {
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

std::vector<Point> astar(
    const Point& start,
    const Point& goal,
    int width,
    int height,
    const std::vector<std::vector<int>>& grid)
{
    PriorityQueue<Point, double> frontier;
    frontier.put(start, 0);

    std::map<Point, Point> came_from;
    std::map<Point, double> cost_so_far;

    came_from[start] = start;
    cost_so_far[start] = 0;

    while (!frontier.empty()) {
        Point current = frontier.get();

        if (current == goal) {
            break;
        }

        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0) continue;

                Point next = { current.x + dx, current.y + dy };

                // *** 핵심 장애물 확인 로직 ***
                if (next.x >= 0 && next.x < width && next.y >= 0 && next.y < height && grid[next.y][next.x] == 0) {
                    double move_cost = (dx == 0 || dy == 0) ? 1.0 : std::sqrt(2.0);
                    double new_cost = cost_so_far[current] + move_cost;

                    if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next]) {
                        cost_so_far[next] = new_cost;
                        double priority = new_cost + heuristic(next, goal);
                        frontier.put(next, priority);
                        came_from[next] = current;
                    }
                }
            }
        }
    }

    // 경로 재구성
    std::vector<Point> path;
    if (came_from.find(goal) == came_from.end()) {
        return path;
    }
    Point current = goal;
    while (!(current == start)) {
        path.push_back(current);
        current = came_from[current];
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}