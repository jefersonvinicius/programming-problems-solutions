#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

class Node {
    public:
        char value;
        Node* left;
        Node* right;

        Node(char value) {
            this->value = value;
            this->left = NULL;
            this->right = NULL;
        }
};

class BSTree {
    public:
        Node* root;

        BSTree() {
            this->root = NULL;
        }

        void insert(char value) {
            this->insertAtNode(&this->root, value);
        }

        Node* search(char target) {
            return this->searchNode(this->root, target);
        }

        vector<char> preorder() {
            vector<char> result;
            this->preRecursive(this->root, &result);
            return result;
        }

        vector<char> inorder() {
            vector<char> result;
            this->inRecursive(this->root, &result);
            return result;
        }

        vector<char> postorder() {
            vector<char> result;
            this->postRecursive(this->root, &result);
            return result;
        }

    private:
        void insertAtNode(Node** node, char value) {
            if (*node == NULL) *node = new Node(value);
            else if (value > (*node)->value) 
                this->insertAtNode(&(*node)->right, value);
            else
                this->insertAtNode(&(*node)->left, value);
        }

        Node* searchNode(Node* node, char target) {
            if (node == NULL) return NULL;

            if (node->value == target)
                return node;
            else if (target > node->value)
                return this->searchNode(node->right, target);
            else 
                return this->searchNode(node->left, target);
        }

        void preRecursive(Node* node, vector<char>* result) {
            if (node == NULL) return;

            result->push_back(node->value);
            this->preRecursive(node->left, result);
            this->preRecursive(node->right, result);
        }

        void inRecursive(Node* node, vector<char>* result) {
            if (node == NULL) return;

            this->inRecursive(node->left, result);
            result->push_back(node->value);
            this->inRecursive(node->right, result);
        }

        void postRecursive(Node* node, vector<char>* result) {
            if (node == NULL) return;

            this->postRecursive(node->left, result);
            this->postRecursive(node->right, result);
            result->push_back(node->value);
        }
};

void printVector(vector<char> v) {
    int size = v.size();
    for (int i = 0; i < size; i++) {
        if (i == size - 1) printf("%c\n", v[i]);
        else printf("%c ", v[i]);  
    }
}

int main() {

    char commandCStr[20];
    BSTree* tree = new BSTree();
    while (scanf(" %[^\n]", commandCStr) != EOF) {
        string command = commandCStr;
        
        if (command == "INFIXA") {
            printVector(tree->inorder());
        } else if (command == "PREFIXA") {
            printVector(tree->preorder());
        } else if (command == "POSFIXA") {
            printVector(tree->postorder());
        } else if (command[0] == 'I') {
            tree->insert(command[2]);
        } else {
            char target = command[2];
            Node* node = tree->search(target);
            if (node == NULL) {
                printf("%c nao existe\n", target);
            } else {
                printf("%c existe\n", node->value);
            }
        }
    }

    return 0;
}