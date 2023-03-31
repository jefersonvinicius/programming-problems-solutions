#include "stdio.h"
#include "assert.h"
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

#define MAX_DISJOINT_SET 200005

struct IntDisjointSet {
    int* parent;    
};

struct IntDisjointSet* create_set() {
    struct IntDisjointSet* set = (struct IntDisjointSet*) malloc(sizeof(struct IntDisjointSet));
    set->parent = (int*) malloc(MAX_DISJOINT_SET * sizeof(int));
    for (int i = 0; i < MAX_DISJOINT_SET; i++) set->parent[i] = i;
    return set;
}

int set_find(struct IntDisjointSet* set, int i) {
    if (set->parent[i] == i) return i;
    return set_find(set, set->parent[i]);
}

void set_union(struct IntDisjointSet* set, int a, int b) {
    int a_parent = set_find(set, a);
    int b_parent = set_find(set, b);
    set->parent[b_parent] = a_parent;
}

int set_same(struct IntDisjointSet* set, int a, int b) {
    return set_find(set, a) == set_find(set, b);
}

class Junction;

class Street {
    public:
        int meters;
        Junction* junctionA;
        Junction* junctionB;

    Street(int meters, Junction* junctionA, Junction* junctionB);
};

class Junction {
    public:
        int id;
        vector<Street*> streets;

        Junction(int id) {
            this->id = id;
        }

        Street* addStreet(Junction* to, int meters) {
            Street* street = new Street(meters, this, to);
            this->streets.push_back(street);
            to->streets.push_back(street);
            return street;
        }
};

Street::Street(int meters, Junction* junctionA, Junction* junctionB) {
    this->meters = meters;
    this->junctionA = junctionA;
    this->junctionB = junctionB;
}

bool compare(Street* a, Street* b) { return a->meters > b->meters; }

class City {
    private:
        unsigned long int totalMeters, totalIlluminatedMeters;

    public:
        vector<Junction*> junctions;
        vector<Street*> streets;

        City(int junctionsAmount) {
            for (int i = 0; i < junctionsAmount; i++) {
                junctions.push_back(new Junction(i));
            }
            this->totalIlluminatedMeters = 0;
            this->totalMeters = 0;
        }

        void addStreet(int junctionAId, int junctionBId, int meters) {
            Street* street = this->junctions[junctionAId]->addStreet(this->junctions[junctionBId], meters);
            this->streets.push_back(street);
            this->totalMeters += meters;
        }

        unsigned long int getTotalMeters() {
            return this->totalMeters;
        }


        unsigned long int getTotalMetersIlluminated() {
            return this->totalIlluminatedMeters;
        }

        unsigned long int getTotalMoneySaved() {
            return this->totalMeters - this->totalIlluminatedMeters;
        }

        void illuminate() {
            vector<Street*> streets(this->streets);
            make_heap(streets.begin(), streets.end(), compare);
            struct IntDisjointSet* set = create_set();
            while (!streets.empty()) {
                Street* current = streets.front();
                if (!set_same(set, current->junctionA->id, current->junctionB->id)) {
                    set_union(set, current->junctionA->id, current->junctionB->id);
                    this->totalIlluminatedMeters += current->meters;
                }
                pop_heap(streets.begin(), streets.end(), compare); streets.pop_back();
            }
        }
};


void printStreets(vector<Street*> streets) {
    for (auto street : streets) {
        printf("%d ", street->meters);
    }
    printf("\n");
}

void tests() {
    { // heap study
        vector<Street*> streets;
        Junction* junction1 = new Junction(1);
        Junction* junction2 = new Junction(2);
        Junction* junction3 = new Junction(3);
        streets.push_back(new Street(10, junction1, junction2));
        streets.push_back(new Street(20, junction1, junction3));
        streets.push_back(new Street(50, junction1, junction3));
        make_heap(streets.begin(), streets.end(), compare);
        assert(streets.front()->meters == 10);
        pop_heap(streets.begin(), streets.end(), compare); streets.pop_back();
        assert(streets.front()->meters == 20);
        pop_heap(streets.begin(), streets.end(), compare); streets.pop_back();
        assert(streets.front()->meters == 50);
    }

    { // junction creation
        Junction* junction1 = new Junction(0);
        Junction* junction2 = new Junction(1);
        junction1->addStreet(junction2, 10);
        assert(junction1->streets.size() == 1);
        assert(junction1->streets[0]->junctionA->id == 0);
        assert(junction1->streets[0]->junctionB->id == 1);
        assert(junction1->streets[0]->meters == 10);
        assert(junction2->streets.size() == 1);
        assert(junction2->streets[0]->junctionA->id == 0);
        assert(junction2->streets[0]->junctionB->id == 1);
        assert(junction2->streets[0]->meters == 10);
    }

    { // city creation
        City* city = new City(10);
        assert(city->junctions.size() == 10);
    }

    { // city streets building
        City* city = new City(3);
        city->addStreet(0, 1, 10);
        city->addStreet(1, 2, 5);
        city->addStreet(2, 0, 50);
        city->illuminate();
        assert(city->streets.size() == 3);
        assert(city->getTotalMeters() == 65);
        assert(city->getTotalMetersIlluminated() == 15);
        assert(city->getTotalMoneySaved() == 50);
    }

    { // illuminating city (2 junctions)
        City* city = new City(2);
        city->addStreet(0, 1, 10);
        city->illuminate();
        assert(city->getTotalMoneySaved() == 0);
    }

    { // illuminating city (3 junctions - cycle)
        City* city = new City(3);
        city->addStreet(0, 1, 10);
        city->addStreet(0, 2, 20);
        city->addStreet(1, 2, 5);
        city->illuminate();
        assert(city->getTotalMoneySaved() == 20);
    }

    { // illuminating city (3 junctions - no cycle)
        City* city = new City(4);
        city->addStreet(0, 1, 10);
        city->addStreet(1, 2, 8);
        city->addStreet(1, 3, 7);
        city->illuminate();
        assert(city->getTotalMoneySaved() == 0);
    }

    { // illuminating city (4 junctions - backing)
        City* city = new City(4);
        city->addStreet(0, 1, 6);
        city->addStreet(0, 2, 7);
        city->addStreet(1, 3, 100);
        city->addStreet(2, 3, 2);
        city->illuminate();
        assert(city->getTotalMoneySaved() == 100);
    }

    { // illuminating city (7 junctions)
        City* city = new City(7);
        city->addStreet(0, 1, 7);
        city->addStreet(0, 3, 5);
        city->addStreet(1, 2, 8);
        city->addStreet(1, 3, 9);
        city->addStreet(1, 4, 7);
        city->addStreet(2, 4, 5);
        city->addStreet(3, 4, 15);
        city->addStreet(3, 5, 6);
        city->addStreet(4, 5, 8);
        city->addStreet(4, 6, 9);
        city->addStreet(5, 6, 11);
        city->illuminate();
        assert(city->getTotalMoneySaved() == 51);
    }
}

int main() {
    #ifdef TESTING
        printf(">>> TESTING <<<\n");
        tests();
        printf("OK.\n\n");
        return 0;
    #endif

    while (true) {
        int m, n; scanf("%d%d", &m, &n);
        if (m == 0 && n == 0) break;
        City* city = new City(m);
        for (int i = 0; i < n; i++) {
            int x, y, z; scanf("%d%d%d", &x, &y, &z);
            city->addStreet(x, y, z);
        }
        city->illuminate();
        printf("%ld\n", city->getTotalMoneySaved());
    }

    return 0;
}