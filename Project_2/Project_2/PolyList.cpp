#include "PolyList.h"
#include <iostream>
using namespace std;

CPolyList::CPolyList() {	// 빈 다항식 리스트 초기화
	head = nullptr;
	last = nullptr;
}

CPolyList::~CPolyList() {	// 동적할당 노드 해제
	cout << "~CPolyList" << endl;
	NODE* temp;
	while (head != nullptr) {
		temp = head;
		head = head->link;
		delete temp;
	}
}

void CPolyList::AppendTerm(int coef, int expo) {	// 새 항 추가
	NODE* newNODE = new NODE;
	newNODE->coef = coef;
	newNODE->expo = expo;
	newNODE->link = nullptr;

	if (head == nullptr) {	// 리스트가 비어있을 때
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
		if (p->expo != 0)	// 지수가 0이면 지수 출력 X
			cout << "x^" << p->expo;
		if (p->link != nullptr)
			cout << " + ";
		p = p->link;
	}
	cout << endl;
}

void CPolyList::AddPoly(CPolyList& Q, CPolyList& R) {	// 두 다항식 덧셈
	NODE* p = Q.head;
	NODE* q = R.head;

	while (p != nullptr && q != nullptr) {
		if (p->expo == q->expo) {	// 지수가 같으면 계수 덧셈
			int sum = p->coef + q->coef;
			if (sum != 0)
				AppendTerm(sum, p->expo);
			p = p->link;
			q = q->link;
		}
		else if (p->expo > q->expo) {	// 높은 지수가 앞에 오도록(내림차순)
			AppendTerm(p->coef, p->expo);
			p = p->link;
		}
		else {
			AppendTerm(q->coef, q->expo);
			q = q->link;
		}
	}

	while (p != nullptr) {	// 두 다항식의 길이가 다를 경우
		AppendTerm(p->coef, p->expo);
		p = p->link;
	}

	while (q != nullptr) {
		AppendTerm(q->coef, q->expo);
		q = q->link;
	}
}


void CPolyList::MultiPoly(CPolyList& Q, CPolyList& R) {	// 다항식 곱셈
    NODE* temp;
    while (head != nullptr) {	// 초기화
        temp = head;
        head = head->link;
        delete temp;
    }
    last = nullptr;

    NODE* p = Q.head;
    while (p != nullptr) {	// Q의 첫번째 노드부터 순회
        NODE* q = R.head;
        while (q != nullptr) {	// R의 각 노드 순회
            int coef = p->coef * q->coef;
            int expo = p->expo + q->expo;

            if (coef == 0) {	// 계수가 0이면 추가X
                q = q->link;
                continue;
            }

            NODE* curr = head;	// 내림차순
            NODE* prev = nullptr;
            while (curr != nullptr && curr->expo > expo) {
                prev = curr;
                curr = curr->link;
            }

            if (curr != nullptr && curr->expo == expo) {	// 동일한 지수가 있으면 계수 덧셈
                curr->coef += coef;
                if (curr->coef == 0) {
                    if (prev == nullptr) {
                        head = curr->link;
                    }
                    else {
                        prev->link = curr->link;
                    }
                    if (curr == last) {
                        last = prev;
                    }
                    delete curr;
                }
            }
            else {	// 동일한 지수가 없다면 newNode 업데이트
                NODE* newNode = new NODE{ coef, expo, curr };
                if (prev == nullptr) {
                    head = newNode;
                }
                else {
                    prev->link = newNode;
                }
                if (curr == nullptr) {
                    last = newNode;
                }
            }
            q = q->link;	// R 순회
        }
        p = p->link;	// Q 순회
    }
}