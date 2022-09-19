#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

using namespace std;

#define MAX_PLAYERS 1000000
#define ull unsigned long long

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
            int startAt = this->size - (this->size & (-this->size)); 
            int result = 0;
            for (int i = startAt; i < this->size; i++) {
                result += this->raw[i];
            }
            this->indexed[this->size] = result;
            this->size++;
        }

        void remove(int index) {
            int value = this->raw[index];
            int correctIndex = this->playerAmount - index;
            for (int i = correctIndex; i <= this->size; i += i & (-i)) {
                this->indexed[i] -= value;
            }
            this->raw[index] = 0;
        }

        ull sum(int start) {
            ull result = 0;
            int correctIndex = this->playerAmount - start;
            for (int i = correctIndex; i > 0; i -= i & (-i)) {
                result += this->indexed[i];
            }
            return result;
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
        int playersIndexes[n + 1];
        
        BITree* tree = new BITree(n + 1);

        for (int i = 1; i <= n; i++) {
            int x; scanf("%d", &x);
            playersIndexes[x] = i;
        }

        for (int i = 0; i < n; i++)
            tree->insert(1);

        ull result = 0;
        for (int player = 1; player <= n; player++) {
            int index = playersIndexes[player];
            result += tree->sum(index);
            tree->remove(index);
        }
        printf("%lld\n", result);

        free(tree);
    }

    return 0;
}