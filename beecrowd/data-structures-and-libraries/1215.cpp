#include <stdio.h>
#include <algorithm>
#include <string>
#include <map>
#include <iostream>

using namespace std;

int main() {

    map<string, bool> dictionary;
    string sentence;
    while (!getline(cin, sentence).eof()) {
        string word = "";
        for (int i = 0; i < sentence.size(); i++) {
            char c = sentence[i];

            if (isalpha(c)) {
                word += c;
            }
            
            if ((!isalpha(c) && word != "") || (i == sentence.size() - 1 && word != "")) {
                transform(word.begin(), word.end(), word.begin(), ::tolower);
                dictionary[word] = true;
                word = "";
            }
        }
    }

    map<string, bool>::iterator it;
    for (it = dictionary.begin(); it != dictionary.end(); it++) {
        printf("%s\n", it->first.c_str());
    }

    return 0;
}