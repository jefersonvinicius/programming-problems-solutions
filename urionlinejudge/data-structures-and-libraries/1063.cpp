#include <stdio.h>
#include <stack>
#include <string>

using namespace std;

int main() {

    int n;
    while (true) {

        scanf("%d", &n);

        if (n == 0) break;

        char wagon;
        stack<char> trainArriving;
        char desiredOrder[26];

        char tmp[26];
        for (int i = 0; i < n; i++) {
            scanf(" %c", &wagon);
            tmp[i] = wagon; 
        }

        for (int i = n - 1; i >= 0; i--) {
            trainArriving.push(tmp[i]);
        }
        

        for (int i = 0; i < n; i++) {
            scanf(" %c", &wagon);
            desiredOrder[i] = wagon;
        }

        string answer = "";
        int currentWagonIndex = 0;
        stack<char> station;

        while (true) {
            char currentWagonNecessary = desiredOrder[currentWagonIndex];

            if (station.empty() && trainArriving.empty()) break;

            if (!station.empty() && station.top() != currentWagonNecessary && trainArriving.empty()) {
                answer += " Impossible";
                break;
            }

            if (station.size() > 0 && station.top() == currentWagonNecessary) {
                answer += 'R';
                station.pop();
                currentWagonIndex++;
            } else {
                station.push(trainArriving.top());
                trainArriving.pop();
                answer += 'I';    

            }
        } 

        printf("%s\n", answer.c_str());
    }

    return 0;
}