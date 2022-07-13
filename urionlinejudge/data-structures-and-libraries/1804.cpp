#include <assert.h>
#include <stdio.h>
#include <string.h>

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
            int n = this->size;
            int index = at + 1;
            this->raw[index] = 0;
            int valueBeingRemoved = this->raw[at];
            while (index <= n) {
                this->indexed[index] -= valueBeingRemoved;
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
    while (n--) {
        printf("n: %d\n", n);
        int x; scanf("%d", &x);
        tree->insert(x);
    }

    char s[100];
    int operation = 0, value = 0;
    scanf(" %[^\n]", s);
    printf("S: %s\n", s);
    // while (scanf("%d %d", &operation, &value) != EOF) {
        // if (operation == 'a')
        printf(">> %d %d\n", operation, value);
        // for (int i = 0; i < 100000000; i++) {}
            // tree->remove(value - 1);
        // else
            // printf("%d\n", tree->sum(value - 1));
    // }

    return 0;
}