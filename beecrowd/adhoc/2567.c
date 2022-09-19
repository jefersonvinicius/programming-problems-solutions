#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return *(int *)b - *(int *)a ;
}

int main() {

    int n; 
    while (scanf("%d", &n) != EOF) {
        int virus[n];
        for (int i = 0; i < n; i++) {
            int x; scanf("%d", &x);
            virus[i] = x;
        }

        qsort(virus, n, sizeof(int), cmp);

        int answer = 0;
        for (int i = 0; i < n / 2; i++) {
            answer += (virus[i] - virus[n-i-1]);
        }

        printf("%d\n", answer);
    }

    return 0;
}