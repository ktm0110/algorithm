#include "queue.h"
#include <stdexcept>

using namespace std;

template <class KeyType>
Queue<KeyType>::Queue(int MaxQueueSize) {
    MaxSize = MaxQueueSize + 1;
    queue = new KeyType[MaxSize];
    head = tail = 0;
}

template <class KeyType>
Queue<KeyType>::~Queue() {
    delete[] queue;
}

template <class KeyType>
bool Queue<KeyType>::IsEmpty() {
    return head == tail;
}

template <class KeyType>
bool Queue<KeyType>::IsFull() {
    return (tail + 1) % MaxSize == head;
}

template <class KeyType>
void Queue<KeyType>::Enqueue(KeyType& item) {
    if (IsFull()) throw runtime_error("Queue Full");
    queue[tail] = item;
    tail = (tail + 1) % MaxSize;
}

template <class KeyType>
KeyType Queue<KeyType>::Dequeue() {
    if (IsEmpty()) throw runtime_error("Queue Empty");
    KeyType item = queue[head];
    head = (head + 1) % MaxSize;
    return item;
}