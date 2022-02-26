#include <stdio.h>

int main() {

    int a[15];
    for (int i = 0; i <= 9; i++) {
        int x; scanf("%d", &x);
        a[i] = x;
    }

    int index = 0;
    for (int i = 0; i < 3; i++) {
        index = a[index];
    }

    printf("%d\n", index);

    return 0;
}