#pragma once
#include <iostream>
using namespace std;

struct NODE
{
	int coef;	// 계수
	int expo;	// 지수
	NODE* link;	// 다음 노드 포인터
};

class CPolyList {
protected:
	NODE* head;
	NODE* last;
public:
	CPolyList();
	~CPolyList();
	void AppendTerm(int coef, int expo);
	void Print();
	void AddPoly(CPolyList& Q, CPolyList& R);
	void MultiPoly(CPolyList& Q, CPolyList& R);
};