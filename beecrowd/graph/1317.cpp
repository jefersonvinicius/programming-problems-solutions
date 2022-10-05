#include "assert.h"
#include <string>
#include <vector>

using namespace std;

class Person {
    public:
        int id, spammed;
        string name;

        Person(int id, string name) {
            this->id = id;
            this->name = name;
            this->spammed = 0;
        }

        void incrementSpammed() {
            this->spammed++;
        }
};

class Spam {
    public:
        int initialThreshold, finalThreshold;
        vector<string> labels;

        Spam(int initialThreshold, int finalThreshold, vector<string> labels) {
            this->initialThreshold = initialThreshold;
            this->finalThreshold = finalThreshold;
            this->labels = labels;
        }

        string determinePersonAttribute(Person* person) {
            if (person->spammed < this->initialThreshold)
                return labels[0];
            if (person->spammed >= this->initialThreshold && person->spammed < this->finalThreshold)
                return labels[1];
            
            return labels[2];
        }

};

void tests() {
    { // person creation
        Person* person = new Person(1, "Jeferson");
        assert(person->id == 1);
        assert(person->name == "Jeferson");
        assert(person->spammed == 0);
    }

    { // spam creation
        Spam* spam = new Spam(2, 5, {"poor", "medium", "rich"});
        assert(spam->initialThreshold == 2);
        assert(spam->finalThreshold == 5);
        assert(spam->labels[0] == "poor");
        assert(spam->labels[1] == "medium");
        assert(spam->labels[2] == "rich");
    }

    { // spam and user attribute
        Spam* spam = new Spam(2, 5, {"poor", "medium", "rich"});
        Person* person = new Person(1, "Jeferson");
        assert(spam->determinePersonAttribute(person) == "poor");
        person->incrementSpammed();
        person->incrementSpammed();
        assert(spam->determinePersonAttribute(person) == "medium");
        person->incrementSpammed();
        assert(spam->determinePersonAttribute(person) == "medium");
        person->incrementSpammed();
        person->incrementSpammed();
        assert(spam->determinePersonAttribute(person) == "rich");
        person->incrementSpammed();
        assert(spam->determinePersonAttribute(person) == "rich");        
    }
}

int main() {
    tests();

    return 0;
}