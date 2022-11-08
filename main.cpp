#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cctype>
#include <vector>
#include <algorithm>
using namespace std;

#include "SpellChecker.h"

int main() {
    string userSentence;
    cout << "Enter a sentence or paragraph." << endl;
    getline(cin, userSentence);
    istringstream inSS(userSentence);
    //string wordsInSentence[30];
    vector<string> wordsInSentence;
    int numWords = 0;
    //For loop to find how many words are in the sentence
    for (int i = 0; i < userSentence.size(); i++) {
        if (isspace(userSentence[i])) {
            numWords++;
        }
    }
    numWords = numWords + 1;
    string word = "";
    int wordsAcquired = 0;
    //Going for as long as every word has been aquired
    string punctuation = "";
    int punctIndex = 0;
    string firstWord = "";
    string secondWord = "";
    char letter;
    while (wordsAcquired <= numWords) {
        inSS >> word;
        if (word.find("/") != string::npos) {
            firstWord = word[0];
            size_t slashIndex = word.find("/");
            firstWord = word.substr(0, slashIndex);
            SpellCheck(firstWord);
            secondWord = word.substr((slashIndex + 1), (word.size() - 1));
            SpellCheck(secondWord);
            word = firstWord;
            word.append("/");
            word.append(secondWord);
        }
        else if ((wordsAcquired + 1) != numWords) {
            //int numPunctuation = 1;
            while (punctIndex < word.size()) {
                if (ispunct(word[punctIndex]) && (punctIndex == word.size() - 1)) {
                    punctuation = word[punctIndex];
                    /*for (int j = punctIndex; j < word.size() - 1; j++) {
                        if (ispunct(word[punctIndex + 1])) {
                            numPunctuation++;
                        }
                    }*/
                    break;
                }
                punctIndex++;
            }
            SpellCheck(word);
        }
        else if ((wordsAcquired + 1) == numWords) {
            while (punctIndex < word.size()) {
                if (ispunct(word[punctIndex]) && (punctIndex == word.size() - 1)) {
                    punctuation = word[punctIndex];
                    break;
                }
                punctIndex++;
            }
            SpellCheck(word);
        }
        if (wordsAcquired == 0) {
            word[0] = toupper(word[0]);
        }
        if (punctuation != "") {
            word.append(punctuation);
        }
        /*if (word[0] == "a" || word[0] == "e" || word[0] == "i" || word[0] == "o" || word[0] == "u") {
            if (wordsInSentence[wordsAcquired - 1] == "a" || wordsInSentence[wordsAcquired - 1] == "A") {
                (wordsInSentence[wordsAcquired -1]).append("n");
            }
        }*/
        //wordsInSentence[wordsAcquired] = word;
        wordsInSentence.push_back(word);
        punctuation = "";
        punctIndex = 0;
        word = "";
        string firstWord = "";
        string secondWord = "";
        wordsAcquired++;
    }
    /*
    for (int x = 0; x < numWords; x++) {
        wordsInSentence[x] = wordsInSentence[x];
        cout << wordsInSentence[x] << " ";
    }
    */
    for_each(wordsInSentence.begin(), wordsInSentence.end(), [] (string currWord) {cout << currWord << " ";});
    cout << endl;
    return 0;
}
