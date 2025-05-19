#include "lcs.h"
#include <iostream>

int main() {
        string X = "ACATGGAC";
        string Y = "TGATAATC";

    try {
        LCS a;
        a.LCS_Length(X, Y);
        a.Print_LCS(X, Y);
    }
    catch (const char* error) {
        cout << "X : " << X << '\n' << "Y : " << Y << '\n' << "error : " << error << endl;
    }
}