#include <stdio.h>
#include <unordered_map>

using namespace std;

int main() {

    unordered_map<int, int> noddles;
    int noddles_quantity, days_quantity;
    scanf("%d %d", &noddles_quantity, &days_quantity);

    int x;
    for (int i = 0; i < noddles_quantity; i++) {
        scanf("%d", &x); 
        noddles[x]++;
    }

    bool achieved = true;
    for (int i = 0; i < days_quantity; i++) {
        scanf("%d", &x); 
        if (noddles.find(x) == noddles.end() || noddles[x] == 0) {
            achieved = false;
            break;
        } else {
            noddles[x]--;
        }
    }

    if (achieved) printf("Yes\n");
    else printf("No\n");

    return 0;
}