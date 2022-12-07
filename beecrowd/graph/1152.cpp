#include "stdio.h"
#include "assert.h"
#include <vector>
#include <stack>

using namespace std;

class Junction;

class Street {
    public:
        int meters;
        bool illuminated;
        Junction* junctionA;
        Junction* junctionB;

    Street(int meters, Junction* junctionA, Junction* junctionB);
    void illuminate();
    Junction* getNextJunction(Junction* currentJunction);
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
    this->illuminated = false;
}

void Street::illuminate() {
    this->illuminated = true;
}

Junction* Street::getNextJunction(Junction* currentJunction) {
    if (this->junctionA->id == currentJunction->id) return this->junctionB;
    return this->junctionA;
}

class City {
    public:
        vector<Junction*> junctions;
        vector<Street*> streets;

        City(int junctionsAmount) {
            for (int i = 0; i < junctionsAmount; i++) {
                junctions.push_back(new Junction(i));
            }
        }

        void addStreet(int junctionAId, int junctionBId, int meters) {
            Street* street = this->junctions[junctionAId]->addStreet(this->junctions[junctionBId], meters);
            this->streets.push_back(street);
        }

        int getTotalMeters() {
            int result = 0;
            for (int i = 0; i < this->streets.size(); i++) 
                result += this->streets[i]->meters;
            return result;
        }


        int getTotalMetersIlluminated() {
            int result = 0;
            for (int i = 0; i < this->streets.size(); i++)  {
                if (this->streets[i]->illuminated)
                    result += this->streets[i]->meters;
            }
            return result;
        }

        int getTotalMoneySaved() {
            return this->getTotalMeters() - this->getTotalMetersIlluminated();
        }

        void illuminate() {
            bool junctionsVisited[this->junctions.size()] = {false};
            stack<Junction*> pending;
            pending.push(this->junctions[0]);
            while (!pending.empty()) {
                Junction* current = pending.top();
                pending.pop();
                junctionsVisited[current->id] = true;
                printf("VISITING: %d\n", current->id);

                Street* smallerStreet = this->findSmallerStreetNoIlluminated(current->streets);
                if (smallerStreet == NULL) {
                    continue;
                }

                vector<Junction*> newPendingJunctions;
                for (int i = 0; i < current->streets.size(); i++) {
                    Street* street = current->streets[i];
                    Junction* nextJunction = street->getNextJunction(current);
                    if (junctionsVisited[nextJunction->id] == false && !street->illuminated)
                        newPendingJunctions.push_back(nextJunction);
                }
                for (int i = 0; i < newPendingJunctions.size(); i++) {
                    pending.push(newPendingJunctions[i]);
                }
                if (junctionsVisited[smallerStreet->getNextJunction(current)->id] == true) continue;
                smallerStreet->illuminate();
                pending.push(smallerStreet->getNextJunction(current));
            }
        }

        void debug() {
            printf(">>> CITY <<<\n");
            printf("STREETS AMOUNT: %ld\n", this->streets.size());
        }
    private:

        Street* findSmallerStreetNoIlluminated(vector<Street*> streets) {
            Street* result = NULL;
            for (int i = 0; i < streets.size(); i++) {
                if ((result == NULL && !streets[i]->illuminated) ||
                    (result != NULL && streets[i]->meters < result->meters && !streets[i]->illuminated)) {
                    result = streets[i];
                }
            }
            return result;
        }
};

void tests() {
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

     { // illumination street
        Junction* junction1 = new Junction(0);
        Junction* junction2 = new Junction(1);
        junction1->addStreet(junction2, 10);
        junction1->streets[0]->illuminate();
        assert(junction1->streets[0]->illuminated == true);
        assert(junction2->streets[0]->illuminated == true);
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
        city->junctions[0]->streets[0]->illuminate();
        assert(city->streets.size() == 3);
        assert(city->getTotalMeters() == 65);
        assert(city->getTotalMetersIlluminated() == 10);
        assert(city->getTotalMoneySaved() == 55);
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
        printf("OII\n");
        city->illuminate();
        printf("OII2\n");
        printf("SAVED: %d\n", city->getTotalMoneySaved());
        assert(city->getTotalMoneySaved() == 0);
    }
}

int main() {
    #ifdef TESTING
        printf(">>> TESTING <<<\n");
        tests();
        printf("OK.\n\n");
        return 0;
    #endif

    return 0;
}