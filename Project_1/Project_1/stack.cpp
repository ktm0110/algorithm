#include "stack.h"
#ifndef STACK_CPP
#define STACK_CPP

template <class KeyType>
Stack<KeyType>::Stack(int MaxStackSize) {
	MaxSize = MaxStackSize;
	stack = new KeyType[MaxSize];
	top = -1;
}

template <class KeyType>
Stack<KeyType>::~Stack() {
	delete[] stack;
}

template <class KeyType>
bool Stack<KeyType>::IsFull() {
	if (top == MaxSize - 1) return true;
	else return false;
}

template <class KeyType>
bool Stack<KeyType>::IsEmpty() {
	if (top == -1)return true;
	else return false;
}

template <class KeyType>
void Stack<KeyType>::Push(const KeyType& x) {
	if (IsFull()) {
		throw "full stack";
	}
	else {
		top = top + 1;
		stack[top] = x;
	}
}

template <class KeyType>
KeyType* Stack<KeyType>::Pop(KeyType& x) {
	if (IsEmpty()) {
		throw "empty stack";
		return 0;
	}
	x = stack[top];
	top = top - 1;
	return &x;
}

#endif