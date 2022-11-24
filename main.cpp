#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <vector>
#include <algorithm>
/*
using std::cout; using std::endl; using std::cin;
using std::string;
using std::vector;
using std::istringstream;
*/
using namespace std;

#include "SpellChecker.h"

int main() {
    cout << "Enter a sentence or paragraph." << endl;

    string userEntry;
    getline(cin, userEntry);
    istringstream inSS(userEntry);
    vector<string> enteredWords;
    int numWords = 0;
    //For loop to find how many words are in the sentence
    for (int i = 0; i < userEntry.size(); i++) {
        if (isspace(userEntry[i])) {
            numWords++;
        }
    }
    numWords = numWords + 1;
    string word = "";
    int wordsAcquired = 0;
    string punctuation = "";
    int punctIndex = 0;
    char letter;
    //Going for as long as every word has been aquired
    while (wordsAcquired <= numWords) {
        inSS >> word;
        //checking if a string has a '/' in it
        if (word.find("/") != string::npos) {
            string firstWord = "";
            string secondWord = "";
            size_t slashIndex = word.find("/");
            //setting firstword equal to all char before '/'
            firstWord = word.substr(0, slashIndex);
            SpellCheck(firstWord);
            //setting secondWord equal to all char after '/'
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
        enteredWords.push_back(word);
        punctuation = "";
        punctIndex = 0;
        word = "";
        string firstWord = "";
        string secondWord = "";
        wordsAcquired++;
    }

    //ouputting every spell checked word
    for_each(enteredWords.begin(), enteredWords.end(), [] (string currWord) {cout << currWord << " ";});
    cout << endl;
    return 0;
}