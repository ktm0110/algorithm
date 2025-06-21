// rrt_star.cpp
#include "rrt_star.h"
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <map>
#include <iostream>

// 실수 좌표 사이의 거리 계산
inline double distanceF(const PointF& a, const PointF& b) {
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

// Node 구조체가 PointF를 사용하도록 변경
struct Node {
    PointF pos;
    int parent_id;
    double cost;
};

// 충돌 체크 함수는 내부적으로 정수로 변환하여 그리드 확인
bool is_collision_free(const PointF& p1, const PointF& p2, int width, int height, const std::vector<std::vector<int>>& grid) {
    double dist = distanceF(p1, p2);
    if (dist < 1.0) return true;
    int steps = static_cast<int>(dist);

    for (int i = 0; i <= steps; ++i) {
        double t = (double)i / steps;
        double x = p1.x + t * (p2.x - p1.x);
        double y = p1.y + t * (p2.y - p1.y);

        int grid_x = static_cast<int>(x);
        int grid_y = static_cast<int>(y);

        if (grid_x < 0 || grid_x >= width || grid_y < 0 || grid_y >= height || grid[grid_y][grid_x] == 1) {
            return false;
        }
    }
    return true;
}

// 함수의 반환 타입과 내부 로직을 PointF 기준으로 수정
std::vector<PointF> rrt_star(
    const Point& start,
    const Point& goal,
    int width,
    int height,
    const std::vector<std::vector<int>>& grid,
    int max_iter,
    double step_size)
{
    std::vector<Node> tree;
    // 시작점은 정수 Point를 실수 PointF로 변환하여 추가
    tree.push_back({ {(double)start.x, (double)start.y}, -1, 0.0 });

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis_w(0, width - 1);
    std::uniform_real_distribution<> dis_h(0, height - 1);
    std::uniform_real_distribution<> dis_goal(0, 1);

    PointF goal_f = { (double)goal.x, (double)goal.y };

    for (int i = 0; i < max_iter; ++i) {
        PointF rand_point;
        if (dis_goal(gen) > 0.9) {
            rand_point = goal_f;
        }
        else {
            rand_point = { dis_w(gen), dis_h(gen) };
        }

        int nearest_node_id = -1;
        double min_dist = std::numeric_limits<double>::max();
        for (int j = 0; j < tree.size(); ++j) {
            double d = distanceF(tree[j].pos, rand_point);
            if (d < min_dist) {
                min_dist = d;
                nearest_node_id = j;
            }
        }
        const Node& nearest_node = tree[nearest_node_id];

        // Steer: static_cast<int> 제거하여 실수 좌표 유지
        PointF new_point = rand_point;
        double d = distanceF(nearest_node.pos, rand_point);
        if (d > step_size) {
            new_point.x = nearest_node.pos.x + step_size * (rand_point.x - nearest_node.pos.x) / d;
            new_point.y = nearest_node.pos.y + step_size * (rand_point.y - nearest_node.pos.y) / d;
        }

        if (!is_collision_free(nearest_node.pos, new_point, width, height, grid)) {
            continue;
        }

        std::vector<int> near_node_ids;
        double search_radius = std::min(step_size * 3.0, 50.0);
        for (int j = 0; j < tree.size(); ++j) {
            if (distanceF(tree[j].pos, new_point) < search_radius) {
                near_node_ids.push_back(j);
            }
        }

        int parent_id = nearest_node_id;
        double min_cost = nearest_node.cost + distanceF(nearest_node.pos, new_point);

        for (int id : near_node_ids) {
            const Node& near_node = tree[id];
            if (is_collision_free(near_node.pos, new_point, width, height, grid)) {
                double cost = near_node.cost + distanceF(near_node.pos, new_point);
                if (cost < min_cost) {
                    min_cost = cost;
                    parent_id = id;
                }
            }
        }

        Node new_node = { new_point, parent_id, min_cost };
        tree.push_back(new_node);
        int new_node_id = tree.size() - 1;

        for (int id : near_node_ids) {
            if (id == parent_id) continue;
            Node& near_node = tree[id];
            double cost_via_new = new_node.cost + distanceF(new_node.pos, near_node.pos);
            if (cost_via_new < near_node.cost && is_collision_free(new_node.pos, near_node.pos, width, height, grid)) {
                near_node.parent_id = new_node_id;
                near_node.cost = cost_via_new;
            }
        }

        double dist_to_goal = distanceF(new_node.pos, goal_f);
        if (dist_to_goal < step_size && is_collision_free(new_node.pos, goal_f, width, height, grid)) {
            tree.push_back({ goal_f, new_node_id, new_node.cost + dist_to_goal });
            break;
        }
    }

    std::vector<PointF> path;
    int goal_node_id = -1;

    for (size_t i = 0; i < tree.size(); ++i) {
        if (distanceF(tree[i].pos, goal_f) < 0.1) {
            goal_node_id = i;
            break;
        }
    }

    if (goal_node_id == -1) {
        double min_dist_to_goal = std::numeric_limits<double>::max();
        int best_node_id = -1;
        for (size_t i = 0; i < tree.size(); ++i) {
            if (is_collision_free(tree[i].pos, goal_f, width, height, grid)) {
                double d = distanceF(tree[i].pos, goal_f);
                if (d < min_dist_to_goal) {
                    min_dist_to_goal = d;
                    best_node_id = i;
                }
            }
        }

        if (best_node_id != -1) {
            tree.push_back({ goal_f, best_node_id, tree[best_node_id].cost + min_dist_to_goal });
            goal_node_id = tree.size() - 1;
        }
    }

    if (goal_node_id != -1) {
        int current_id = goal_node_id;
        while (current_id != -1) {
            path.push_back(tree[current_id].pos);
            current_id = tree[current_id].parent_id;
        }
        std::reverse(path.begin(), path.end());
    }

    return path;
}