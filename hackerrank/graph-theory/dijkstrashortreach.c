#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_GRAPH_SIZE 5498510

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);
int parse_int(char*);

int* intp(int v) { 
    int* pointer = (int*) malloc(sizeof(int));
    (*pointer) = v;
    return pointer;
}

struct Pair {
    void* left;
    void* right;
};

struct Pair* make_pair(void* left, void* right) {
    struct Pair* pair = malloc(sizeof(struct Pair));
    pair->left = left;
    pair->right = right;
    return pair;
}

struct HeapElement {
    void* value;
};

struct Heap {
    struct HeapElement** elements;
    int max_size, current_index, size;
    size_t element_size;
    int (*cmp)(void*, void*);
};

#define HEAP_ROOT_INDEX 1

int _parent_index(int i) { return i / 2; }
int _left_child_index(int i) { return 2 * i; }
int _right_child_index(int i) { return 2 * i + 1; }

int _get_next_child_index(struct Heap* heap, int index) {
    struct HeapElement* current = heap->elements[index];
    int right_child_index = _right_child_index(index);
    int left_child_index = _left_child_index(index);
    int is_valid_right_child_index = right_child_index <= heap->current_index;
    int is_valid_left_child_index = left_child_index <= heap->current_index;
    if (
        is_valid_right_child_index && 
        heap->cmp(heap->elements[right_child_index]->value, current->value)  && 
        (!is_valid_left_child_index || (is_valid_left_child_index && heap->cmp(heap->elements[right_child_index]->value, heap->elements[left_child_index]->value)))
    ) 
        return right_child_index;
    if (is_valid_left_child_index && heap->cmp(heap->elements[left_child_index]->value, current->value)) return left_child_index;
    return -1;
}

void _swap_elements(struct HeapElement** elements, int index_a, int index_b) {
    void* tmp = elements[index_a];
    elements[index_a] = elements[index_b];
    elements[index_b] = tmp;
}


int _max_cmp(int* a, int* b) { return *a > *b; }
int _min_cmp(int* a, int* b) { return *a < *b; }

struct HeapElement* __create_heap_element(void* value) {
    struct HeapElement* element = (struct HeapElement*) malloc(sizeof(struct HeapElement));
    element->value = value;
    return element;
}

struct Heap* __create_heap(int size, size_t element_size, int (*cmp)(void*, void*)) {
    struct Heap* heap = (struct Heap*) malloc(sizeof(struct Heap));
    heap->max_size = size;
    heap->current_index = 1;
    heap->element_size = element_size;
    heap->elements = (struct HeapElement**) malloc(sizeof(struct HeapElement) * size);
    heap->elements[0] = __create_heap_element(NULL);
    heap->cmp = cmp;
    return heap;
}

#define create_heap(size, element_size, cmp) __create_heap(size, element_size, (int(*)(void*, void*))cmp)

void** heap_to_c_array(struct Heap* heap) {
    void** result = malloc(heap->element_size * heap->current_index);
    for (int i = 1; i < heap->current_index; i++) {
        result[i-1] = heap->elements[i]->value;
    }
    return result;
}

struct Heap* create_max_heap(int size) {
    return create_heap(size, sizeof(int*), _max_cmp);
}

struct Heap* create_min_heap(int size) {
    return create_heap(size, sizeof(int*), _min_cmp);
}

#define heap_insert(heap, value) __heap_insert(heap, (void*) value)

void __heap_insert(struct Heap* heap, void* value) {
    int index = heap->current_index;
    while (index > 1 &&  heap->cmp(value, heap->elements[_parent_index(index)]->value)) {
        heap->elements[index] = heap->elements[_parent_index(index)];
        index = _parent_index(index);
    }
    heap->elements[index] = __create_heap_element(value);
    heap->current_index++;
}

void* heap_top(struct Heap* heap) {
    if (heap->current_index <= 1) return NULL;
    return heap->elements[HEAP_ROOT_INDEX]->value;
}

void* heap_delete(struct Heap* heap) {
    void* deleted_value = heap_top(heap);
    void* last = heap->elements[--heap->current_index];
    heap->elements[HEAP_ROOT_INDEX] = last;
    int index = HEAP_ROOT_INDEX;
    while (1) {
        int next_index = _get_next_child_index(heap, index);
        if (next_index == -1) break;
        _swap_elements(heap->elements, index, next_index);
        index = next_index;
    }
    return deleted_value;
}

int heap_is_empty(struct Heap* heap) {
    return heap->current_index <= 1;
}

struct ALGNode {
    struct ALGNode* next;
    int vertex, weight, parent_vertex;
};

struct ALGNode* create_alg_node(int vertex, int weight) {
    struct ALGNode* node = (struct ALGNode*) malloc(sizeof(struct ALGNode));
    node->vertex = vertex;
    node->weight = weight;
    node->next = NULL;
    node->parent_vertex = -1;
    return node; 
}

struct ALGNode* alg_get_last_node(struct ALGNode* root) {
    struct ALGNode* node = root;
    while (node->next != NULL) node = node->next;
    return node;
}

enum GraphBidirectionalFlag {
    NotBidirectional = 0,
    IsBidirectional = 1
};

struct AdjacencyListGraph {
    struct ALGNode** list;
    enum GraphBidirectionalFlag is_bidirectional;
    size_t size;
};

struct AdjacencyListGraph* create_adjacency_list_graph(enum GraphBidirectionalFlag is_bidirectional) {
    struct AdjacencyListGraph* graph = (struct AdjacencyListGraph*) malloc(sizeof(struct AdjacencyListGraph));
    graph->is_bidirectional = is_bidirectional;
    graph->list = (struct ALGNode**) malloc(sizeof(struct ALGNode) * MAX_GRAPH_SIZE);
    for (int i = 0; i < MAX_GRAPH_SIZE; i++) graph->list[i] = NULL;
    return graph;
}

void __add_edge(struct AdjacencyListGraph* graph, int a, int b, int weight) {
    if (graph->list[a] == NULL) {
        graph->list[a] = create_alg_node(b, weight);
        graph->list[a]->parent_vertex = a;
    } else {
        struct ALGNode* last = alg_get_last_node(graph->list[a]);
        last->next = create_alg_node(b, weight);
        last->next->parent_vertex = a;
    }
}

void graph_add_edge(struct AdjacencyListGraph* graph, int a, int b, int weight) {
    __add_edge(graph, a, b, weight);
    if (graph->is_bidirectional == IsBidirectional) {
        __add_edge(graph, b, a, weight);
    }
}

struct ALGNode* graph_get_vertex_edges(struct AdjacencyListGraph* graph, int vertex) {
    return graph->list[vertex];
}


int cmp_pairs(struct Pair* a, struct Pair* b) {
   int a_weight = *((int*)a->left);
   int b_weight = *((int*)b->left);
   return a_weight < b_weight;
}

struct Pair* __make_vertex_pair(struct AdjacencyListGraph* graph, int vertex) {
    return make_pair(&graph_get_vertex_edges(graph, vertex)->weight, intp(vertex));
}

struct DijkstraResult { int* distances; };

struct DijkstraResult graph_dijkstra(struct AdjacencyListGraph* graph, int initial_vertex) {
    printf("OI\n");

    int distances[MAX_GRAPH_SIZE]; for(int i=0;i<MAX_GRAPH_SIZE;i++) distances[i]=INT_MAX;
    int visited[MAX_GRAPH_SIZE]; memset(visited, 0, sizeof(visited));
    distances[initial_vertex] = 0;
    struct Heap* heap = create_heap(MAX_GRAPH_SIZE, sizeof(struct Pair), cmp_pairs);
    heap_insert(heap, __make_vertex_pair(graph, initial_vertex));
    while (!heap_is_empty(heap)) {
        struct Pair* pair = (struct Pair*) heap_top(heap);
        int current_vertex = *((int*) pair->right);
        heap_delete(heap);
        if (visited[current_vertex]) continue;
        visited[current_vertex] = 1;
        struct ALGNode* node = graph_get_vertex_edges(graph, current_vertex);
        while (node != NULL) {
            if (distances[current_vertex] + node->weight < distances[node->vertex]) 
                distances[node->vertex] = distances[current_vertex] + node->weight;
            
            if (!visited[node->vertex])
                heap_insert(heap, __make_vertex_pair(graph, node->vertex));
            node = node->next;
        }
    }
    free(heap);
    struct DijkstraResult result = { .distances = distances };
    return result;
}

int* shortestReach(int n, int edges_rows, int edges_columns, int** edges, int s, int* result_count) {
    struct AdjacencyListGraph* graph = create_adjacency_list_graph(IsBidirectional);
    for (int i = 0; i < edges_rows; i++) graph_add_edge(graph, edges[i][0] - 1, edges[i][1] - 1, edges[i][2]);
    *result_count = n;
    struct DijkstraResult result = graph_dijkstra(graph, s - 1);
    for (int i = 0; i < n; i++) if (result.distances[i] == INT_MAX) result.distances[i] = -1;
    return result.distances;
}

int main() {
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");
    int t = parse_int(ltrim(rtrim(readline())));
    for (int t_itr = 0; t_itr < t; t_itr++) {
        char** first_multiple_input = split_string(rtrim(readline()));
        int n = parse_int(*(first_multiple_input + 0));
        int m = parse_int(*(first_multiple_input + 1));
        int** edges = malloc(m * sizeof(int*));
        for (int i = 0; i < m; i++) {
            *(edges + i) = malloc(3 * (sizeof(int)));
            char** edges_item_temp = split_string(rtrim(readline()));
            for (int j = 0; j < 3; j++) {
                int edges_item = parse_int(*(edges_item_temp + j));
                *(*(edges + i) + j) = edges_item;
            }
        }
        int s = parse_int(ltrim(rtrim(readline())));
        int result_count;
        int* result = shortestReach(n, m, 3, edges, s, &result_count);
        for (int i = 0; i < result_count; i++) {
            if (i == s - 1) continue;
            fprintf(fptr, "%d", *(result + i));
            if (i != result_count - 1) {
                fprintf(fptr, " ");
            }
        }
        fprintf(fptr, "\n");
    }
    fclose(fptr);
    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
