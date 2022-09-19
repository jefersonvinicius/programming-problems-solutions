#include <stdio.h>
#include <map>
#include <string>

using namespace std;

int main() {

    int n, numberOfProducts, listSize, listProductAmount;
    char productName[51];
    double productPrice;

    map<string, double> productsPrices;

    scanf("%d", &n);
    while (n--) {
        scanf("%d", &numberOfProducts);
        while (numberOfProducts--) {
            scanf("%s %lf", productName, &productPrice);
            string s = productName;
            productsPrices[s] = productPrice;
        }

        scanf("%d", &listSize);
        double total = 0;
        while (listSize--) {
            scanf("%s %d", productName, &listProductAmount);
            string s = productName;

            total += (productsPrices[s] * listProductAmount);
        }

        printf("R$ %.2lf\n", total);

    }

    return 0;
}