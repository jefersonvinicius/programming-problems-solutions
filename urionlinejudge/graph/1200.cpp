#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

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

    private:
        void insertAtNode(Node** node, char value) {
            if (*node == NULL) *node = new Node(value);
            else if (value > (*node)->value) 
                this->insertAtNode(&(*node)->right, value);
            else
                this->insertAtNode(&(*node)->left, value);
        }
};

int main() {

    { // should create empty tree
        BSTree* tree = new BSTree();
        assert(tree->root == NULL);
    }

    { // should insert on root
        BSTree* tree = new BSTree();
        tree->insert('a');
        assert(tree->root->value == 'a');

    }

    { // should insert on left of root when is lower
        BSTree* tree = new BSTree();
        tree->insert('b');
        tree->insert('a');
        assert(tree->root->value == 'b');
        assert(tree->root->left->value == 'a');
        assert(tree->root->right == NULL);
    }

    { // should insert on right of root when is lower
        BSTree* tree = new BSTree();
        tree->insert('b');
        tree->insert('a');
        tree->insert('c');
        assert(tree->root->value == 'b');
        assert(tree->root->left->value == 'a');
        assert(tree->root->right->value == 'c');
    }

    { // should insert correctly the values
        BSTree* tree = new BSTree();
        tree->insert('m');
        tree->insert('o');
        tree->insert('p');
        tree->insert('n');
        tree->insert('b');
        tree->insert('a');
        tree->insert('c');
        tree->insert('z');
        assert(tree->root->value == 'm');
        assert(tree->root->right->value == 'o');
        assert(tree->root->right->right->value == 'p');
        assert(tree->root->right->left->value == 'n');
        assert(tree->root->left->value == 'b');
        assert(tree->root->left->left->value == 'a');
        assert(tree->root->left->right->value == 'c');
        assert(tree->root->right->right->right->value == 'z');
    }


    return 0;
}