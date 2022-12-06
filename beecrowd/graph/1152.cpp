#include "stdio.h"
#include "assert.h"

class Street {
    public:
        int meters;
        bool illuminated;

        Street(int meters) {
            this->meters = meters;
        }
};

void tests() {
    { // street creation
        Street* street = new Street(10);
        assert(street->meters == 10);
        assert(street->illuminated == false);
    }
}

int main() {
    #ifdef TESTING
        printf(">>> TESTING <<<\n");
        tests();
        printf("OK.\n\n");
        return 0;
    #endif

    return 0;
}