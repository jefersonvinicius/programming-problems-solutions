#include <stdio.h>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;



int main() {

    int amountAliceCards, amountBettyCards;
    while (true) {
        scanf("%d%d", &amountAliceCards, &amountBettyCards);
        if (amountAliceCards == 0 && amountBettyCards == 0) break;

        set<int> aliceCards, bettyCards;
        int n;
        for (int i = 0; i < amountAliceCards; i++) {
            scanf("%d", &n); aliceCards.insert(n);
        }

        for (int i = 0; i < amountBettyCards; i++) {
            scanf("%d", &n); bettyCards.insert(n);
        }

        vector<int> diffBetweenAliceAndBetty(aliceCards.size()), diffBetweenBettyAndAlice(bettyCards.size());
        vector<int>::iterator it;
        
        it = set_difference(aliceCards.begin(), aliceCards.end(), bettyCards.begin(), bettyCards.end(), diffBetweenAliceAndBetty.begin());
        diffBetweenAliceAndBetty.resize(it-diffBetweenAliceAndBetty.begin());

        it = set_difference(bettyCards.begin(), bettyCards.end(), aliceCards.begin(), aliceCards.end(), diffBetweenBettyAndAlice.begin());
        diffBetweenBettyAndAlice.resize(it-diffBetweenBettyAndAlice.begin());

        int answer = min(diffBetweenBettyAndAlice.size(), diffBetweenAliceAndBetty.size());

        printf("%d\n", answer);
    }

    return 0;
}