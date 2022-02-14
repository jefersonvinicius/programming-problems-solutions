#include <stdio.h>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {

    int n, m; 
    while (scanf("%d %d", &n, &m) != EOF) {
        unordered_map<int, vector<int>> positions;

        for(int i = 0; i < n; i++) {
            int x; scanf("%d", &x);
            positions[x].push_back(i);
        } 

        for (int i = 0; i < m; i++) {
            int occurrence, nToFind; scanf("%d %d", &occurrence, &nToFind);
            int finalOccurrence = occurrence - 1;

            unordered_map<int, vector<int>>::const_iterator element = positions.find(nToFind);
            if (element == positions.end()) {
                printf("0\n");
                continue;
            }

            vector<int> occurrences = element->second;
            if (finalOccurrence >= occurrences.size()) {
                printf("0\n");
            } else {
                printf("%d\n", occurrences.at(finalOccurrence) + 1);
            }
        }
    }
    

    return 0;
}