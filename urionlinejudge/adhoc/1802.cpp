#include <stdio.h>
#include <stdlib.h>

#define MAX_BOOKS 11

enum BookTypes {
    PORTUGUESE = 0,
    MATH = 1,
    PHYSICS = 2,
    CHEMISTRY = 3,
    BIOLOGY = 4,
};

int cmp(const void *a, const void *b) {
    return *(int *)b - *(int *)a;
}

int main() {

    int portuguese_qty, math_qty, physics_qty, chemistry_qty, biology_qty;
    int books[6][MAX_BOOKS];

    scanf("%d", &portuguese_qty);
    for (int i = 0; i < portuguese_qty; i++) scanf("%d", &books[PORTUGUESE][i]);

    scanf("%d", &math_qty);
    for (int i = 0; i < math_qty; i++) scanf("%d", &books[MATH][i]);

    scanf("%d", &physics_qty);
    for (int i = 0; i < physics_qty; i++) scanf("%d", &books[PHYSICS][i]);

    scanf("%d", &chemistry_qty);
    for (int i = 0; i < chemistry_qty; i++) scanf("%d", &books[CHEMISTRY][i]);
    
    scanf("%d", &biology_qty);
    for (int i = 0; i < biology_qty; i++) scanf("%d", &books[BIOLOGY][i]);

    int sets[100005], set_index = 5;
    for (int portuguese_current = 0; portuguese_current < portuguese_qty; portuguese_current++) {
        for (int math_current = 0; math_current < math_qty; math_current++) {
            for (int physics_current = 0; physics_current < physics_qty; physics_current++) {
                for (int chemistry_current = 0; chemistry_current < chemistry_qty; chemistry_current++) {
                    for (int biology_current = 0; biology_current < biology_qty; biology_current++) {
                        int portuguese = books[PORTUGUESE][portuguese_current];
                        int math = books[MATH][math_current];
                        int physics = books[PHYSICS][physics_current];
                        int chemistry = books[CHEMISTRY][chemistry_current];
                        int biology = books[BIOLOGY][biology_current];
                        sets[set_index] = (portuguese + math + physics + chemistry + biology);
                        set_index++;
                    }
                }
            }
        }
    }

    qsort(sets, set_index, sizeof(int), cmp);

    int k; scanf("%d", &k);
    int answer = 0;
    for (int i = 0; i < k; i++) {
        answer += sets[i];
    }

    printf("%d\n", answer);
    return 0;
}