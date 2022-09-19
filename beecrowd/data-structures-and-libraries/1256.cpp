#include <stdio.h>
#include <map>
#include <vector>

using namespace std;

int main() {

    int t;
    scanf("%d", &t);

    while (t--) {
        int tableSize, amountKeys;
        scanf("%d%d", &tableSize, &amountKeys);

        map<int, vector<int> > hashTable;

        for (int i = 0; i < tableSize; i++) {
            hashTable[i] = vector<int>();
        }

        for (int i = 0; i < amountKeys; i++) {
            int x; scanf("%d", &x);
            int hash = x % tableSize;
            hashTable[hash].push_back(x);
        }

        for (int i = 0; i < tableSize; i++) {
            printf("%d ->", i);
            for (int j = 0; j < hashTable[i].size(); j++) {
                printf(" %d ->", hashTable[i][j]);
            }    
            printf(" \\\n");
        }

        if (t > 0) {
            printf("\n");
        }
    }

    return 0;
}