#pragma once
#include <iostream>
using namespace std;

struct NODE
{
	int coef;
	int expo;
	NODE* link;
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