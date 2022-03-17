#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

vector<string> lesser_lexicographic_list(vector<string> list1, vector<string> list2) {
    for (int i = 0; i < list1.size(); i++) {
        if (list1[i] < list2[i]) return list1;
        else if (list2[i] < list1[i]) return list2;
    }
    return list1;
}

vector<string> sorting(vector<string> names, int max_swaps, int initial_index) {
    vector<string> result = names;
    int swaps = 0;
    int index = initial_index;
    while (swaps < max_swaps) {
        bool some_swap_done = false;
        for (int i = index; i < result.size() - 1; i++) {
            if (result[i] > result[i+1]) {
                some_swap_done = true;
                string tmp = result[i];
                result[i] = result[i+1];
                result[i+1] = tmp; 
                
                swaps++;
                if (swaps == max_swaps) break;
            }
        }

        if (!some_swap_done && index == 0) break;
        index = 0;
    }
    return result;
}

int main() {

    int n, k, instance = 1;
    while (1) {
        scanf("%d %d", &n, &k);
        if (n == 0 && k == 0) break;

        vector<string> names;
        char name_c[21];
        for (int i = 0; i < n; i++) {
            scanf("%s", name_c);
            names.push_back(name_c);
        }

        vector<vector<string>> lists;
        vector<string> answer;
        for (int i = 0; i < names.size() - 1; i++) {
            vector<string> sorted = sorting(names, k, i);
            lists.push_back(sorted);
            if (answer.empty()) {
                answer = sorted;
            } else {
                answer = lesser_lexicographic_list(answer, sorted);
            }
        }

        printf("Instancia %d\n", instance);

        for (int i = 0; i < answer.size(); i++) {
            printf("%s ", answer[i].c_str());
        }
        printf("\n\n");

        instance++;
    }


    return 0;
}