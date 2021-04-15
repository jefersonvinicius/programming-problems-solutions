#include <stdio.h>
#include <algorithm>

using namespace std;

int calculateMDC(int a, int b) {
    int rest;
    while (true) {
        rest = a%b;
        if (rest == 0) break;

        a = b;
        b = rest;
    }
    return b;
}

int main() {

    int n, richardCards, vicentCards;

    scanf("%d", &n);

    while (n--) {
        scanf("%d%d", &richardCards, &vicentCards);
        printf("%d\n", calculateMDC(richardCards, vicentCards));
    }

    return 0;
}