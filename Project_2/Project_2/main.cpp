#include "PolyList.h"
using namespace std;

int main() {
	CPolyList p1;
	p1.AppendTerm(3, 2);
	p1.AppendTerm(2, 1);
	p1.AppendTerm(5, 0);
	p1.Print();

	CPolyList p2;
	p2.AppendTerm(3, 3);
	p2.AppendTerm(6, 2);
	p2.AppendTerm(2, 1);
	p2.AppendTerm(7, 0);
	p2.Print();

	CPolyList p3;
	p3.AddPoly(p1, p2);
	p3.Print();

	return 0;
}