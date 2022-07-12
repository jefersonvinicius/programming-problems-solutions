#include <assert.h>
#include <stdio.h>
#include <string.h>

#define MAX_BUGGIES 10005

class BITree {

    private:
        int size = 0;
        int raw[MAX_BUGGIES];
        int indexed[MAX_BUGGIES];

    public:
        BITree() {
            memset(this->raw, 0, MAX_BUGGIES);
            memset(this->indexed, 0, MAX_BUGGIES);
            this->size = 1;
        }

        void insert(int value) {
            int index = this->size;
            this->raw[index] = value;
            while (index > 0) {
                printf("%d\n", index);
                this->indexed[index] += this->raw[index];
                index -= index & (-index);
            }
            this->size++;
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
    BITree* tree = new BITree();
    tree->insert(1);
    tree->insert(2);
    tree->insert(3);
    tree->print();
    // printf("oi\n");

    return 0;
}