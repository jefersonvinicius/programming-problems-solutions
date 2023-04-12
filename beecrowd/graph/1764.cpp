#include "stdio.h"
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_ROADS 50005
#define MAX_CITIES 40000

int* make_disjoint_sets(size_t size) {
    int* sets = (int*) malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) sets[i] = i;
    return sets;
}

int find_set_parent(int* parent, int set) {
    if (parent[set] == set) return set;
    return find_set_parent(parent, parent[set]);
}

void union_sets(int* parent, int a, int b) {
    int parent_a = find_set_parent(parent, a);
    int parent_b = find_set_parent(parent, b);
    parent[parent_b] = parent_a;
}

bool is_same_set(int* parent, int a, int b) {
    return find_set_parent(parent, a) == find_set_parent(parent, b); 
}

struct Edge {
    int a, b, weight;
};

bool heap_comparision(struct Edge a, struct Edge b) {
    return a.weight > b.weight;
}

int main() {
    while (true) {
        int numberOfCities, numberOfRoads; scanf("%d%d", &numberOfCities, &numberOfRoads);
        if (numberOfCities == 0 && numberOfRoads == 0) break;
    

        vector<struct Edge> connections;
        for (int i = 0; i < numberOfRoads; i++) {
            int routeA, routeB, distance; scanf("%d%d%d", &routeA, &routeB, &distance);
            connections.push_back(Edge {
                .a = routeA,
                .b = routeB,
                .weight = distance
            });
        }

        make_heap(connections.begin(), connections.end(), heap_comparision);
        int answer = 0;
        int* sets = make_disjoint_sets(numberOfCities);
        while (!connections.empty()) {
            struct Edge edge = connections.front();
            if (!is_same_set(sets, edge.a, edge.b)) {
                answer += edge.weight;
                union_sets(sets, edge.a, edge.b);
            }
            pop_heap(connections.begin(), connections.end(), heap_comparision); connections.pop_back();
        }
        free(sets);
        printf("%d\n", answer);
    }

    return 0;
}