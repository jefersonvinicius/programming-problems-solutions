
#include <stdio.h>
#include <stdlib.h>

struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};

struct AdjList {
    struct AdjListNode* head;
};

struct Graph {
    int V;
    struct AdjList* array;
};

struct AdjListNode* newAdjListNode(int dest) {
    struct AdjListNode* newNode =
        (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;

    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));

    for (int i = 0; i < V; ++i) graph->array[i].head = NULL;

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {

    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

void reverseUtil(struct AdjListNode** head_ref) {
    struct AdjListNode* prev = NULL;
    struct AdjListNode* current = *head_ref;
    struct AdjListNode* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head_ref = prev;
}

void reverse(struct Graph* graph) {
    int v;
    for (v = 0; v < graph->V; ++v) {
        struct AdjListNode* pCrawl = graph->array[v].head;
        reverseUtil(&graph->array[v].head);
    }
}

struct AdjList* printGraph(int V, struct Graph* adj) {
    return adj->array;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int V;
        scanf("%d", &V);
        int E;
        scanf("%d", &E);
        struct Graph* graph = createGraph(V);
        for (int i = 0; i < E; i++) {
            int u, v;
            scanf("%d", &u);
            scanf("%d", &v);
            addEdge(graph, u, v);
        }
        reverse(graph);
        struct AdjList* ans =
            (struct AdjList*)malloc(V * sizeof(struct AdjList));
        ans = printGraph(V, graph);
        for (int v = 0; v < V; ++v) {
            struct AdjListNode* pCrawl = ans[v].head;
            printf("%d", v);
            while (pCrawl) {
                printf("-> %d", pCrawl->dest);
                pCrawl = pCrawl->next;
            }
            printf("\n");
        }
    }

    return 0;
}
