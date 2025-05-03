#include "stack.h"
#include <iostream>
#include <string>
using namespace std;

int priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

string infix_to_postfix(string exp) {
    Stack<char> stack;
    string postfix = "";
    string num = "";
    int openCheck = 0;

    if (exp[0] != '(') throw "error";

    for (int i = 0; i < exp.size(); i++) {
        char symbol = exp[i];

        if (symbol == ' ') continue;

        if (isdigit(symbol) || symbol == '.') {
            num = num + symbol;
        }
        else {
            if (!num.empty()) {
                postfix = postfix + num + " ";
                num = "";
            }
            if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/') {
                char top;
                while (!stack.IsEmpty()) {
                    stack.Pop(top);
                    if (top != '(' && priority(top) >= priority(symbol)) {
                        postfix = postfix + top + " ";
                    }
                    else {
                        stack.Push(top);
                        break;
                    }
                }
                stack.Push(symbol);
            }
            else if (symbol == '(') {
                stack.Push(symbol);
                openCheck++;
            }
            else if (symbol == ')') {
                openCheck--;
                if (openCheck < 0) throw "error";

                char top;
                while (!stack.IsEmpty()) {
                    stack.Pop(top);
                    if (top != '(') {
                        postfix = postfix + top + " ";
                    }
                    else {
                        break;
                    }
                }
                if (stack.IsEmpty() && openCheck > 0) throw "error";
            }
            else throw "opcode error";
        }
    }

    if (!num.empty()) {
        postfix = postfix + num + " ";
    }

    if (openCheck > 0) throw "error";

    char top;
    while (!stack.IsEmpty()) {
        stack.Pop(top);
        if (top == '(') throw "error";
        postfix = postfix + top + " ";
    }
    return postfix;
}

double evalPostfix(string exp) {
    Stack<double> stack;
    string num = "";

    for (int i = 0; i < exp.size(); i++) {
        char symbol = exp[i];

        if (symbol == ' ') {
            if (!num.empty()) {
                stack.Push(stod(num));
                num = "";
            }
        }

        else if (isdigit(symbol) || symbol == '.') {
            num = num + symbol;
        }
        else if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/') {
            if (!num.empty()) {
                stack.Push(stod(num));
                num = "";
            }

            if (stack.IsEmpty()) throw "less operand";
            double opr2, opr1;
            stack.Pop(opr2);
            if (stack.IsEmpty()) throw "less operand";
            stack.Pop(opr1);
            double result;

            switch (symbol) {
            case '+': result = opr1 + opr2; break;
            case '-': result = opr1 - opr2; break;
            case '*': result = opr1 * opr2; break;
            case '/': 
                if (opr2 == 0) throw "division zero error";
                result = opr1 / opr2;
                break;
            default: result = 0;
            }
            stack.Push(result);
        }
    }

    if (!num.empty()) {
        stack.Push(stod(num));
    }

    double final;
    stack.Pop(final);
    if (!stack.IsEmpty()) throw "many operand";
    return final;
}

int main() {
    try {
        string exp;
        getline(cin, exp);

        string postfix = infix_to_postfix(exp);
        cout << "postfix: " << postfix << endl;

        double result = evalPostfix(postfix);
        cout << "result: " << result << endl;
    }
    catch (const char* error) {
        cout << error << endl;
    }

    return 0;
}