#include <stdio.h>
#include <vector>

using namespace std;

class Node {
    public:
        int value;
        Node* right;
        Node* left;

        Node(int value) {
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

        void insert(int value) {
            this->insertAtNode(&this->root, value);
        }

        vector<int> inorder() {
            vector<int> result;
            this->_inorder(this->root, &result);
            return result;
        }

        vector<int> preorder() {
            vector<int> result;
            this->_preorder(this->root, &result);
            return result;
        }

        vector<int> postorder() {
            vector<int> result;
            this->_postorder(this->root, &result);
            return result;
        }

    private:
        void _inorder(Node* node, vector<int>* result) {
            if (node == NULL) return;
            this->_inorder(node->left, result);
            result->push_back(node->value);
            this->_inorder(node->right, result);
        }

        void _preorder(Node* node, vector<int>* result) {
            if (node == NULL) return;
            result->push_back(node->value);
            this->_preorder(node->left, result);
            this->_preorder(node->right, result);
        }

        void _postorder(Node* node, vector<int>* result) {
            if (node == NULL) return;
            this->_postorder(node->left, result);
            this->_postorder(node->right, result);
            result->push_back(node->value);
        }

        void insertAtNode(Node** node, int value) {
            if (*node == NULL) {
                *node = new Node(value);
            } else if (value > (*node)->value) {
                this->insertAtNode(&(*node)->right, value);
            } else {
                this->insertAtNode(&(*node)->left, value);
            }
        }
};

void printVector(vector<int> v) {
    for (int i = 0; i < v.size(); i++) {
        if (i == v.size() - 1) printf("%d\n", v[i]);
        else printf("%d ", v[i]);
    }
}

int main() {

    int c; scanf("%d", &c);
    int caseNumber = 1;
    while (c--) {
        int n; scanf("%d", &n);
        BSTree* tree = new BSTree();

        for (int i = 0; i < n; i++) {
            int x; scanf("%d", &x);
            tree->insert(x);
        }

        printf("Case %d:\n", caseNumber);
        printf("Pre.: ");
        printVector(tree->preorder());
        printf("In..: ");
        printVector(tree->inorder());
        printf("Post: ");
        printVector(tree->postorder());
        printf("\n");
        caseNumber++;

        delete tree;
    }

    return 0;
}