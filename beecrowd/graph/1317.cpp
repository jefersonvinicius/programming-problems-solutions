#include "assert.h"
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Spam;
class Person;

class Person {
    private:
        unordered_map<int, Person*> friends;
        unordered_map<string, bool> spammedTrack;
        unordered_map<Spam*, int> spamsCount;
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

        int friendsAmount() {
            return this->friends.size();
        }

        void addFriend(Person* person) {
            this->friends[person->id] = person;
        }

        Person* getFriendById(int id) {
            if (this->friends.find(id) != this->friends.end())
                return this->friends[id];
            return NULL;
        }

        void sendSpam(Spam* spam, Person* beingSpammed) {
            string key = to_string(spam->id) + "-" + to_string(beingSpammed->id);
            if (this->spammedTrack[key] != true) {
                this->spamsCount[spam]++;
                this->spammedTrack[key] = true;
            }
        }

        int countSpammed(Spam* spam) {
            if (this->spamsCount.find(spam) != this->spamsCount.end())
                return this->spamsCount[spam]; 
            return 0;
        }
};

class Spam {
    public:
        int id, initialThreshold, finalThreshold;
        vector<string> labels;

        Spam(int id, int initialThreshold, int finalThreshold, vector<string> labels) {
            this->id = id;
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
        Spam* spam = new Spam(1, 2, 5, {"poor", "medium", "rich"});
        assert(spam->initialThreshold == 2);
        assert(spam->finalThreshold == 5);
        assert(spam->labels[0] == "poor");
        assert(spam->labels[1] == "medium");
        assert(spam->labels[2] == "rich");
    }

    { // person send spam
        Person* person = new Person(1, "Jeferson");
        Person* pFriend = new Person(2, "Any");
        Spam* spam = new Spam(1, 2, 5, {"poor", "medium", "rich"});
        Spam* spam2 = new Spam(1, 3, 6, {"sad", "medium", "happy"});
        person->sendSpam(spam, pFriend);
        assert(person->countSpammed(spam) == 1);
        person->sendSpam(spam, pFriend);
        assert(person->countSpammed(spam) == 1);
        assert(person->countSpammed(spam2) == 0);
        person->sendSpam(spam2, pFriend);
        assert(person->countSpammed(spam2) == 1);
    }

    { // spam and user attribute
        Spam* spam = new Spam(1, 2, 5, {"poor", "medium", "rich"});
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

    { // Add friend
        Person* person = new Person(1, "Jeferson");
        assert(person->friendsAmount() == 0);
        person->addFriend(new Person(2, "Any"));
        assert(person->friendsAmount() == 1);
        assert(person->getFriendById(2)->name == "Any");
    }
}

int main() {
    tests();

    return 0;
}