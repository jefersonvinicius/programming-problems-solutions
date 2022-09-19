#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAME_SIZE 25

int cmp(const void *a, const void *b) {
    const char* a_value = (const char*) a;
    const char* b_value = (const char*) b;
    return strcmp(a_value, b_value);
}

int main() {

    int n; scanf("%d", &n);
    char b, name[NAME_SIZE];     

    char names[n + 1][NAME_SIZE];
    int name_index = 0, bad_behavior = 0, god_behavior = 0;
    while (n--) {
        scanf(" %c %s\n", &b, name);

        if (b == '-') bad_behavior++;
        else god_behavior++;
        
        strcpy(names[name_index], name);
        name_index++;
    }

    qsort(names, name_index, sizeof(char) * NAME_SIZE, cmp);

    for (int i = 0; i < name_index; i++) {
        printf("%s\n", names[i]);
    }
    printf("Se comportaram: %d | Nao se comportaram: %d\n", god_behavior, bad_behavior);

    return 0;
}