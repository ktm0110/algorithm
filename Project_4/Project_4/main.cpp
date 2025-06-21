// main.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip> // std::fixed, std::setprecision

#include "Point.h"
#include "dijkstra.h"
#include "astar.h"
#include "rrt_star.h" // PointF�� ����ϱ� ���� ����

// ������ �׸��带 �ֿܼ� ����ϴ� �Լ� (���������� ����)
void print_grid(int width, int height, const std::vector<std::vector<int>>& grid, const Point& start, const Point& goal) {
    // ... (������ ����, ���� ����)
}

// ���� ��θ� ���Ͽ� ���� �Լ� (Dijkstra, A*)
void write_path_to_file(const std::string& filename, const std::vector<Point>& path) {
    if (path.empty()) {
        std::cout << "Path not found. No output file generated." << std::endl;
        return;
    }

    std::ofstream output_file(filename);
    if (!output_file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    for (const auto& p : path) {
        output_file << p.x + 1 << " " << p.y + 1 << std::endl;
    }
    output_file.close();
    std::cout << "Path successfully written to " << filename << std::endl;
}

// �Ǽ� ��θ� ���Ͽ� ���� �Լ� (RRT*)
void write_path_to_file_f(const std::string& filename, const std::vector<PointF>& path) {
    if (path.empty()) {
        std::cout << "Path not found. No output file generated." << std::endl;
        return;
    }

    std::ofstream output_file(filename);
    if (!output_file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    // �Ҽ��� �� �ڸ����� �����Ͽ� ���
    output_file << std::fixed << std::setprecision(1);

    for (const auto& p : path) {
        output_file << p.x + 1.0 << " " << p.y + 1.0 << std::endl;
    }
    output_file.close();
    std::cout << "Path successfully written to " << filename << std::endl;
}


int main() {
    // ... (���� �б� �� �׸��� ���� �κ��� ������ ����)
    const int width = 20;
    const int height = 20;
    Point start = { 0, 0 };
    Point goal = { 19, 19 };
    std::vector<std::vector<int>> grid(height, std::vector<int>(width, 0));
    std::ifstream map_file("map.txt");
    if (!map_file.is_open()) { /* ... */ return 1; }
    int num_obstacles;
    map_file >> num_obstacles;
    for (int i = 0; i < num_obstacles; ++i) { /* ... */ }
    map_file.close();
    if (grid[start.y][start.x] == 1) { /* ... */ }
    if (grid[goal.y][goal.x] == 1) { /* ... */ }
    print_grid(width, height, grid, start, goal);
    // ... (������� ���� ����)

    // �˰��� ����
    int choice;
    std::cout << "Select Path Planning Algorithm:" << std::endl;
    std::cout << "1: Dijkstra" << std::endl;
    std::cout << "2: A* (A-Star)" << std::endl;
    std::cout << "3: RRT* (RRT-Star)" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    auto start_time = std::chrono::high_resolution_clock::now();

    switch (choice) {
    case 1: {
        std::vector<Point> path = dijkstra(start, goal, width, height, grid);
        write_path_to_file("path_D.txt", path);
        break;
    }
    case 2: {
        std::vector<Point> path = astar(start, goal, width, height, grid);
        write_path_to_file("path_A.txt", path);
        break;
    }
    case 3: {
        int max_iter = 15000;
        double step_size = 2.0;
        std::cout << "Running RRT* with max_iter=" << max_iter << " and step_size=" << step_size << std::endl;
        std::vector<PointF> path = rrt_star(start, goal, width, height, grid, max_iter, step_size);
        write_path_to_file_f("path_R.txt", path);
        break;
    }
    default:
        std::cerr << "Invalid choice." << std::endl;
        return 1;
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end_time - start_time;

    std::cout << "Time taken: " << elapsed.count() << " ms" << std::endl;

    return 0;
}