#pragma once
#include <iostream>
using namespace std;

struct Node {
    int vertex;
    Node* next;
    Node(int v, Node* n = nullptr) : vertex(v), next(n) {}
};

class AdjacencyList {
    int numVertex;
    Node** adjList;
    int* pi;
    int* d;
public:
    AdjacencyList();
    ~AdjacencyList();
    void readFile(const string& filename);
    void addEdge(int u, int v);
    void bfs(int s);
    void printPath(int s, int v);
    const int* getDistance() { return d; }
};