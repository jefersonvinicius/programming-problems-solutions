#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PLAYERS 1000000

class BITree {
    public:
        int raw[MAX_PLAYERS];
        int indexed[MAX_PLAYERS];
        int size, playerAmount;

        BITree(int playerAmount) {
            memset(this->indexed, 0, MAX_PLAYERS);
            memset(this->raw, 0, MAX_PLAYERS);
            this->size = 1;
            this->playerAmount = playerAmount;
        }

        void insert(int value) {
            this->raw[this->size] = value;
            int index = this->size, result = value;
            for (int i = index; i > 0; i -= i & (-i)) {
                result += this->indexed[i];
            }
            this->indexed[this->size] = result;
            this->size++;
        }

        void remove(int index) {
            
        }
};

void print_array(int* array, size_t size, int start = 1) {
    for (int i = start; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {


    int n;
     
    while (scanf("%d", &n) != EOF) {
        int players[n + 1], playersIndexes[n + 1];
        
        BITree* tree = new BITree(n + 1);

        for (int i = 1; i <= n; i++) {
            int x; scanf("%d", &x);
            players[i] = x;
            playersIndexes[x] = i;
        }

        for (int i = 0; i < n; i++)
            tree->insert(i);

        int memo[n + 1];
        for (int i = 1; i <= n; i++) {
            int player = players[i];
            int playerIndex = playersIndexes[player];
            memo[player] = n - playerIndex;
        }

        printf("raw: ");
        print_array(tree->raw, tree->playerAmount);
        printf("indexed: ");
        print_array(tree->indexed, tree->playerAmount);
        // printf("memo: ");
        // print_array(memo, n+1);


        int result = 0;
        for (int player = 1; player <= n; player++) {
            result += memo[player];
            int playerIndex = playersIndexes[player];
            for (int i = playerIndex - 1; i >= 0; i--) {
                int playerToUpdate = playersIndexes[i];
                memo[playerToUpdate]--;
            }
        }
        printf("%d\n", result);
    }

    return 0;
}