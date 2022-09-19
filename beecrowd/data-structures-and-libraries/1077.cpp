#include <stdio.h>
#include <string>
#include <stack>
#include <cctype>

using namespace std;

const int EXPRESSION_MAX = 1005;

int getOperatorPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return -1;
}

string infixToPostfix(string expression) {
    stack<char> expStack;
    string postfix = "";
    
    for (int i = 0; i < expression.size(); i++) {
        char currentChar = expression[i];
        if (isalpha(currentChar) || isdigit(currentChar)) {
            postfix += currentChar;
        } else if (currentChar == '(') {
            expStack.push(currentChar);
        } else if (currentChar == ')') {
            while (!expStack.empty()) {
                char top = expStack.top();
                expStack.pop();
                if (top == '(') break;
                postfix += top;
            }
        } else {
            int currentPrecedence = getOperatorPrecedence(currentChar);
            while (!expStack.empty() && currentPrecedence <= getOperatorPrecedence(expStack.top())) {
                postfix += expStack.top();
                expStack.pop();
            }
            expStack.push(currentChar);
        }
    }

    while (!expStack.empty()) {
        postfix += expStack.top();
        expStack.pop();
    }

    return postfix;
}

int main() {
    int n; scanf("%d", &n);
    
    char cExpression[EXPRESSION_MAX];
    while (n--) {
        scanf(" %[^\n]", cExpression);
        string expression = infixToPostfix(cExpression);
        printf("%s\n", expression.c_str());
    }
}