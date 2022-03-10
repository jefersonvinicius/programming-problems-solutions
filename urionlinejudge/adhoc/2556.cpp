#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return *(int *) a - *(int *)b;
}

int main() {
    int n; 
    while (scanf("%d", &n) != EOF) {
        int times[n];
        for (int i = 0; i < n; i++) {
            int x; scanf("%d", &times[i]);
        }
        qsort(times, n, sizeof(int), cmp);
        printf("%d %d\n", n/2, times[n/2] - times[(n/2) - 1]);
    }
    return 0;
}