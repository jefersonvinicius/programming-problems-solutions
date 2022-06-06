#include <stdio.h>
#include <string>
#include <assert.h>

using namespace std;

class Murder {
    public:
        string name;
        int killed;

        Murder (string name) {
            this->killed = 0;
            this->name = name;
        }
};

class Node {
    public:
        Murder* value;
        Node* left;
        Node* right;

        Node(string murderName) {
            this->value = new Murder(murderName);
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

        void insert(string murderName) {
            Node* alreadyExists = this->searchNode(this->root, murderName);
            if (alreadyExists == NULL)
                this->insertNode(&this->root, murderName);
            else
                alreadyExists->value->killed++;
        }

        void remove(string murderName) {

        }

    private:
        void insertNode(Node** node, string murderName) {
            if (*node == NULL) {
                *node = new Node(murderName);
            } else if (murderName > (*node)->value->name) {
                this->insertNode(&(*node)->right, murderName);
            } else {
                this->insertNode(&(*node)->left, murderName);
            }
        } 

        void removeNode(Node** node, string target) {
            if (*node != NULL && (*node)->value->name == target) {

            } else if (target > (*node)->value->name && (*node)->right) {
                
            }
        }

        Node* searchNode(Node* node, string target) {
            if (node == NULL || node->value->name == target) 
                return node;
            
            if (target > node->value->name)
                return this->searchNode(node->right, target);
            else 
                return this->searchNode(node->left, target);
        }
};

int main() {

    { // should insert
        BSTree* tree = new BSTree();
        tree->insert("Jeferson");
        tree->insert("Isa");
        tree->insert("Zefa");
        assert(tree->root->value->name == "Jeferson");
        assert(tree->root->right->value->name == "Zefa");
        assert(tree->root->left->value->name == "Isa");
    }

    { // should insert
        BSTree* tree = new BSTree();
        tree->insert("Jeferson");
        tree->insert("Isa");
        tree->insert("Zefa");
        tree->insert("Isa");
        assert(tree->root->value->name == "Jeferson");
        assert(tree->root->value->killed == 0);
        assert(tree->root->right->value->name == "Zefa");
        assert(tree->root->right->value->killed == 0);
        assert(tree->root->left->value->name == "Isa");
        assert(tree->root->left->value->killed == 1);
    }

    // char murderNameC[12], killedNameC[12];
    // while (scanf("%s %s", murderNameC, killedNameC) != EOF) {
    //     string murderName = murderNameC, killedName = killedNameC;
    // }

    return 0;
}