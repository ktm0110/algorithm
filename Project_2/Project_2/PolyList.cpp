#include "PolyList.h"
#include <iostream>
using namespace std;

CPolyList::CPolyList() {	// �� ���׽� ����Ʈ �ʱ�ȭ
	head = nullptr;
	last = nullptr;
}

CPolyList::~CPolyList() {	// �����Ҵ� ��� ����
	cout << "~CPolyList" << endl;
	NODE* temp;
	while (head != nullptr) {
		temp = head;
		head = head->link;
		delete temp;
	}
}

void CPolyList::AppendTerm(int coef, int expo) {	// �� �� �߰�
	NODE* newNODE = new NODE;
	newNODE->coef = coef;
	newNODE->expo = expo;
	newNODE->link = nullptr;

	if (head == nullptr) {	// ����Ʈ�� ������� ��
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
		if (p->expo != 0)	// ������ 0�̸� ���� ��� X
			cout << "x^" << p->expo;
		if (p->link != nullptr)
			cout << " + ";
		p = p->link;
	}
	cout << endl;
}

void CPolyList::AddPoly(CPolyList& Q, CPolyList& R) {	// �� ���׽� ����
	NODE* p = Q.head;
	NODE* q = R.head;

	while (p != nullptr && q != nullptr) {
		if (p->expo == q->expo) {	// ������ ������ ��� ����
			int sum = p->coef + q->coef;
			if (sum != 0)
				AppendTerm(sum, p->expo);
			p = p->link;
			q = q->link;
		}
		else if (p->expo > q->expo) {	// ���� ������ �տ� ������(��������)
			AppendTerm(p->coef, p->expo);
			p = p->link;
		}
		else {
			AppendTerm(q->coef, q->expo);
			q = q->link;
		}
	}

	while (p != nullptr) {	// �� ���׽��� ���̰� �ٸ� ���
		AppendTerm(p->coef, p->expo);
		p = p->link;
	}

	while (q != nullptr) {
		AppendTerm(q->coef, q->expo);
		q = q->link;
	}
}


void CPolyList::MultiPoly(CPolyList& Q, CPolyList& R) {	// ���׽� ����
    NODE* temp;
    while (head != nullptr) {	// �ʱ�ȭ
        temp = head;
        head = head->link;
        delete temp;
    }
    last = nullptr;

    NODE* p = Q.head;
    while (p != nullptr) {	// Q�� ù��° ������ ��ȸ
        NODE* q = R.head;
        while (q != nullptr) {	// R�� �� ��� ��ȸ
            int coef = p->coef * q->coef;
            int expo = p->expo + q->expo;

            if (coef == 0) {	// ����� 0�̸� �߰�X
                q = q->link;
                continue;
            }

            NODE* curr = head;	// ��������
            NODE* prev = nullptr;
            while (curr != nullptr && curr->expo > expo) {
                prev = curr;
                curr = curr->link;
            }

            if (curr != nullptr && curr->expo == expo) {	// ������ ������ ������ ��� ����
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
            else {	// ������ ������ ���ٸ� newNode ������Ʈ
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
            q = q->link;	// R ��ȸ
        }
        p = p->link;	// Q ��ȸ
    }
}