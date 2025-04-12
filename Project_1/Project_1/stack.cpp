#include "stack.h"

template <class KeyType>
Stack<KeyType>::Stack(int MaxStackSize) {
	MaxSize = MaxStackSize;
	stack = new KeyType[MaxSize];
	top = -1;
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
void Stack<KeyType>::Push(KeyType& x) {
	if (IsFull()) StackFull();
	else {
		top = top + 1;
		Stack[top] = x;
	}
}

template <class KeyType>
KeyType* Stack<KeyType>::Pop(KeyType& x) {
	if (IsEmpty()) { StackEmpty(); return 0; }
	x = Stack[top];
	top = top - 1;
	return &x;
}

template <class KeyType>
Stack<KeyType>::~Stack() {
	delete[] Stack;
}