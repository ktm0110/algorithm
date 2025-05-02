#include <iostream>
#include <cstdlib>
#include <ctime>
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
	for (int i = 0; i < n1; i++) {

	}
}

void MergeSort(int* A) {

}

void QuickSort(int* A) {

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
	case '1':
		InsertionSort(A);
	case '2':
		BubbleSort(A);
	case '3':
		MergeSort(A);
	case '4':
		QuickSort(A);
	default:
		cout << "wrong Num" << endl;
		return 1;
	}
	Output(A);

	return 0;
}