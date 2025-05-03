#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>
using namespace std;

#define LENGTH 100

void InsertionSort(int* A) {
	for (int j = 1; j < LENGTH; j++) {
		int key = A[j];
		int i = j - 1;

		while (i >= 0 && A[i] > key) {
			A[i + 1] = A[i];
			i--;
		}
		A[i + 1] = key;
	}
}

void BubbleSort(int* A) {
	for (int i = 0; i < LENGTH - 1; i++) {
		for (int j = 0; j < LENGTH - i - 1; j++) {
			if (A[j] > A[j + 1]) {
				int key = A[j];
				A[j] = A[j + 1];
				A[j + 1] = key;
			}
		}
	}
}

void Merge(int* A, int p, int q, int r) {
	int n1 = q - p + 1;
	int n2 = r - q;

	int* L = new int[n1 + 1];
	int* R = new int[n2 + 1];

	for (int i = 0; i < n1; i++)
		L[i] = A[p + i];
	for (int j = 0; j < n2; j++)
		R[j] = A[q + j + 1];

	L[n1] = INT_MAX;
	R[n2] = INT_MAX;

	int i = 0;
	int j = 0;
	for (int k = p; k <= r; k++) {
		if (L[i] <= R[j]) {
			A[k] = L[i];
			i++;
		}
		else {
			A[k] = R[j];
			j++;
		}
	}

	delete[] L;
	delete[] R;
}
void MergeSort(int* A, int p, int r) {
	if (p < r) {
		int q = (p + r) / 2;
		MergeSort(A, p, q);
		MergeSort(A, q + 1, r);
		Merge(A, p, q, r);
	}
}
int Partition(int* A, int p, int r) {
	int x = A[r];
	int i = p - 1;
	for (int j = p; j < r; j++) {
		if (A[j] <= x) {
			i++;
			swap(A[i], A[j]);
		}
	}
	swap(A[i + 1], A[r]);
	return i + 1;
}
void QuickSort(int* A, int p, int r) {
	if (p < r) {
		int q = Partition(A, p, r);
		QuickSort(A, p, q - 1);
		QuickSort(A, q + 1, r);
	}
}

void RandomNum(int* A) {
	srand(time(0));
	for (int i = 0; i < LENGTH; i++) {
		A[i] = rand() % 100 + 1;
	}
}

void Output(int* A) {
	for (int i = 0; i < LENGTH; i++) {
		cout << A[i] << " ";
	}
	cout << endl;
}

int main() {
	int A[LENGTH];

	RandomNum(A);
	cout << "Random: \n";
	Output(A);

	int choice;
	cout << "1: Insertion Sort\n";
	cout << "2: Bubble Sort\n";
	cout << "3: Merge Sort\n";
	cout << "4: Quick Sort\n";
	cin >> choice;

	switch (choice) {
	case 1:
		InsertionSort(A);
		break;
	case 2:
		BubbleSort(A);
		break;
	case 3:
		MergeSort(A, 0, LENGTH - 1);
		break;
	case 4:
		QuickSort(A, 0, LENGTH - 1);
		break;
	default:
		cout << "wrong Num" << endl;
		return 1;
	}
	Output(A);

	return 0;
}