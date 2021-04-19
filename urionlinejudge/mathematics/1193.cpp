#include <stdio.h>
#include <string>

using namespace std;

string decimalToBinary(int dec) {
    
    if (dec == 1) return "1";

    string binary = "";
    int bit;
    while (true) {
        dec /= 2;
        if (dec == 1 || dec == 0) break;

        bit = dec%2; 
        printf("bit: %d\n", bit);
        binary += to_string(bit);
    }

    reverse(binary.begin(), binary.end());

    return binary;

}

int main() {

    int n; scanf("%d", &n);
    
    while (n--) {
        char x[50], type[4]; scanf("%s", x);

        string number = x;
        int numberInt = stoi(number);

        printf("NUMBER: %s\n", number.c_str());
        printf("Binario: %s\n", decimalToBinary(numberInt).c_str());
        printf("\n");
    }

    return 0;
}