#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

#define MAX_CELLS 1005

bool shouldStopIteration = false;

string iterateOverCells(string cells) {
    string cellsAfterIteration = "";
    int amountOfAlive = 0, amountOfDead = 0;
    for (int i = 0; i < cells.size(); i++) {
        if (i == 0 && cells[i] == '0' && cells[i + 1] == '1') {
            cellsAfterIteration += '1';
            amountOfAlive++;
        } else  if (i == cells.size() - 1 && cells[i] == '0' && cells[i - 1] == '1') {
            cellsAfterIteration += '1';
            amountOfAlive++;
        } else if (cells[i] == '0' && (cells[i + 1] == '1' && cells[i - 1] == '0') || (cells[i + 1] == '0' && cells[i - 1] == '1') ) {
            cellsAfterIteration += '1';
            amountOfAlive++;
        } else {
            cellsAfterIteration += cells[i];
            if (cells[i] == '0') amountOfDead++;
            else amountOfAlive++;
        }
    }

    if (amountOfAlive == cells.size() || amountOfDead == cells.size()) {
        shouldStopIteration = true;
    }  

    return cellsAfterIteration;
}

int main() {

    char cells[MAX_CELLS] = "";

    int t; scanf("%d", &t);

    while (t--) {
        int numberOfCells, numberOfIterations;
        scanf("%d %d", &numberOfCells, &numberOfIterations);
        scanf(" %[^\n]", cells);
        string strCells = cells;
        shouldStopIteration = false;
        for (int i = 0; i < numberOfIterations; i++) {
            strCells = iterateOverCells(strCells);
            if (shouldStopIteration) break;
        }

        printf("%s\n", strCells.c_str());
    }

    return 0;
}