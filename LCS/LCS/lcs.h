#pragma once
#include <string>
#include <vector>
using namespace std;

class LCS {
protected:
	int** cost;
	int** pointer;
	int row;
	int column;

public:
	LCS();
	~LCS();
	bool LCS_Length(string& X, string& Y);
	string Print_LCS(string& X, string& Y);
};