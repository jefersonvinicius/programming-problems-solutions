#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>

#define MAX_BOOKS 11

#define DEBUG 0

enum BookTypes {
    PORTUGUESE = 0,
    MATH = 1,
    PHYSICS = 2,
    CHEMISTRY = 3,
    BIOLOGY = 4,
    NONE = -1
};

int portuguese[MAX_BOOKS], math[MAX_BOOKS], physics[MAX_BOOKS], chemistry[MAX_BOOKS], biology[MAX_BOOKS];

int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

void log(const char *__restrict__ __format, ...) {
    if (DEBUG) {
        va_list arg; 
        va_start(arg, __format);
        vprintf(__format, arg);
        va_end(arg);
    }
}

int first_is_bigger(int first, int a, int b, int c, int d) {
    log("Comparing %d with %d, %d, %d, %d\n", first, a, b, c, d);
    return first >= a && first >= b && first >= c && first >= d;
}

int sd(int index) {
    if (index == 0) return index;
    return index - 1;
}

BookTypes next_book_type_bigger(int portuguese_v, int math_v, int physics_v, int chemistry_v, int biology_v) {
    if (first_is_bigger(portuguese_v, math_v, physics_v, chemistry_v, biology_v)) {
        log("Portuguese\n");
        return PORTUGUESE;
    } else if (first_is_bigger(math_v, portuguese_v, physics_v, chemistry_v, biology_v)) {
        log("Math\n");
        return MATH;
    } else if (first_is_bigger(physics_v, portuguese_v, math_v, chemistry_v, biology_v)) {
        log("Physics\n");
        return PHYSICS;
    } else if (first_is_bigger(chemistry_v, portuguese_v, math_v, physics_v, biology_v)) {
        log("Chemistry\n");
        return CHEMISTRY;
    } else {
        log("Biology\n");
        return BIOLOGY;
    }

    return NONE;
}



void print_array(int *array, int size) {
    for (int i = 0; i < size; i++) {
        log("%d ", array[i]);
    }
    log("\n");
}

BookTypes less_diff(int* books1, int* books2, int* selected_memo) {
    BookTypes lesser = NONE;
    int lesser_diff = INT_MAX;
    for (int i = 0; i <= BIOLOGY; i++) {
        if (selected_memo[i]) continue;
        int diff = books1[i] - books2[i];
        if (diff < lesser_diff) {
            lesser_diff = diff;
            lesser = (BookTypes) i;
        }
    }
    return lesser;
}

int main() {

    // int portuguese_qty, math_qty, physics_qty, chemistry_qty, biology_qty;
    
    // scanf("%d", &portuguese_qty);
    // for (int i = 0; i < portuguese_qty; i++) scanf("%d", &portuguese[i]);

    // scanf("%d", &math_qty);
    // for (int i = 0; i < math_qty; i++) scanf("%d", &math[i]);

    // scanf("%d", &physics_qty);
    // for (int i = 0; i < physics_qty; i++) scanf("%d", &physics[i]);

    // scanf("%d", &chemistry_qty);
    // for (int i = 0; i < chemistry_qty; i++) scanf("%d", &chemistry[i]);
    
    // scanf("%d", &biology_qty);
    // for (int i = 0; i < biology_qty; i++) scanf("%d", &biology[i]);

    // int portuguese_current = portuguese_qty - 1, 
    //     math_current = math_qty - 1, 
    //     physics_current = physics_qty - 1, 
    //     chemistry_current = chemistry_qty - 1, 
    //     biology_current = biology_qty - 1;

    // qsort(portuguese, portuguese_qty, sizeof(int), cmp);
    // qsort(math, math_qty, sizeof(int), cmp);
    // qsort(physics, physics_qty, sizeof(int), cmp);
    // qsort(chemistry, chemistry_qty, sizeof(int), cmp);
    // qsort(biology, biology_qty, sizeof(int), cmp);

    // print_array(portuguese, portuguese_qty);
    // print_array(math, math_qty);
    // print_array(physics, physics_qty);
    // print_array(chemistry, chemistry_qty);
    // print_array(biology, biology_qty);

    // int answer = 0;

    // int k; scanf("%d", &k);
    // for (int i = 1; i <= k; i++) {
    //     int already_selected_memo[] = {0, 0, 0, 0, 0};

    //     answer += portuguese[portuguese_current] + math[math_current] + physics[physics_current] + chemistry[chemistry_current] + biology[biology_current];

    //     for (int j = 0; j < 5; j++) {
    //         if (i == k) break;


    //         BookTypes next = next_book_type_bigger(
    //             !already_selected_memo[PORTUGUESE] ? portuguese[sd(portuguese_current)] : -1, 
    //             !already_selected_memo[MATH] ? math[sd(math_current)] : -1, 
    //             !already_selected_memo[PHYSICS] ? physics[sd(physics_current)] : -1, 
    //             !already_selected_memo[CHEMISTRY] ? chemistry[sd(chemistry_current)] : -1, 
    //             !already_selected_memo[BIOLOGY] ? biology[sd(biology_current)] : -1
    //         );

    //         if (next != NONE) {
    //             already_selected_memo[next] = 1;

    //             int portuguese_v = next == PORTUGUESE ? portuguese[sd(portuguese_current)] : portuguese[portuguese_current];
    //             int math_v = next == MATH ? math[sd(math_current)] : math[math_current];
    //             int physics_v = next == PHYSICS ? physics[sd(physics_current)] : physics[physics_current];
    //             int chemistry_v = next == CHEMISTRY ? chemistry[sd(chemistry_current)] : chemistry[chemistry_current];
    //             int biology_v = next == BIOLOGY ? biology[sd(biology_current)] : biology[biology_current];

    //             log("%d %d %d %d %d\n", portuguese_v, math_v, physics_v, chemistry_v, biology_v);

    //             answer += (
    //                 portuguese_v +
    //                 math_v + 
    //                 physics_v + 
    //                 chemistry_v +
    //                 biology_v
    //             );

    //             i++;
    //             log("\n");
    //         }
    //     }

    //     portuguese_current--;
    //     math_current--;
    //     physics_current--;
    //     chemistry_current--;
    //     biology_current--;
    // }

    // printf("%d\n", answer);

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

    int portuguese_current = portuguese_qty - 1, 
        math_current = math_qty - 1, 
        physics_current = physics_qty - 1, 
        chemistry_current = chemistry_qty - 1, 
        biology_current = biology_qty - 1;

    qsort(books[PORTUGUESE], portuguese_qty, sizeof(int), cmp);
    qsort(books[MATH], math_qty, sizeof(int), cmp);
    qsort(books[PHYSICS], physics_qty, sizeof(int), cmp);
    qsort(books[CHEMISTRY], chemistry_qty, sizeof(int), cmp);
    qsort(books[BIOLOGY], biology_qty, sizeof(int), cmp);

    print_array(books[PORTUGUESE], portuguese_qty);
    print_array(books[MATH], math_qty);
    print_array(books[PHYSICS], physics_qty);
    print_array(books[CHEMISTRY], chemistry_qty);
    print_array(books[BIOLOGY], biology_qty);


    int answer = 0;
    answer += books[PORTUGUESE][portuguese_current] + books[MATH][math_current] + books[PHYSICS][physics_current] + books[CHEMISTRY][chemistry_current] + books[BIOLOGY][biology_current];

    int k; scanf("%d", &k);
    int i = 1, first_lesser = NONE;
    while (i < k) {
        int already_selected_memo[] = {0, 0, 0, 0, 0};

        for (int j = 0; j < 4; j++) {

            if (i == k) break;

            int current[] = {books[PORTUGUESE][portuguese_current], books[MATH][math_current], books[PHYSICS][physics_current], books[CHEMISTRY][chemistry_current], books[BIOLOGY][biology_current]};
            int next[] = {books[PORTUGUESE][portuguese_current - 1], books[MATH][math_current - 1], books[PHYSICS][physics_current - 1], books[CHEMISTRY][chemistry_current - 1], books[BIOLOGY][biology_current - 1]};
            BookTypes lesser = less_diff(current, next, already_selected_memo);
            log("lesser: %d\n", lesser);
            
            if (lesser != NONE) {
                if (first_lesser == NONE) first_lesser = lesser;
                already_selected_memo[lesser] = 1;

                int portuguese_v = lesser == PORTUGUESE ? books[PORTUGUESE][sd(portuguese_current)] : books[PORTUGUESE][portuguese_current];
                int math_v = lesser == MATH ? books[MATH][sd(math_current)] : books[MATH][math_current];
                int physics_v = lesser == PHYSICS ? books[PHYSICS][sd(physics_current)] : books[PHYSICS][physics_current];
                int chemistry_v = lesser == CHEMISTRY ? books[CHEMISTRY][sd(chemistry_current)] : books[CHEMISTRY][chemistry_current];
                int biology_v = lesser == BIOLOGY ? books[BIOLOGY][sd(biology_current)] : books[BIOLOGY][biology_current];

                log("%d %d %d %d %d\n", portuguese_v, math_v, physics_v, chemistry_v, biology_v);
                
                answer += (
                    portuguese_v +
                    math_v + 
                    physics_v + 
                    chemistry_v +
                    biology_v
                );

                i++;
                log("\n");
            }
        }

        log("FIRST LESSER: %d\n", first_lesser);

        if (first_lesser == PORTUGUESE) portuguese_current--;
        if (first_lesser == MATH) math_current--;
        if (first_lesser == PHYSICS) physics_current--;
        if (first_lesser == CHEMISTRY) chemistry_current--;
        if (first_lesser == BIOLOGY) biology_current--;
    }

    printf("%d\n", answer);

    // for (int i = 1; i <= k; i++) {
    //     int already_selected_memo[] = {0, 0, 0, 0, 0};

    //     answer += portuguese[portuguese_current] + math[math_current] + physics[physics_current] + chemistry[chemistry_current] + biology[biology_current];

    //     for (int j = 0; j < 5; j++) {
    //         if (i == k) break;


    //         BookTypes next = next_book_type_bigger(
    //             !already_selected_memo[PORTUGUESE] ? portuguese[sd(portuguese_current)] : -1, 
    //             !already_selected_memo[MATH] ? math[sd(math_current)] : -1, 
    //             !already_selected_memo[PHYSICS] ? physics[sd(physics_current)] : -1, 
    //             !already_selected_memo[CHEMISTRY] ? chemistry[sd(chemistry_current)] : -1, 
    //             !already_selected_memo[BIOLOGY] ? biology[sd(biology_current)] : -1
    //         );

    //         if (next != NONE) {
    //             already_selected_memo[next] = 1;

    //             int portuguese_v = next == PORTUGUESE ? portuguese[sd(portuguese_current)] : portuguese[portuguese_current];
    //             int math_v = next == MATH ? math[sd(math_current)] : math[math_current];
    //             int physics_v = next == PHYSICS ? physics[sd(physics_current)] : physics[physics_current];
    //             int chemistry_v = next == CHEMISTRY ? chemistry[sd(chemistry_current)] : chemistry[chemistry_current];
    //             int biology_v = next == BIOLOGY ? biology[sd(biology_current)] : biology[biology_current];

    //             log("%d %d %d %d %d\n", portuguese_v, math_v, physics_v, chemistry_v, biology_v);

    //             answer += (
    //                 portuguese_v +
    //                 math_v + 
    //                 physics_v + 
    //                 chemistry_v +
    //                 biology_v
    //             );

    //             i++;
    //             log("\n");
    //         }
    //     }

    //     portuguese_current--;
    //     math_current--;
    //     physics_current--;
    //     chemistry_current--;
    //     biology_current--;
    // }

    // printf("%d\n", answer);

    return 0;
}