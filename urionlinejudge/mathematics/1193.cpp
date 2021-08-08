#include <stdio.h>
#include <string>
#include <algorithm>
#include <math.h>

using namespace std;

char getHexLetterOf(int n) {
    if (n == 10) return 'a';
    if (n == 11) return 'b';
    if (n == 12) return 'c';
    if (n == 13) return 'd';
    if (n == 14) return 'e';
    if (n == 15) return 'f';
    return n + '0';
}

int getDecValueOf(char hexLetter) {
    if (hexLetter == 'a') return 10;
    if (hexLetter == 'b') return 11;
    if (hexLetter == 'c') return 12;
    if (hexLetter == 'd') return 13;
    if (hexLetter == 'e') return 14;
    if (hexLetter == 'f') return 15;
    return hexLetter - '0';
}

string decimalToHex(int dec) {
    if (dec <= 15) return to_string(getHexLetterOf(dec));

    string result = "";
    while (true) {
        char letter = getHexLetterOf(dec%16);
        result += letter;
        dec /= 16;
        if (dec == 0) break;
    }
    reverse(result.begin(), result.end());
    return result;
}


string decimalToBinary(int dec) {
    if (dec == 1) return "1";
    if (dec == 0) return "0";

    string result = "";
    while (true) {
        result += to_string(dec%2);
        dec /= 2;
        if (dec == 0) break;
    }
    reverse(result.begin(), result.end());
    return result;
}

int hexToDecimal(string hex) {
    int result = 0, power = 0;
    for (int i = hex.size() - 1; i >= 0; i--) {
        int n = getDecValueOf(hex[i]);
        result += (n * pow(16, power));
        power++;
    }
    return result;
}


string hexToBinary(string hex) {
    int dec = hexToDecimal(hex);
    return decimalToBinary(dec);
}

int binaryToDecimal(string binary) {
    int result = 0, power = 0;
    for (int i = binary.size() - 1; i >= 0; i--) {
        if (binary[i] == '1') {
            result += pow(2, power);
        }
        power++;
    }
    return result;
}

string binaryToHex(string binary) {
    int dec = binaryToDecimal(binary);
    return decimalToHex(dec);
}

int main() {

    int n; scanf("%d", &n);
    
    int currentCase = 1;
    while (n--) {
        char x[50], type_c_str[4]; scanf("%s %s", x, type_c_str);

        string number = x;
        string type = type_c_str;

        printf("Case %d:\n", currentCase);

        if (type == "dec") {
            int numberInt = stoi(number);
            printf("%s hex\n", decimalToHex(numberInt).c_str());
            printf("%s bin\n", decimalToBinary(numberInt).c_str());
        }
        if (type == "bin") {
            printf("%d dec\n", binaryToDecimal(number));
            printf("%s hex\n", binaryToHex(number).c_str());
        }
        if (type == "hex") {
            printf("%d dec\n", hexToDecimal(number));
            printf("%s bin\n", hexToBinary(number).c_str());
        }
        printf("\n");

        currentCase++;
    }

    return 0;
}