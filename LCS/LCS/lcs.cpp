#include "lcs.h"
#include <iostream>

using namespace std;

LCS::LCS() : cost(nullptr), pointer(nullptr), row(0), column(0) {}

LCS::~LCS() {
	for (int i = 0; i < row; ++i) {
		delete[] cost[i];
		delete[] pointer[i];
	}
	delete[] cost;
	delete[] pointer;
}

bool LCS::LCS_Length(string& X, string& Y) {
	for (char ch : X + Y)
		if (ch != 'A' && ch != 'C' && ch != 'G' && ch != 'T') throw "wrong alphabet";

	int m = X.length();
	int n = Y.length();
	row = m + 1;
	column = n + 1;

	cost = new int* [row];
	pointer = new int* [row];
	for (int i = 0; i < row; ++i) {
		cost[i] = new int[column] {0};
		pointer[i] = new int[column] {0};
	}

	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (X[i - 1] == Y[j - 1]) {
				cost[i][j] = cost[i - 1][j - 1] + 1;
				pointer[i][j] = 1;	// 대각선
			}
			else if (cost[i - 1][j] >= cost[i][j - 1]) {
				cost[i][j] = cost[i - 1][j];
				pointer[i][j] = 2;	// 위
			}
			else {
				cost[i][j] = cost[i][j - 1];
				pointer[i][j] = 3;	// 왼쪽
			}
		}
	}
	return true;
}

string LCS::Print_LCS(string& X, string& Y) {
	string result;
	int i = X.length();
	int j = Y.length();

	while (i > 0 && j > 0) {
		if (pointer[i][j] == 1) {                      // 대각
			result.push_back(X[i - 1]);
			i = i - 1; j = j - 1;
		}
		else if (pointer[i][j] == 2) {                 // 위
			i = i - 1;
		}
		else {                                     // 왼쪽
			j = j - 1;
		}
	}
	reverse(result.begin(), result.end());
	cout << "X : " << X << '\n' << "Y : " << Y << endl;
	cout << "length : " << result.length() << endl;
	cout << "LCS : " << result << endl;
	return result;
}