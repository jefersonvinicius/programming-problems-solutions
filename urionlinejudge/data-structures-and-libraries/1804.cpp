#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

#define MAX_BUGGIES 10005

class BITree {

    private:
        int size;
        int raw[MAX_BUGGIES];
        int indexed[MAX_BUGGIES];

    public:
        BITree() {
            memset(this->raw, 0, MAX_BUGGIES);
            memset(this->indexed, 0, MAX_BUGGIES);
            this->size = 1;
        }

        void insert(int value) {
            int initialIndex = this->size;
            this->raw[initialIndex] = value;
            this->indexed[initialIndex] = value;
            int finalIndex = initialIndex - (initialIndex & (-initialIndex));
            for (int i = initialIndex - 1; i > finalIndex; i--) {
                this->indexed[initialIndex] += this->raw[i];
            }
            this->size++;
        }

        void remove(int at) {
            int index = at + 1;
            int valueBeingRemoved = this->raw[index];
            this->raw[index] = 0;
            this->indexed[index] = 0;
            while (index <= this->size) {
                this->indexed[index] = max(indexed[index] - valueBeingRemoved, 0);
                index += index & (-index);
            }
        }

        int sum(int untilIndex) {
            int result = 0;
            int index = untilIndex + 1;
            while (index > 0) {
                result += this->indexed[index];
                index -= index & (-index);
            }
            return result;
        }

        void print() {
            printf("BITree %p\n", this);
            printf("Raw: ");
            for (int i = 0; i < this->size; i++) printf("%d ", this->raw[i]);
            printf("\nIndexed: ");
            for (int i = 0; i < this->size; i++) printf("%d ", this->indexed[i]);
            printf("\n");
        }
};

int main() {
    
    int n; scanf("%d", &n);
    BITree* tree = new BITree();
    for (int i = 0; i < n; i++) {
        int x; scanf("%d", &x);
        tree->insert(x);
    }

    char operation[1];
    int value;
    while (scanf("%s %d", operation, &value) != EOF) {
        tree->print();
        if (strcmp(operation, "a") == 0)
            tree->remove(value - 1);
        else
            printf("%d\n", tree->sum(value - 2));
    }

    return 0;
}