#include "PolyList.h"
#include <iostream>
using namespace std;

CPolyList::CPolyList() {
	head = nullptr;
	last = nullptr;
}

CPolyList::~CPolyList() {
	NODE* temp;
	while (head != nullptr) {
		temp = head;
		head = head->link;
		delete temp;
	}
}

void CPolyList::AppendTerm(int coef, int expo) {
	NODE* newNODE = new NODE;
	newNODE->coef = coef;
	newNODE->expo = expo;
	newNODE->link = nullptr;

	if (head == nullptr) {
		head = newNODE;
		last = newNODE;
	}

	else {
		last->link = newNODE;
		last = newNODE;
	}
}

void CPolyList::Print() {
	NODE* p = head;
	while (p != nullptr) {
		cout << p->coef;
		if (p->expo != 0)	// if 0, not print
			cout << "x^" << p->expo;
		if (p->link != nullptr)
			cout << " + ";
		p = p->link;
	}
	cout << endl;
}

void CPolyList::AddPoly(CPolyList& Q, CPolyList& R) {
	NODE* p = Q.head;
	NODE* q = R.head;

	while (p != nullptr && q != nullptr) {
		if (p->expo == q->expo) {
			int sum = p->coef + q->coef;
			if (sum != 0)
				AppendTerm(sum, p->expo);
			p = p->link;
			q = q->link;
		}
		else if (p->expo > q->expo) {
			AppendTerm(p->coef, p->expo);
			p = p->link;
		}
		else {
			AppendTerm(q->coef, q->expo);
			q = q->link;
		}
	}

	while (p != nullptr) {
		AppendTerm(p->coef, p->expo);
		p = p->link;
	}

	while (q != nullptr) {
		AppendTerm(q->coef, q->expo);
		q = q->link;
	}
}


void MultiPoly(CPolyList& Q, CPolyList& R) {

}