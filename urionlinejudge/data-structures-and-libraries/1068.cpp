#include <stdio.h>
#include <string>
#include <stack>

using namespace std;

const int MAX = 10005;

bool isBalancedExpression(string expression) {
    stack<char> holder;
    for (int i = 0; i < expression.size(); i++) {
        char current = expression[i];
        if (current == '(') holder.push(current);
        if (current == ')') {
            while (!holder.empty() && holder.top() != '(') {
                holder.pop();
            }
            if (holder.empty()) return false;
            else holder.pop();
        }
    }

    return holder.size() == 0;
}

int main() {
    char cExpression[MAX] = "";

    while (scanf(" %[^\n]", cExpression) != EOF) {
        string expression = cExpression;
        if (isBalancedExpression(expression)) {
            printf("correct\n");
        } else {
            printf("incorrect\n");
        }
    }
}