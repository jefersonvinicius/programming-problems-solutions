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

void debugNode(Node* node) {
    printf("(%p) %d -> (%p) %d -> (%p) %d\n", node->prev, (node->prev != NULL) ? node->prev->enemyId : -666, node, node->enemyId, node->next, (node->next != NULL) ? node->next->enemyId : -666);
}

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

        void debugEnemiesReferences() {
            for (auto it = this->enemiesReferences.cbegin(); it != this->enemiesReferences.cend(); it++) {
                printf("[%d] -> (%p) %d\n", it->first, it->second, it->second->enemyId);
            }
        }

        void debug() {
            if (this->head == NULL) {
                printf("Empty List\n");
                return;
            }

            printf("Next Order:\n");
            Node* node = this->head;
            while (node->next != NULL) {
                printf("%d -> ", node->enemyId);
                node = node->next;
            }
            printf("%d\n", node->enemyId);
            
            printf("Prev Order:\n");
            while (node != NULL) {
                if (node->prev == NULL) {
                    printf("%d\n", node->enemyId);
                } else {
                    printf("%d -> ", node->enemyId);
                }
                node = node->prev;
            }
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
    LinkedList list;    
    assert(list.head == NULL);

    list.addAtEnd(new Node(1));    
    assert(list.head->enemyId == 1);
    assert(list.head->next == NULL);
    assert(list.head->prev == NULL);

    list.addAtEnd(new Node(2));
    assert(list.head->next->enemyId == 2);
    assert(list.head->next->next == NULL);
    assert(list.head->next->prev->enemyId == 1);
    
    list.addAtEnd(new Node(3));
    
    assert(list.head->next->next->enemyId == 3);
    assert(list.head->next->next->next == NULL);
    assert(list.head->next->next->prev->enemyId == 2);
    assert(list.head->next->next->prev->prev->enemyId == 1);
    assert(list.head->next->next->prev->prev->prev == NULL);

    
    list.insertAfter(2, new Node(4));
    assert(list.head->next->enemyId == 2);
    assert(list.head->next->next->enemyId == 4);
    assert(list.head->next->next->next->enemyId == 3);
    assert(list.head->next->next->next->next == NULL);
    assert(list.head->next->next->next->prev->enemyId == 4);
    assert(list.head->next->next->next->prev->prev->enemyId == 2);

    list.insertAfter(1, new Node(5));
    assert(list.head->enemyId == 1);
    assert(list.head->next->enemyId == 5);
    assert(list.head->next->next->enemyId == 2);
    assert(list.head->next->next->next->enemyId == 4);
    assert(list.head->next->next->next->next->enemyId == 3);
    assert(list.head->next->next->next->next->next == NULL);
    assert(list.head->next->next->next->next->prev->enemyId == 4);
    assert(list.head->next->next->next->next->prev->prev->enemyId == 2);
    assert(list.head->next->next->next->next->prev->prev->prev->enemyId == 5);
    assert(list.head->next->next->next->next->prev->prev->prev->prev->enemyId == 1);

    assert(list.amountBetweenNodes(1, 4) == 2);
    assert(list.amountBetweenNodes(3, 5) == 2);
    assert(list.amountBetweenNodes(1, 5) == 0);
    assert(list.amountBetweenNodes(4, 2) == 0);
    assert(list.amountBetweenNodes(1, 3) == 3);

    list.remove(1);
    assert(list.head->enemyId == 5);
    assert(list.head->next->enemyId == 2);
    assert(list.head->next->next->enemyId == 4);
    assert(list.head->next->next->next->enemyId == 3);
    assert(list.head->next->next->next->prev->enemyId == 4);
    assert(list.head->next->next->next->prev->prev->enemyId == 2);
    assert(list.head->next->next->next->prev->prev->prev->enemyId == 5);
    assert(list.enemiesReferences[1] == NULL);

    list.remove(3);
    assert(list.head->enemyId == 5);
    assert(list.head->next->enemyId == 2);
    assert(list.head->next->next->enemyId == 4);
    assert(list.head->next->next->next == NULL);
    assert(list.head->next->next->prev->enemyId == 2);
    assert(list.head->next->next->prev->prev->enemyId == 5);
    assert(list.enemiesReferences[3] == NULL);

    list.remove(2);
    assert(list.head->enemyId == 5);
    assert(list.head->next->enemyId == 4);
    assert(list.head->next->next == NULL);
    assert(list.head->next->prev->enemyId == 5);
    assert(list.head->next->prev->prev == NULL);
    assert(list.enemiesReferences[2] == NULL);
    
    list.remove(4);
    assert(list.head->enemyId == 5);
    assert(list.head->next == NULL);
    assert(list.head->prev == NULL);
    assert(list.enemiesReferences[4] == NULL);

    // LinkedList enemies;
    // int n; scanf("%d", &n);
    // while (n--) {
    //     int x; scanf("%d", &x);
    //     enemies.add(new Node(x));
    // }

    // int q; scanf("%d\n", &q);
    // string line;
    // while (q--) {
    //     getline(cin, line);

    //     vector<string> input = split(line);
    //     char op = line[0];
    //     if (op == 'I') {
    //         int p = atoi(input[1].c_str());
    //         int e = atoi(input[2].c_str());
    //         enemies.insertAfter(e, new Node(p));
    //     } else if (op == 'R') {
    //         int e = atoi(input[1].c_str());
    //         enemies.remove(e);
    //     } else if (op == 'Q') {
    //         int a = atoi(input[1].c_str());
    //         int b = atoi(input[2].c_str());
    //         int r = enemies.amountBetweenNodes(a, b);
    //         printf("%d\n", r);
    //     } 
    // } 

    return 0;
}