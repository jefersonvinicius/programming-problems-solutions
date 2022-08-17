#include "stdio.h"
#include "assert.h"
#include <vector>

using namespace std;

class Analogimon {
    public:
        int combatPower, numberOfAttacks;

        Analogimon(int combatPower, int numberOfAttacks) {
            this->combatPower = combatPower;
            this->numberOfAttacks = numberOfAttacks;
        }
};

class Gym {
    public:
        vector<Analogimon*> analogimons;
        int powerInterval;

        Gym(int powerInterval) {
            this->powerInterval = powerInterval;
        }

        void addAnalogimon(Analogimon* analogimon) {
            vector<Analogimon*> withinRules = this->getAnalogimonWithCPWithinDiffOfPIAndCP(analogimon);
            if (withinRules.size() <= analogimon->numberOfAttacks)
                this->analogimons.push_back(analogimon);            
        }

    private:
        vector<Analogimon*> getAnalogimonWithCPWithinDiffOfPIAndCP(Analogimon* analogimonBeingPut) {
            vector<Analogimon*> result;
            int rangeStart = analogimonBeingPut->combatPower - this->powerInterval;
            int rangeEnd = analogimonBeingPut->combatPower + this->powerInterval;   
            for (int i = 0; i < this->analogimons.size(); i++) {
                Analogimon* analogimon = this->analogimons[i];
                if (analogimon->combatPower >= rangeStart && analogimon->combatPower <= rangeEnd) {
                    result.push_back(analogimon);
                }
            }
            return result;
        }
};

int main() {

    { // should add when is empty gym
        Gym* gym = new Gym(3);
        gym->addAnalogimon(new Analogimon(5, 2));

        assert(gym->analogimons.size() == 1);
    }

    { // should add when analogimons within rules is lesser than Number of Attack of analogimon being put
        Gym* gym = new Gym(3);
        gym->addAnalogimon(new Analogimon(5, 2));
        gym->addAnalogimon(new Analogimon(13, 1));

        assert(gym->analogimons.size() == 2);
    }

    // should add when analogimons within rules is equal than Number of Attack of analogimon being put
    { 
        Gym* gym = new Gym(3);
        gym->addAnalogimon(new Analogimon(8, 2));
        gym->addAnalogimon(new Analogimon(12, 1));
        gym->addAnalogimon(new Analogimon(10, 2));

        assert(gym->analogimons.size() == 3);
    }

    { // should not when analogimons within rules is greater than Number of Attack of analogimon being put
        Gym* gym = new Gym(3);
        gym->addAnalogimon(new Analogimon(8, 2));
        gym->addAnalogimon(new Analogimon(12, 1));
        gym->addAnalogimon(new Analogimon(10, 1));

        assert(gym->analogimons.size() == 2);
    }

     // should add when analogimons within rules (end of range) is equal than Number of Attack of analogimon being put
    { 
        Gym* gym = new Gym(3);
        gym->addAnalogimon(new Analogimon(8, 2));
        gym->addAnalogimon(new Analogimon(10, 1));
        gym->addAnalogimon(new Analogimon(14, 1));
        gym->addAnalogimon(new Analogimon(10, 2));

        assert(gym->analogimons.size() == 4);
    }

     // should add when analogimons within rules (end of range) is equal than Number of Attack of analogimon being put
    { 
        Gym* gym = new Gym(3);
        gym->addAnalogimon(new Analogimon(5, 2));
        assert(gym->analogimons.size() == 1);
        gym->addAnalogimon(new Analogimon(13, 1));
        assert(gym->analogimons.size() == 2);
        gym->addAnalogimon(new Analogimon(8, 1));
        assert(gym->analogimons.size() == 3);
        gym->addAnalogimon(new Analogimon(20, 5));
        assert(gym->analogimons.size() == 4);
        gym->addAnalogimon(new Analogimon(6, 1));
        assert(gym->analogimons.size() == 4);
        gym->addAnalogimon(new Analogimon(11, 1));
        assert(gym->analogimons.size() == 4);
        gym->addAnalogimon(new Analogimon(10, 4));
        assert(gym->analogimons.size() == 5);
    }

    int pi, m; scanf("%d%d", &pi, &m);
    Gym* gym = new Gym(pi);
    for (int i = 0; i < m; i++) {
        int cp, na; scanf("%d%d", &cp, &na);
        gym->addAnalogimon(new Analogimon(cp, na));
    }

    printf("%ld\n", gym->analogimons.size());

    return 0;
}