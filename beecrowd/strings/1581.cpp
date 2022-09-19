#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

int main() {

    int n, k;
    scanf("%d", &n);

    while (n--) {
        scanf("%d\n", &k);
        string firstLanguage, currentLanguage;
        bool alreadydDifferentsFound = false;

        for (int i = 0; i < k; i++) {
            getline(cin, currentLanguage);

            if (i == 0) {
                firstLanguage = currentLanguage;
                continue;
            }

            if (currentLanguage != firstLanguage && !alreadydDifferentsFound) {
                printf("ingles\n");
                alreadydDifferentsFound = true;
                continue;
            }

            if (i == k - 1 && currentLanguage == firstLanguage && !alreadydDifferentsFound) {
                printf("%s\n", currentLanguage.c_str());
            }
        }
    }

    return 0;
}