#include <stdio.h>
#include <string>
#include <stack>
#include <ctype.h>

#define MAX_EXPRESSION 105

using namespace std;

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int getOperatorPrecedence(char c) {
    switch (c) {
        case '+':
        case '-':
            return 1;
            break;
        case '*':
        case '/':
            return 2;
            break;
        default:
            return -1;
            break;
    }
}

string toPostfix(string expression) {
    stack<char> s;
    string result = "";

    for (int i = 0; i < expression.size(); i++) {
        char current = expression[i];
        if (current == ' ') continue;

        if (isalpha(current) || isdigit(current)) {
            result += current;
        } else if (isOperator(current)) {
            int currentPrecedence = getOperatorPrecedence(current);
            while (!s.empty() && currentPrecedence <= getOperatorPrecedence(s.top())) {
                result += s.top();
                s.pop();
            }
            s.push(current);
        }
    }

    while (!s.empty()) {
        result += s.top();
        s.pop();
    }
    
    return result;
}

class Node {
    public: 
        char value;
        Node* right;
        Node* left;

        Node(char value) {
            this->value = value;
        }
};

class Tree {
    public:
        Node* root;
};

Tree* buildTree(string postFixExpression) {
    stack<Node*> nodes;
    for (int i = 0; i < postFixExpression.size(); i++) {
        char current = postFixExpression[i];
        printf("C: %c\n",current);
        if (isalpha(current) || isdigit(current)) {
            nodes.push(new Node(current));
        } else {
            Node* pop1 = nodes.top();
            nodes.pop();
            Node* pop2 = nodes.top();
            nodes.pop();
            Node* root = new Node(current);
            root->left = pop1;
            root->right = pop2; 
        }
    }

    Tree* tree;
    tree->root = nodes.top();
    return tree; 
}



int main() {

    char expressionC[MAX_EXPRESSION];

    while (scanf(" %[^\n]s", expressionC) != EOF) {
        string expression = expressionC;
        printf("%s\n", toPostfix(expression).c_str());
        Tree* tree = buildTree(toPostfix(expression));
    }


    return 0;
}