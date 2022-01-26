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
        map<int, Node*> enemiesReferences;
        Node* lastAddedAtEnd;

    public:
        Node* head;

        LinkedList() {
            head = NULL;
            lastAddedAtEnd = NULL;
        }


        void addAtEnd(Node* node) {
            if (this->head == NULL) {
                this->head = node;
                this->lastAddedAtEnd = node;
                return;
            }

            node->prev = lastAddedAtEnd;
            node->next = NULL;
            lastAddedAtEnd->next = node;

            this->enemiesReferences.insert(make_pair(node->enemyId, node));
            this->lastAddedAtEnd = node;
        }

        void insertAfter(int prevEnemyId, Node* nodeToInsert) {
            Node* prevNode = this->enemiesReferences[prevEnemyId];
            nodeToInsert->next = prevNode->next;
            prevNode->next = nodeToInsert;

            this->enemiesReferences.insert(make_pair(nodeToInsert->enemyId, nodeToInsert));
        }

        int amountBetweenNodes(int enemyIdStart, int enemyIdEnd) {
            Node* node = this->enemiesReferences.find(enemyIdStart)->second->next;
            int count = 0;
            while (node->enemyId != enemyIdEnd) {
                count++;
                node = node->next;
            }
            return count;
        }

        void remove(int enemyId) {
            Node* nodeToRemove = this->enemiesReferences[enemyId];
            this->enemiesReferences.erase(enemyId);
            Node* node = this->head;
            while (node->next != nodeToRemove) {
                node = node->next;
            }

            node->next = nodeToRemove->next;
            free(nodeToRemove);
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
    

    printf("oi\n");
    LinkedList list;    
    assert(list.head == NULL);
    printf("oi2\n");

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
    list.debug();
    assert(list.head->next->enemyId == 2);
    assert(list.head->next->next->enemyId == 4);
    assert(list.head->next->next->next->enemyId == 3);
    assert(list.head->next->next->next->next == NULL);
    assert(list.head->next->next->next->prev->enemyId == 4);
    assert(list.head->next->next->next->prev->prev->enemyId == 3);

    printf("Oi8\n");

    // assert(list.amountBetweenNodes(1, 3) == 2);
    // list.addAtEnd(new Node(5));
    // assert(list.amountBetweenNodes(1, 5) == 3);

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