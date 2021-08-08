#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <string>
#include <iostream>

using namespace std;

const int WEST = '1';
const int NORTH = '3';
const int SOUTH = '2';
const int EAST = '4';

int updateCurrentSide(int currentSide) {
    if (currentSide == WEST) return NORTH;
    if (currentSide == NORTH) return SOUTH;
    if (currentSide == SOUTH) return EAST;
    return WEST;
}

bool isFirst = true;
void printFront(queue<string> q) {
    if (isFirst) {
        printf("%s", q.front().c_str());
        isFirst = false;
    } else {
        printf(" %s", q.front().c_str());
    }
}

queue<string> westQueue;
queue<string> northQueue;
queue<string> southQueue;
queue<string> eastQueue;
int currentSide;

queue<string>* getCurrentQueue() {
    if (currentSide == WEST) return &westQueue;
    if (currentSide == NORTH) return &northQueue;
    if (currentSide == SOUTH) return &southQueue;
    return &eastQueue;
}

int main() {

    string input;

    int totalPlanes = 0;
    while (true) {
        getline(cin, input);

        if (input == "0") break;

        if (input[0] == '-') {
            currentSide = input[1];
            continue; 
        } 

        if (currentSide == WEST) westQueue.push(input);
        if (currentSide == NORTH) northQueue.push(input);
        if (currentSide == EAST) eastQueue.push(input);
        if (currentSide == SOUTH) southQueue.push(input);
        totalPlanes++;
    }

    currentSide = WEST;
    while (true) {
        queue<string> *current = getCurrentQueue();
        if (westQueue.empty() && northQueue.empty() && southQueue.empty() && eastQueue.empty()) break;

        if (!current->empty()) {
            printFront(*current);
            current->pop();
        }
        currentSide = updateCurrentSide(currentSide);
    }
    printf("\n");

    return 0;
}