#include <stdio.h>
#include <math.h>

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n; scanf("%d", &n);
        printf("%lld\n", (long long unsigned) pow(2, n) - 1);
    }
}