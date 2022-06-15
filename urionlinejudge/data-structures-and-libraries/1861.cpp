#include <stdio.h>
#include <string>
#include <assert.h>
#include <vector>
#include <unordered_map>

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

        bool hasNoneChildren() {
            return this->left == NULL && this->right == NULL;
        }

        bool hasOnlyLeft() {
            return this->left != NULL && this->right == NULL;
        }

        bool hasOnlyRight() {
            return this->left == NULL && this->right != NULL;
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
            this->removeNode(&this->root, murderName);
        }

        vector<Murder*> getMurders() {
            vector<Murder*> result;
            this->getMurderNode(this->root, &result);
            return result;
        }

    private:
        void insertNode(Node** node, string murderName) {
            if (*node == NULL) {
                *node = new Node(murderName);
                (*node)->value->killed++;
            } else if (murderName > (*node)->value->name) {
                this->insertNode(&(*node)->right, murderName);
            } else {
                this->insertNode(&(*node)->left, murderName);
            }
        } 

        void removeNode(Node** node, string target) {
            if (*node == NULL) return;

            if ((*node)->value->name == target) {
                if ((*node)->hasNoneChildren()) {
                    *node = NULL;
                    free(*node);
                } else if ((*node)->hasOnlyLeft()) {
                    Node* hold = (*node)->left;
                    *node = (*node)->left;
                    hold = NULL;
                    free(hold);
                } else if ((*node)->hasOnlyRight()) {
                    Node* hold = (*node)->right;
                    *node = (*node)->right;
                    hold = NULL;
                    free(hold);
                } else {
                    Node** greatest = this->findGreatest(&(*node)->left);
                    (*node)->value = (*greatest)->value;
                    if ((*greatest)->hasNoneChildren()) {
                        (*greatest) = NULL;
                        free(*greatest);
                    } else {
                        Node* hold = (*greatest)->left;
                        (*greatest) = (*greatest)->left;
                        hold = NULL;
                        free(hold);
                    }
                }
            } else if (target > (*node)->value->name) {
                this->removeNode(&(*node)->right, target);
            } else {
                this->removeNode(&(*node)->left, target);
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

        void getMurderNode(Node* node, vector<Murder*>* result) {
            if (node == NULL) return;

            this->getMurderNode(node->left, result);
            result->push_back(node->value);
            this->getMurderNode(node->right, result);
        }

        Node** findGreatest(Node** node) {
            if ((*node)->right == NULL) return node;
            return this->findGreatest(&(*node)->right);
        }
};

int main() {

    char murderNameC[12], killedNameC[12];
    BSTree* hallOfMurders = new BSTree();
    vector<string> killedNames;
    while (scanf("%s %s", murderNameC, killedNameC) != EOF) {
        string murderName = murderNameC, killedName = killedNameC;    
        hallOfMurders->insert(murderName);        
        killedNames.push_back(killedName);
    }

    for (string name : killedNames) {
        hallOfMurders->remove(name);
    }

    printf("HALL OF MURDERERS\n");
    vector<Murder*> murders = hallOfMurders->getMurders();
    for (Murder* murder : murders) {
        printf("%s %d\n", murder->name.c_str(), murder->killed);
    }

    return 0;
}