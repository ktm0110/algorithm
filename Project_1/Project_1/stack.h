#ifndef STACK_H
#define STACK_H
#include <iostream>
using namespace std;

template <class KeyType>
class Stack {
private:
	KeyType* stack;
	int MaxSize;
	int top;

public:
	static const int DefaultSize = 100;

	Stack(int MaxStackSize = DefaultSize);
	~Stack();

	bool IsFull();
	bool IsEmpty();
	void Push(KeyType& item);
	KeyType* Pop(KeyType&);
};

#include "stack.cpp"
#endif