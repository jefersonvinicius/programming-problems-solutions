#include <stdio.h>
#include <string>

#define MAX_TEXT 52

using namespace std;

int indexOf(string str, int left, int right, char target) {
    int result = -1;
    for (int i = left; i <= right; i++) {
        if (str[i] == target) {
            result = i;
            break;
        }
    }
    return result;
}

class Node {
    public:
        char value;
        Node* left;
        Node* right;

        Node() {}

        Node(char value) {
            this->value = value;
            this->right = NULL;
            this->left = NULL;
        }
};

class Tree {
    public:
        Node root;

        Tree() {}

        string postOrder() {
            string result = "";
            this->postOrderRecursion(&this->root, &result);
            return result;
        }

        static Tree buildFromPreAndInOrder(string preOrder, string inOrder) {
            printf("%s %s\n", preOrder.c_str(), inOrder.c_str());
            int preOrderIndex = 0;
            Node root = Node(preOrder[preOrderIndex]);
            int inIndex = indexOf(inOrder, 0, inOrder.size() - 1, root.value);
            printf("inIndex: %d\n", inIndex);

            Node* left = Tree::buildNode(preOrder, inOrder, 0, inIndex - 1, &preOrderIndex);
            Node* right = Tree::buildNode(preOrder, inOrder, inIndex + 1, inOrder.size() - 1, &preOrderIndex);

            printf("%p\n", left);

            if (left != NULL) {
                root.left = left;
            }
            if (right != NULL) {
                root.right = right;
            }

            Tree tree = Tree();
            tree.root = root;
            return tree;
        }

    private:
        static Node* buildNode(string preOrder, string inOrder, int left, int right, int* preOrderIndex) {
            if (left <= right) {
                (*preOrderIndex)++;
                Node root = Node(preOrder[*preOrderIndex]);
                int inIndex = indexOf(inOrder, left, right, root.value);
                printf("%d\n", inIndex);

                Node* leftNode = Tree::buildNode(inOrder, preOrder, 0, inIndex - 1, preOrderIndex);
                Node* rightNode = Tree::buildNode(inOrder, preOrder, inIndex + 1, right, preOrderIndex);

                if (leftNode != NULL) {
                    root.left = leftNode;
                }
                if (rightNode != NULL) {
                    root.right = rightNode;
                }

                printf("root: %p -> %c\n", root, root.value);

                return &root;
            }
            return NULL;
        }

        void postOrderRecursion(Node* node, string* result) {
            if (node == NULL)
                return;

            Tree::postOrderRecursion(node->left, result);
            Tree::postOrderRecursion(node->right, result);
            *result += node->value;
        }
};

int main() {

    int n; scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int x; 
        char s1[MAX_TEXT], s2[MAX_TEXT];
        scanf("%d", &x);
        scanf("%s", s1);
        scanf("%s", s2);

        Tree tree = Tree::buildFromPreAndInOrder(s1, s2);
        string result = tree.postOrder();
        printf("%s\n", result.c_str());
    }

    return 0;
}