#include "assert.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

class Spam {
    public:
        int id, initialThreshold, finalThreshold, personIdStart;
        vector<string> labels;

        Spam(int initialThreshold, int finalThreshold, vector<string> labels) {
            this->initialThreshold = initialThreshold;
            this->finalThreshold = finalThreshold;
            this->labels = labels;
        }
};

class Person {
    private:
        unordered_map<int, Person*> friends;
        unordered_map<Spam*, bool> spamsReceived;
        unordered_map<Spam*, int> spamsCount;

        bool hasReceived(Spam* spam) {
            if (this->spamsReceived.find(spam) != this->spamsReceived.end())
                return true;
            return false;
        }

        void addReceived(Spam* spam) {
            this->spamsReceived[spam] = true;
        }

    public:
        int id, spammed;
        string name;

        Person(int id, string name) {
            this->id = id;
            this->name = name;
            this->spammed = 0;
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
            if (!beingSpammed->hasReceived(spam)) {
                this->spamsCount[spam]++;
                beingSpammed->addReceived(spam);
            }
        }

        int countSpammed(Spam* spam) {
            if (this->spamsCount.find(spam) != this->spamsCount.end())
                return this->spamsCount[spam]; 
            return 0;
        }

        string getAttributeFor(Spam* spam) {
            int spammed = this->countSpammed(spam);
            if (spammed < spam->initialThreshold)
                return spam->labels[0];
            if (spammed >= spam->initialThreshold && spammed < spam->finalThreshold)
                return spam->labels[1];
        
            return spam->labels[2];
        }
};

class Network {

    private:
        vector<Person*> people;
        vector<Spam*> spams;

    public:
        vector<string> getPersonAttributes(int personId) {
            
            for (int i = 0; i < this->spams.size(); i++) {
                Spam* spam = this->spams[i];
            }
            queue<Person*> pending;
            return {"rich", "sad"};
        }  

        void addPerson(Person* person) {}

        void addSpam(Spam* spam, int initialIndex) {} 
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

    { // person send spam
        Person* person = new Person(1, "Jeferson");
        Person* pFriend = new Person(2, "Any");
        Spam* spam = new Spam(2, 5, {"poor", "medium", "rich"});
        Spam* spam2 = new Spam(3, 6, {"sad", "medium", "happy"});
        person->sendSpam(spam, pFriend);
        assert(person->countSpammed(spam) == 1);
        person->sendSpam(spam, pFriend);
        assert(person->countSpammed(spam) == 1);
        assert(person->countSpammed(spam2) == 0);
        person->sendSpam(spam2, pFriend);
        assert(person->countSpammed(spam2) == 1);
    }

    { // spam and user attribute
        Spam* spam = new Spam(2, 5, {"poor", "medium", "rich"});
        Person* person = new Person(1, "Jeferson");
        assert(person->getAttributeFor(spam) == "poor");
        person->sendSpam(spam, new Person(2, "Any 1"));
        person->sendSpam(spam, new Person(3, "Any 2"));
        assert(person->getAttributeFor(spam) == "medium");
        person->sendSpam(spam, new Person(4, "Any 3"));
        assert(person->getAttributeFor(spam) == "medium");
        person->sendSpam(spam, new Person(5, "Any 4"));
        person->sendSpam(spam, new Person(6, "Any 5"));
        assert(person->getAttributeFor(spam) == "rich");
        person->sendSpam(spam, new Person(7, "Any 6"));
        assert(person->getAttributeFor(spam) == "rich");
    }

    { // Add friend
        Person* person = new Person(1, "Jeferson");
        assert(person->friendsAmount() == 0);
        person->addFriend(new Person(2, "Any"));
        assert(person->friendsAmount() == 1);
        assert(person->getFriendById(2)->name == "Any");
    }

    { // spamming
        Person* person = new Person(1, "Jeferson");
        person->addFriend(new Person(2, "Any 2"));
        person->addFriend(new Person(3, "Any 3"));
        person->addFriend(new Person(4, "Any 4"));


        Network* network = new Network();
        network->addPerson(person);
        network->addPerson(new Person(5, "Any 5"));
        network->addSpam(new Spam(2, 5, {"poor", "rich", "millionaire"}), 0);
        network->addSpam(new Spam(2, 5, {"sad", "normal", "happy"}), 1);
        assert(network->getPersonAttributes(1)[0] == "rich");
        assert(network->getPersonAttributes(1)[1] == "sad");
    }
}

int main() {
    tests();

    return 0;
}