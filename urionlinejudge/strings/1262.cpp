#include <stdio.h>
#include <cstring>

int calculateNumberOfReadOperationsInClockCycle(int numberOfReadConsecutive, int operationsSimultaneously) {
    if (numberOfReadConsecutive <= operationsSimultaneously) return 1;
    
    int totalOperation = numberOfReadConsecutive/operationsSimultaneously;
    if (numberOfReadConsecutive%operationsSimultaneously != 0) {
        totalOperation++;
    }

    return totalOperation;
}

int main() {

    char trace[51];
    int operationsSimultaneously;
    while (scanf("%s", trace) != EOF) {
        scanf("%d", &operationsSimultaneously);

        int answer = 0;
        int numberOfReadConsecutive = 0;
        for (int i = 0; i < strlen(trace); i++) {
            if (trace[i] == 'W') {
                answer++;
                if (numberOfReadConsecutive != 0) {
                    answer += calculateNumberOfReadOperationsInClockCycle(numberOfReadConsecutive, operationsSimultaneously);
                    numberOfReadConsecutive = 0;
                }
            } else {
                numberOfReadConsecutive++;
            }

            if (i == strlen(trace) - 1 && numberOfReadConsecutive != 0) {
                answer += calculateNumberOfReadOperationsInClockCycle(numberOfReadConsecutive, operationsSimultaneously);
            }
        }

        printf("%d\n", answer);
    }

    return 0;
}