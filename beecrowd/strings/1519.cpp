#include <stdio.h>
#include <string>
#include <iostream>
#include <map>
#include <utility>

using namespace std;

int main() {

    string sentence;
    while (true) {
        getline(cin, sentence);
        if (sentence == ".") break;

        map<string, int> dictionary;
        string word = "";
        for (int i = 0; i < sentence.size(); i++) {
            char c = sentence[i];
            if ((c == ' ' || i == sentence.size() - 1)) {
                if (c != ' ') word += c;

                if (word.size() > 2) {
                    dictionary[word] += (word.size() - 2);
                }
                word = "";
            } else {
                word += c;
            }
        }

        map<string, int>::iterator itDictionary;
        map<char, pair<string, int> > abbreviations;
        for (itDictionary = dictionary.begin(); itDictionary != dictionary.end(); itDictionary++) {
            if (itDictionary->second > abbreviations[itDictionary->first[0]].second) {
                abbreviations[itDictionary->first[0]] = make_pair(itDictionary->first, itDictionary->second);
            }
        }

        bool isFirstWordPrinted = true;
        for (int i = 0; i < sentence.size(); i++) {
            char c = sentence[i];
            if ((c == ' ' || i == sentence.size() - 1)) {
                if (c != ' ') word += c;

                bool existsAbbreviation = abbreviations.find(word[0]) != abbreviations.end();
                if (existsAbbreviation && abbreviations[word[0]].first == word) {
                    if (isFirstWordPrinted) {
                        printf("%c.", word[0]);
                        isFirstWordPrinted = false;
                    } else {
                        printf(" %c.", word[0]);
                    }
                } else {
                    if (isFirstWordPrinted) {
                        printf("%s", word.c_str());
                        isFirstWordPrinted = false;
                    } else {
                        printf(" %s", word.c_str());
                    }
                }
                word = "";
            } else {
                word += c;
            }
        }

        printf("\n%lu\n", abbreviations.size());

        map<char, pair<string, int> >::iterator it;
        for (it = abbreviations.begin(); it != abbreviations.end(); it++) {
            printf("%c. = %s\n", it->first, it->second.first.c_str());
        }
    }

    return 0;
}