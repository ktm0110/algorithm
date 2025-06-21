// priorityqueue.h
#pragma once

#include <queue>
#include <vector>
using namespace std;

template<typename T, typename Priority>
struct PriorityQueue {
    typedef pair<Priority, T> PQElement;
    priority_queue<PQElement, vector<PQElement>, greater<PQElement>> elements;

    inline bool empty() const {
        return elements.empty();
    }

    inline void put(T item, Priority priority) {
        elements.emplace(priority, item);
    }

    inline T get() {
        T best_item = elements.top().second;
        elements.pop();
        return best_item;
    }
};