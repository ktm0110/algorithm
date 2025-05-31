#include "BFS.h"
#include "queue.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <climits>

using namespace std;

AdjacencyList::AdjacencyList() : numVertex(0), adjList(nullptr), pi(nullptr), d(nullptr) {}

AdjacencyList::~AdjacencyList() {
    if (adjList) {
        for (int i = 1; i <= numVertex; ++i) {
            Node* cur = adjList[i];
            while (cur) {
                Node* tmp = cur;
                cur = cur->next;
                delete tmp;
            }
        }
        delete[] adjList;
    }
    delete[] pi;
    delete[] d;
}
void AdjacencyList::addEdge(int u, int v) {
    adjList[u] = new Node(v, adjList[u]);
}

void AdjacencyList::readFile(const string& filename) {
    if (adjList) {  // ~adjacencyList
        for (int i = 1; i <= numVertex; ++i) {
            Node* cur = adjList[i];
            while (cur) {
                Node* tmp = cur;
                cur = cur->next;
                delete tmp;
            }
        }
        delete[] adjList;
    }

    ifstream fin(filename);
    if (!fin) {
        cout << "cant open file\n";
        exit(1);
    }

    fin >> numVertex;
    adjList = new Node * [numVertex + 1];
    for (int i = 1; i <= numVertex; ++i) adjList[i] = nullptr;

    for (int i = 1; i <= numVertex; ++i) {
        for (int j = 1; j <= numVertex; ++j) {
            int val;
            fin >> val;
            if (val) addEdge(i, j);
        }
    }
    fin.close();
}

void AdjacencyList::bfs(int s) {
    // color, °Å¸®, predecessor
    vector<int> color(numVertex + 1, 0);    // 0:white, 1:gray, 2:black

    if (pi) delete[] pi;
    if (d) delete[] d;
    pi = new int[numVertex + 1];
    d = new int[numVertex + 1];

    for (int i = 1; i <= numVertex; ++i) {
        pi[i] = -1;
        d[i] = INT_MAX;
    }
    Queue<int> Q(numVertex + 10);

    color[s] = 1;
    d[s] = 0;
    pi[s] = -1;
    Q.Enqueue(s);

    while (!Q.IsEmpty()) {
        int u = Q.Dequeue();
        for (Node* p = adjList[u]; p; p = p->next) {
            int v = p->vertex;
            if (color[v] == 0) {
                color[v] = 1;
                d[v] = d[u] + 1;
                pi[v] = u;
                Q.Enqueue(v);
            }
        }
        color[u] = 2;
    }
}



void AdjacencyList::printPath(int s, int v) {
    if (v == s)
        cout << s;
    else if (pi[v] == -1)
        cout << "no path from" << s << " to " << v << " exists";
    else {
        printPath(s, pi[v]);
        cout << " -> " << v;
    }
}
