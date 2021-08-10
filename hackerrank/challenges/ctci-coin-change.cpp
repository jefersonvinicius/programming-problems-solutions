#include <stdio.h>
#include <string.h>

#define MAX_COINS 51
#define MAX_N 251
#define llu long long unsigned

llu memo[MAX_N][MAX_COINS];

llu coinChange(int n, int amountOfCoins, int coins[MAX_COINS]) {
    if (n == 0) return 1;
    if (n < 0 || amountOfCoins == 0) return 0;

    if (memo[n][amountOfCoins] != -1) {
        return memo[n][amountOfCoins];
    }

    memo[n][amountOfCoins] = coinChange(n, amountOfCoins - 1, coins) + coinChange(n - coins[amountOfCoins - 1], amountOfCoins, coins);
    return memo[n][amountOfCoins];
}

int main() {

    memset(memo, -1, sizeof(memo));

    int n, m; scanf("%d%d", &n, &m);
    int coins[MAX_COINS];

    for (int i = 0; i < m; i++) {
        int x; scanf("%d", &x);
        coins[i] = x;
    }

    printf("%lld\n", coinChange(n, m, coins));
    return 0;
}