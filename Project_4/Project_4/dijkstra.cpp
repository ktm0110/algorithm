// dijkstra.cpp
#include "dijkstra.h"
#include "priorityqueue.h"
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

vector<Point> dijkstra(
    const Point& start,
    const Point& goal,
    int width,
    int height,
    const vector<vector<int>>& grid)
{
    PriorityQueue<Point, double> frontier;
    frontier.put(start, 0);

    map<Point, Point> came_from;
    map<Point, double> cost_so_far;

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

                if (next.x >= 0 && next.x < width && next.y >= 0 && next.y < height && grid[next.y][next.x] == 0) {
                    double move_cost = (dx == 0 || dy == 0) ? 1.0 : sqrt(2.0);
                    double new_cost = cost_so_far[current] + move_cost;

                    if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next]) {
                        cost_so_far[next] = new_cost;
                        frontier.put(next, new_cost);
                        came_from[next] = current;
                    }
                }
            }
        }
    }

    vector<Point> path;
    if (came_from.find(goal) == came_from.end()) {
        return path;
    }
    Point current = goal;
    while (!(current == start)) {
        path.push_back(current);
        current = came_from[current];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}