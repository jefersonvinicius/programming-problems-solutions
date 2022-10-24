#include "assert.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>

#define MAX_PERSON 25
#define MAX_SPAM_ATTRIBUTE_LENGTH 23
#define MAX_PERSON_NAME_LENGTH 23

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

// class SpamReceived {
//     public:
//         Spam* spam;
//         Person* source;

//         SpamReceived(Spam* spam, Person* person) {
//             this->spam = spam;
//             this->source = source;
//         }
// }

class Person {
    private:
        unordered_map<int, Person*> friends;
        unordered_map<int, unordered_map<Spam*, bool> > spamsReceived;
        unordered_map<Spam*, int> spamsCount;

        bool hasReceived(Spam* spam, Person* from) {
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
                printf("%s spamming %s\n", this->name.c_str(), beingSpammed->name.c_str());
                this->spamsCount[spam]++;
                beingSpammed->addReceived(spam);
            }
        }

        int countSpammed(Spam* spam) {
            if (this->spamsCount.find(spam) != this->spamsCount.end())
                return this->spamsCount[spam]; 
            return 0;
        }

        vector<Person*> getFriends() {
            vector<Person*> result;
            for (auto a : this->friends) result.push_back(a.second);
            return result;
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


void printPeople(vector<Person*> people) {
    for (auto person : people) {
        printf("%s ", person->name.c_str());
    }
    printf("\n");
}


class Network {
    private:
        class SpamIndexed {
            public: 
                Spam* spam;
                int index;

                SpamIndexed(Spam* spam, int index) {
                    this->spam = spam;
                    this->index = index;
                }
        };

        vector<Person*> people;
        vector<SpamIndexed*> spams;

    public:
        ~Network() {
            printf("Destroying network\n");
        }

        vector<string> getPersonAttributes(int personIndex) {
            vector<string> result;
            Person* person = this->people[personIndex];
            for (int i = 0; i < this->spams.size(); i++) {
                Spam* spam = this->spams[i]->spam;
                result.push_back(person->getAttributeFor(spam));
            }
            return result;
        }  

        void startSpamming() {
            for (int i = 0; i < this->spams.size(); i++) {
                SpamIndexed* spam = this->spams[i];
                printf("::: SPAM %s %s %s - %d\n", spam->spam->labels[0].c_str(), spam->spam->labels[1].c_str(), spam->spam->labels[2].c_str(), spam->index);
                this->spamming(this->people[spam->index], spam->spam);
            }
        }

        void addPerson(Person* person) {
            this->people.push_back(person);
        }

        void addSpam(Spam* spam, int initialIndex) {
            this->spams.push_back(new SpamIndexed(spam, initialIndex));
        } 

        vector<Person*> getPeople() {
            return this->people;
        }

    private:
        void spamming(Person* person, Spam* spam) {
            bool alreadySpammed[MAX_PERSON] = { false };
            queue<Person*> pending;
            pending.push(person);

            printf("---- %s\n", person->name.c_str());
            printf(">>>>> ");
            printPeople(person->getFriends());
            while (!pending.empty()) {
                Person* current = pending.front();

                for (auto aFriend : current->getFriends()) {
                    current->sendSpam(spam, aFriend);
                    if (!alreadySpammed[current->id]) pending.push(aFriend);
                }
                
                alreadySpammed[current->id] = true;
                pending.pop();
            }
        } 
};

/**
 * [x] circular reference 
 * [] Destroy network
 */

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
        network->startSpamming();
        assert(network->getPersonAttributes(0)[0] == "rich");
        assert(network->getPersonAttributes(0)[1] == "sad");
    }

    { // spamming cyclic
        Person* person = new Person(1, "Jeferson");
        Person* person2 = new Person(2, "Any 2");
        person->addFriend(person2);
        person2->addFriend(person);
        person->addFriend(new Person(3, "Any 3"));
        person->addFriend(new Person(4, "Any 4"));

        Network* network = new Network();
        network->addPerson(person);
        network->addPerson(new Person(5, "Any 5"));
        network->addSpam(new Spam(2, 5, {"poor", "rich", "millionaire"}), 0);
        network->addSpam(new Spam(2, 5, {"sad", "normal", "happy"}), 1);
        network->startSpamming();
        assert(network->getPersonAttributes(0)[0] == "rich");
        assert(network->getPersonAttributes(0)[1] == "sad");
    }

    { // spamming deep
        Person* bob = new Person(1, "bob");
        Person* paul = new Person(2, "paul");
        Person* mary = new Person(3, "mary");

        bob->addFriend(mary);
        bob->addFriend(paul);
        paul->addFriend(bob);
        paul->addFriend(mary);
        paul->addFriend(new Person(4, "Julia"));
        paul->addFriend(new Person(5, "Alice"));

        Network* network = new Network();
        network->addPerson(bob);
        network->addPerson(paul);
        Spam* spam = new Spam(2, 4, {"poor", "rich", "millionaire"});
        network->addSpam(spam, 0);
        network->startSpamming();
        assert(paul->countSpammed(spam) == 4);
        assert(network->getPersonAttributes(1)[0] == "millionaire");
    }
}

int main() {
    tests();
    if (1 == 1) return 0;

    int numberOfPeople;
    while (true) {
        Network* network = new Network();
        scanf("%d", &numberOfPeople);
        if (numberOfPeople == 0) break;

        vector<int> peopleConnections[numberOfPeople];
        for (int i = 0; i < numberOfPeople; i++) {
            vector<int> connections;
            while (true) {
                int x; scanf("%d", &x);
                if (x == 0) break;
                peopleConnections[i].push_back(x - 1);
            }
        }

        while (true)  {
            int spamPersonStartIndex; scanf("%d", &spamPersonStartIndex);
            if (spamPersonStartIndex == 0) break;
            int initialThreshold, finalThreshold;
            char attrA[MAX_SPAM_ATTRIBUTE_LENGTH], attrB[MAX_SPAM_ATTRIBUTE_LENGTH], attrC[MAX_SPAM_ATTRIBUTE_LENGTH];
            scanf("%d%d%s%s%s", &initialThreshold, &finalThreshold, attrA, attrB, attrC);
            Spam* spam = new Spam(initialThreshold, finalThreshold, { attrA, attrB, attrC });
            network->addSpam(spam, spamPersonStartIndex - 1);
        }

        for (int i = 0; i < numberOfPeople; i++) {
            char name[MAX_PERSON_NAME_LENGTH]; scanf("%s", name);
            Person* person = new Person(i, name);
            network->addPerson(person);
        }


        for (int i = 0; i < numberOfPeople; i++) {
            Person* current = network->getPeople()[i];
            vector<int> friendsIndexes = peopleConnections[i];
            for (int f = 0; f < friendsIndexes.size(); f++) {
                int friendIndex = friendsIndexes[f];
                current->addFriend(network->getPeople()[friendIndex]);
            }
        }

        for (int i = 0; i < numberOfPeople; i++) {
            printf("-- %s\n", network->getPeople()[i]->name.c_str());
            printPeople(network->getPeople()[i]->getFriends());
        }

        network->startSpamming();
        vector<Person*> people = network->getPeople();
        for (int i = 0; i < people.size(); i++) {
            Person* person = people[i];
            printf("%s:", person->name.c_str());
            vector<string> attrs = network->getPersonAttributes(i);
            for (auto attr : attrs) {
                printf(" %s", attr.c_str());
            }
            printf("\n");
        }
    }

    return 0;
}