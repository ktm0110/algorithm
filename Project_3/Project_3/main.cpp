#include "BFS.h"
using namespace std;

int main() {
    AdjacencyList BFS;
    BFS.readFile("graph4.txt");
    int start = 1;
    BFS.bfs(start);

    for (int v = 1; v <= 8; ++v) {
        if (v == start) continue;
        cout << start << " -> " << v << " : ";
        BFS.printPath(start, v);
        cout << " (dist: " << BFS.getDistance()[v] << ")" << endl;
    }
}
