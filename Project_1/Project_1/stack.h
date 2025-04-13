#pragma once
#ifndef STACK_H
#define STACK_H

template <class KeyType>
class Stack {
private:
	KeyType* stack;
	int MaxSize;
	int top;

public:
	Stack(int MaxStackSize = 100);
	~Stack();

	bool IsFull();
	bool IsEmpty();
	void Push(const KeyType& item);
	KeyType* Pop(KeyType& x);
};

#include "stack.cpp"
#endif