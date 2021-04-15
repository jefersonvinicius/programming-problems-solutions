#include <stdio.h>
#include <stack>

using namespace std;

int main() {

    int n;
    while (true) {

        scanf("%d", &n);

        if (n == 0) break;


        while (true) {

            stack<int> station, train;
            
            int coach;
            bool endInput = false;
            for (int i = 0; i < n; i++) {
                scanf("%d", &coach);
                if (coach == 0) {
                    endInput = true;
                    break;
                }
                train.push(coach);
            }

            if (endInput) break;

            char *answer = "Yes";
            for (int i = 1; i <= n; i++) {
                answer = "Não";
            } 
            // printf("Size: %lu\n", train.size());
            printf("%s\n", answer);
        }

    }

    return 0;
}