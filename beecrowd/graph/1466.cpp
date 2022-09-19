#include <stdio.h>
#include <vector>
#include <assert.h>

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

        vector<int> levelOrder() {
            vector<int> result;
            result.push_back(this->root->value);
            vector<Node*> nodes;
            if (this->root->left != NULL)
                nodes.push_back(this->root->left);
            if (this->root->right != NULL)
                nodes.push_back(this->root->right);
            
            this->_level(nodes, &result);

            return result;
        }


    private:

        void _level(vector<Node*> levelNodes, vector<int> *result) {
            vector<Node*> nextLevelNodes;
            for (int i = 0; i < levelNodes.size(); i++) {
                Node* current = levelNodes[i];
                result->push_back(current->value);
                if (current->left != NULL)
                    nextLevelNodes.push_back(current->left);
                
                if (current->right != NULL)
                    nextLevelNodes.push_back(current->right);
            }

            if (nextLevelNodes.size() > 0)
                this->_level(nextLevelNodes, result);
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
        printVector(tree->levelOrder());
        printf("\n");
        caseNumber++;

        delete tree;
    }

    return 0;
}