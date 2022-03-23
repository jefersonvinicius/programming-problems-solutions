#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void print_vector(vector<string> v) {
    for (auto item : v) {
        printf("%s ", item.c_str());
    }
}

vector<string> lesser_lexicographic_list(vector<string> list1, vector<string> list2) {
    for (int i = 0; i < list1.size(); i++) {
        if (list1[i] < list2[i]) return list1;
        else if (list2[i] < list1[i]) return list2;
    }
    return list1;
}

int index_of(vector<string> items, string target) {
    vector<string>::iterator it = find(items.begin(), items.end(), target);
    if (it != items.end()) return it - items.begin();
    return -1;
}

int select_better_swap(vector<string> items) {
    int index = -1;
    for (int i = 0; i < items.size() - 1; i++) {
        vector<string> copy = items;
        string tmp = copy[i];
        copy[i] = copy[i+1];
        copy[i+1] = tmp;
        if (copy[i] < items[i]) index = i;
    }
    return index;
}

vector<string> sorting(vector<string> names, int max_swaps, string target) {
    vector<string> result = names;
    if (result.size() == 1) return result;

    int swaps = 0;
    while (swaps < max_swaps) {
        print_vector(result);
        printf("\n");
        int index = select_better_swap(result);
        // printf("index: %d\n", index);
        if (index == -1) break;
        swaps++;
        string tmp = result[index];
        result[index] = result[index+1];
        result[index+1] = tmp;
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

        vector<vector<string>> lists;
        vector<string> answer = names;
        vector<string> sorted_names = names;
        sort(sorted_names.begin(), sorted_names.end());

        for (int i = 0; i < sorted_names.size(); i++) {
            vector<string> sorted = sorting(names, k, sorted_names[i]);
            answer = lesser_lexicographic_list(answer, sorted);
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