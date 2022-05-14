#include <stdio.h>
#include <string>
#include <stack>
#include <queue>
#include <map>
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
    stack<char> support;
    string result = "";

    for (int i = 0; i < expression.size(); i++) {
        char current = expression[i];
        if (current == ' ') continue;

        if (isalpha(current) || isdigit(current)) {
            result += current;
        } else if (current == '(') {
            support.push(current);
        } else if (current == ')') {
            while (true) {
                char top = support.top();
                support.pop();
                if (top == '(') break;
                result += top;
            }
        } else if (isOperator(current)) {
            int currentPrecedence = getOperatorPrecedence(current);
            while (!support.empty() && currentPrecedence <= getOperatorPrecedence(support.top())) {
                result += support.top();
                support.pop();
            }
            support.push(current);
        }
    }

    while (!support.empty()) {
        result += support.top();
        support.pop();
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

class NodeLevel {
    public:
        Node* node;
        int level;

        NodeLevel(Node* node, int level) {
            this->node = node;
            this->level = level;
        }
};

class Tree {
    public:
        Node* root;

        void printLevelOrder() {
            map<int, string> levels;
            queue<NodeLevel*> discovered;
            discovered.push(new NodeLevel(root, 1));

            while (!discovered.empty()) {
                NodeLevel* next = discovered.front();

                if (next->node->left != NULL) 
                    discovered.push(new NodeLevel(next->node->left, next->level + 1));

                if (next->node->right != NULL) 
                    discovered.push(new NodeLevel(next->node->right, next->level + 1));

                if (levels.find(next->level) != levels.end()) {
                    levels[next->level] = next->node->value + levels[next->level];
                } else {
                    levels[next->level] = next->node->value;
                }

                discovered.pop();
            }

            for (auto level : levels) {
                printf("Nivel %d: %s\n", level.first, level.second.c_str());
            }
            
        }

        static Tree* buildTree(string postFixExpression) {
            stack<Node*> nodes;
            for (int i = 0; i < postFixExpression.size(); i++) {
                char current = postFixExpression[i];
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
                    nodes.push(root);
                }
            }

            Tree* tree = new Tree();
            tree->root = nodes.top();
            return tree; 
        }
};





int main() {

    char expressionC[MAX_EXPRESSION];

    bool isFirstCase = true;
    while (scanf(" %[^\n]s", expressionC) != EOF) {
        string expression = expressionC;
        Tree* tree = Tree::buildTree(toPostfix(expression));
        if (!isFirstCase) printf("\n");
        isFirstCase = false;
        tree->printLevelOrder();
    }


    return 0;
}