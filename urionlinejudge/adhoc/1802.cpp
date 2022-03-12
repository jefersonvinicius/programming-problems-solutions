#include <stdio.h>
#include <stdlib.h>

#define MAX_BOOKS 11

int portuguese[MAX_BOOKS], math[MAX_BOOKS], physics[MAX_BOOKS], chemistry[MAX_BOOKS], biology[MAX_BOOKS];

int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int first_is_bigger(int first, int a, int b, int c, int d) {
    return first >= a && first >= b && first >= c && first >= d;
}

int sd(int index) {
    if (index == 0) return index;
    return index - 1;
}

void print_array(int *array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {

    int portuguese_qty, math_qty, physics_qty, chemistry_qty, biology_qty;
    
    scanf("%d", &portuguese_qty);
    for (int i = 0; i < portuguese_qty; i++) scanf("%d", &portuguese[i]);

    scanf("%d", &math_qty);
    for (int i = 0; i < math_qty; i++) scanf("%d", &math[i]);

    scanf("%d", &physics_qty);
    for (int i = 0; i < physics_qty; i++) scanf("%d", &physics[i]);

    scanf("%d", &chemistry_qty);
    for (int i = 0; i < chemistry_qty; i++) scanf("%d", &chemistry[i]);
    
    scanf("%d", &biology_qty);
    for (int i = 0; i < biology_qty; i++) scanf("%d", &biology[i]);

    int portuguese_current = portuguese_qty - 1, 
        math_current = math_qty - 1, 
        physics_current = physics_qty - 1, 
        chemistry_current = chemistry_qty - 1, 
        biology_current = biology_qty - 1;
    int answer = 0;

    qsort(portuguese, portuguese_qty, sizeof(int), cmp);
    qsort(math, math_qty, sizeof(int), cmp);
    qsort(physics, physics_qty, sizeof(int), cmp);
    qsort(chemistry, chemistry_qty, sizeof(int), cmp);
    qsort(biology, biology_qty, sizeof(int), cmp);

    print_array(portuguese, portuguese_qty);
    print_array(math, math_qty);
    print_array(physics, physics_qty);
    print_array(chemistry, chemistry_qty);
    print_array(biology, biology_qty);

    int k; scanf("%d", &k);
    for (int i = 0; i < k; i++) {

        int portuguese_v = portuguese[portuguese_current];
        int math_v = math[math_current];
        int physics_v = physics[physics_current];
        int chemistry_v = chemistry[chemistry_current];
        int biology_v = biology[biology_current];

        answer += (
            portuguese_v +
            math_v + 
            physics_v + 
            chemistry_v +
            biology_v
        );

        if (portuguese_current > 0 && first_is_bigger(portuguese[portuguese_current - 1], math_v, physics_v, chemistry_v, biology_v)) {
            printf("Portuguese\n");
            portuguese_current--;
        } else if (math_current > 0 && first_is_bigger(math[math_current - 1], portuguese_v, physics_v, chemistry_v, biology_v)) {
            printf("Math\n");
            math_current--;
        } else if (physics_current > 0 && first_is_bigger(physics[physics_current - 1], portuguese_v, math_v, chemistry_v, biology_v)) {
            printf("Physics\n");
            physics_current--;
        } else if (chemistry_current > 0 && first_is_bigger(chemistry[chemistry_current - 1], portuguese_v, math_v, physics_v, biology_v)) {
            printf("Chemistry\n");
            chemistry_current--;
        } else if (biology_current > 0 && first_is_bigger(biology[biology_current - 1], portuguese_v, math_v, physics_v, chemistry_v)) {
            printf("Biology\n");
            biology_current--;
        }

    }

    printf("%d\n", answer);

    return 0;
}