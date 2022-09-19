#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <assert.h>

using namespace std;

int smallest_index_of_with_max_swaps(vector<string> items, int start_at, int max_swaps) {
    string smallest = "";
    int index;
    for (int i = start_at; i < items.size(); i++) {
        if (i - start_at > max_swaps) break;
        
        if (smallest.empty() || items[i] < smallest) {
            smallest = items[i];
            index = i;
        }
    }
    return index;
}

vector<string> sorting(vector<string> names, int max_swaps) {
    vector<string> result = names;
    if (result.size() == 1) return result;

    int swaps = max_swaps;
    for (int i = 0; i < result.size() - 1 && swaps > 0; i++) {
        int smallest = smallest_index_of_with_max_swaps(result, i, swaps);

        for (int j = smallest; j > i; j--) {
            swap(result[j], result[j-1]);
        }

        swaps -= (smallest - i);
    }

    return result;
}

int main() {

    int n, k, instance = 1;
    while (1) {
        scanf("%d%d\n", &n, &k);
        if (n == 0 && k == 0) break;

        vector<string> names;
        char name_c[21];
        for (int i = 0; i < n; i++) {
            scanf("%s \n", name_c);
            names.push_back(name_c);
        }

        vector<string> answer = sorting(names, k);

        printf("Instancia %d\n", instance);
        for (int i = 0; i < answer.size(); i++) {
            printf("%s ", answer[i].c_str());
        }
        printf("\n\n");

        instance++;
    }


    return 0;
}