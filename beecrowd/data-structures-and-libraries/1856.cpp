#include <stdio.h>
#include <assert.h>
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class Node {
    public:
        int enemyId;
        Node* next;
        Node* prev;

        Node(int enemyId) {
            this->enemyId = enemyId;
        }
};

class LinkedList {
    private:
        Node* lastAddedAtEnd;

    public:
        map<int, Node*> enemiesReferences;
        Node* head;

        LinkedList() {
            head = NULL;
            lastAddedAtEnd = NULL;
        }


        void addAtEnd(Node* node) {
            if (this->head == NULL) {
                this->head = node; 
            } else {
                node->prev = lastAddedAtEnd;
                node->next = NULL;
                lastAddedAtEnd->next = node;
            }


            this->enemiesReferences.insert(make_pair(node->enemyId, node));
            this->lastAddedAtEnd = node;
        }

        void insertAfter(int prevEnemyId, Node* nodeToInsert) {
            Node* prevNode = this->enemiesReferences[prevEnemyId];

            if (prevNode->next == NULL) {
                nodeToInsert->prev = prevNode;
                nodeToInsert->next = NULL;
                prevNode->next = nodeToInsert;
            } else {
                nodeToInsert->next = prevNode->next;
                prevNode->next->prev = nodeToInsert;
                prevNode->next = nodeToInsert;
                nodeToInsert->prev = prevNode;
            }

            this->enemiesReferences.insert(make_pair(nodeToInsert->enemyId, nodeToInsert));
        }

        int amountBetweenNodes(int enemyIdStart, int enemyIdEnd) {
            Node* node = this->enemiesReferences[enemyIdStart]->next;
            int count = 0, found = 0;
            while (node != NULL && node->enemyId != enemyIdEnd) {
                count++;
                node = node->next;
                if (node != NULL && node->enemyId == enemyIdEnd) found = 1;
            }
            
            if (found) return count;

            count = 0;
            node = this->enemiesReferences[enemyIdStart]->prev;
            while (node != NULL && node->enemyId != enemyIdEnd) {
                count++;
                node = node->prev;
            }

            return count;
        }

        void remove(int enemyId) {
            Node* nodeToRemove = this->enemiesReferences[enemyId];
            
            if (nodeToRemove->prev == NULL) { // is head
                this->head = nodeToRemove->next;
                this->head->prev = NULL;
            } else if (nodeToRemove->next == NULL) { // is end
                nodeToRemove->prev->next = NULL;
            } else { // is middle
                nodeToRemove->next->prev = nodeToRemove->prev;
                nodeToRemove->prev->next = nodeToRemove->next;
            }

            this->enemiesReferences.erase(enemyId);
            free(nodeToRemove);
        }
};

vector <string> split(string text, char separator = ' ') {
    string str = "";
    int textLength = text.size();
    vector<string> result;
    for (int i = 0; i < textLength; i++) {
        if (text[i] == separator) {
            result.push_back(str);
            str = "";
        } else {
            str += text[i];
        }
         
        if (i == textLength - 1) result.push_back(str);
    }
    return result;
}

int main() {
    LinkedList enemies;
    int n; scanf("%d", &n);
    while (n--) {
        int x; scanf("%d", &x);
        enemies.addAtEnd(new Node(x));
    }

    int q; scanf("%d\n", &q);
    string line;
    while (q--) {
        getline(cin, line);

        vector<string> input = split(line);
        char op = line[0];
        if (op == 'I') {
            int p = atoi(input[1].c_str());
            int e = atoi(input[2].c_str());
            enemies.insertAfter(e, new Node(p));
        } else if (op == 'R') {
            int e = atoi(input[1].c_str());
            enemies.remove(e);
        } else if (op == 'Q') {
            int a = atoi(input[1].c_str());
            int b = atoi(input[2].c_str());
            int r = enemies.amountBetweenNodes(a, b);
            printf("%d\n", r);
        } 
    } 

    return 0;
}