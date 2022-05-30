#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

class Node {
    public:
        int value;
        Node* left;
        Node* right;

        Node(int value) {
            this->value = value;
            this->left = NULL;
            this->right = NULL;
        }

        bool hasNoChildren() {
            return this->right == NULL && this->left == NULL;
        }

        bool hasOnlyLeft() {
            return this->right == NULL && this->left != NULL;
        }
        
};

class BSTree {
    public:
        Node* root;

        BSTree() {
            this->root = NULL;
        }

        void insert(int value) {
            this->insertAtNode(&this->root, value);
        }

        Node* search(int target) {
            return this->searchNode(this->root, target);
        }

        Node* remove(int target) {
            return this->removeNode(&this->root, target);
        }

        vector<int> preorder() {
            vector<int> result;
            this->preRecursive(this->root, &result);
            return result;
        }

        vector<int> inorder() {
            vector<int> result;
            this->inRecursive(this->root, &result);
            return result;
        }

        vector<int> postorder() {
            vector<int> result;
            this->postRecursive(this->root, &result);
            return result;
        }

    private:
        void insertAtNode(Node** node, int value) {
            if (*node == NULL) *node = new Node(value);
            else if (value > (*node)->value) 
                this->insertAtNode(&(*node)->right, value);
            else
                this->insertAtNode(&(*node)->left, value);
        }

        Node* searchNode(Node* node, int target) {
            if (node == NULL) return NULL;

            if (node->value == target)
                return node;
            else if (target > node->value)
                return this->searchNode(node->right, target);
            else 
                return this->searchNode(node->left, target);
        }

        Node* removeNode(Node** node, int target) {
            printf("%d\n", (*node)->value);
            if ((*node)->value == target) {
                Node* found = *node;
                
                if ((*node)->hasNoChildren()) {
                    *node = NULL;
                    free(*node);
                } else if ((*node)->hasOnlyLeft()) {
                    (*node)->value = (*node)->left->value;
                    (*node)->left = NULL;
                    free((*node)->left);
                }

                return found;
            } else if (target > (*node)->value) {
                return this->removeNode(&(*node)->right, target);
            } else {
                return this->removeNode(&(*node)->left, target);
            }
        }

        void preRecursive(Node* node, vector<int>* result) {
            if (node == NULL) return;

            result->push_back(node->value);
            this->preRecursive(node->left, result);
            this->preRecursive(node->right, result);
        }

        void inRecursive(Node* node, vector<int>* result) {
            if (node == NULL) return;

            this->inRecursive(node->left, result);
            result->push_back(node->value);
            this->inRecursive(node->right, result);
        }

        void postRecursive(Node* node, vector<int>* result) {
            if (node == NULL) return;

            this->postRecursive(node->left, result);
            this->postRecursive(node->right, result);
            result->push_back(node->value);
        }
};

void printVector(vector<int> v) {
    int size = v.size();
    for (int i = 0; i < size; i++) {
        if (i == size - 1) printf("%d\n", v[i]);
        else printf("%d ", v[i]);  
    }
}

int main() {

    { // should delete node without children
        BSTree* tree = new BSTree();
        tree->insert(10);
        tree->insert(5);
        tree->insert(20);
        tree->insert(4);
        tree->insert(6);
        tree->insert(8);
        tree->insert(7);
        tree->insert(9);
        Node* removed = tree->remove(4);
        assert(tree->root->left->value == 5);
        assert(tree->root->left->left == NULL);
        assert(removed->value == 4);
    }

    { // should delete node with only left child
        BSTree* tree = new BSTree();
        tree->insert(10);
        tree->insert(5);
        tree->insert(20);
        tree->insert(4);
        tree->insert(6);
        tree->insert(8);
        tree->insert(7);
        tree->insert(9);
        tree->insert(15);
        Node* removed = tree->remove(20);
        assert(tree->root->right->value == 15);
        assert(tree->root->right->left == NULL);
        printf("-> %d\n", removed->value);
        assert(removed->value == 20);
    }

    // char commandCStr[20];
    // BSTree* tree = new BSTree();
    // while (scanf(" %[^\n]", commandCStr) != EOF) {
    //     string command = commandCStr;
        
    //     if (command == "INFIXA") {
    //         printVector(tree->inorder());
    //     } else if (command == "PREFIXA") {
    //         printVector(tree->preorder());
    //     } else if (command == "POSFIXA") {
    //         printVector(tree->postorder());
    //     } else if (command[0] == 'I') {
    //         tree->insert(command[2]);
    //     } else {
    //         char target = command[2];
    //         Node* node = tree->search(target);
    //         if (node == NULL) {
    //             printf("%c nao existe\n", target);
    //         } else {
    //             printf("%c existe\n", node->value);
    //         }
    //     }
    // }

    return 0;
}