#include <stdio.h>
#include <unordered_map>
#include <string.h>
#include <limits.h>

using namespace std;

class MatchResult {
    public:
        string team1, team2;
        int team1Goals, team2Goals;
    
        MatchResult(string resultStr) {
            char* dump = strdup(resultStr.c_str());
            char* token;
            token = strtok(dump, " -");
            this->team1 = token;
            token = strtok(NULL, " -");
            this->team1Goals = atoi(token);
            token = strtok(NULL, " -");
            this->team2Goals = atoi(token);
            token = strtok(NULL, " -");
            this->team2 = token;
            free(dump);
        }

        bool isTied() {
            return this->team1Goals == this->team2Goals;
        }
        
        bool isTeam1Winner() {
            return this->team1Goals > this->team2Goals;
        }

        bool isTeam2Winner() {
            return !this->isTeam1Winner();
        }

        int team1Score() {
            int base = this->team1Goals * 3;
            if (this->isTied()) return base + 1;
            return base + (this->isTeam1Winner() ? 5 : 0);
        }

        int team2Score() {
            int base = this->team2Goals * 3;
            if (this->isTied()) return base + 1;
            return base + (this->isTeam2Winner() ? 5 : 0);
        }
};

int main() {

    while (true) {
        int n; scanf("%d", &n);
        if (n == 0) break;

        unordered_map<string, int> teamsScores;
        char name[1000];
        int score;
        for (int i = 0; i < n; i++) {
            scanf("%s %d", name, &score);
            teamsScores[name] = score;
        }

        char resultStr[10000];
        for (int i = 0; i < n/2; i++) {
            scanf(" %[^\n]", resultStr);
            MatchResult result(resultStr);
            teamsScores[result.team1] += result.team1Score();
            teamsScores[result.team2] += result.team2Score();
        }

        pair<string, int> teamWinner = make_pair("any", INT_MIN);
        for (pair<string, int> teamScore : teamsScores) {
            if (teamScore.second > teamWinner.second) {
                teamWinner = teamScore;
            }
        }

        if (teamWinner.first == "Sport") {
            printf("O Sport foi o campeao com %d pontos :D\n", teamWinner.second);
        } else {
            printf("O Sport nao foi o campeao. O time campeao foi o %s com %d pontos :(\n", teamWinner.first.c_str(), teamWinner.second);
        }
        printf("\n");
    }

    return 0;
}