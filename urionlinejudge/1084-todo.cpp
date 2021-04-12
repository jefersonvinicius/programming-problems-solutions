#include <stdio.h>
#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

int main() {

    int n, erasing;
    string number;
    
    while (true) {
        scanf("%d%d\n", &n, &erasing);

        if (n == 0 && erasing == 0) break;

        stack<char> bigger;

        getline(cin, number);

        int numberSize = n - erasing;

        for (int i = 0; i < number.size(); i++) {
            char c = number[i];
            int rest = numberSize - i;
            if (bigger.size() > 0) {
                while (true) {
                    printf("top: %c - current: %c\n", bigger.top(), c);
                    if (c > bigger.top() && rest > numberSize) {
                        bigger.pop();
                        if (bigger.empty()) break;
                    } else {
                        break;
                    }
                }
                bigger.push(c);
            } else {
                bigger.push(c);
            }
        }

        char answer[1000000];
        int biggerSize = bigger.size();
        for (int i = 0; i < biggerSize; i++) {
            answer[biggerSize - i] = bigger.top();
            bigger.pop();
        }

        for (int i = 0; i < numberSize; i++) {
            printf("%c", answer[i]);
        }
        printf("\n");
        // printf("%.*s\n", numberSize, answer);
    }

    return 0;
}