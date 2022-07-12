#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
using namespace std;

void SpellCheck(string &userInput) {
    const int MAX_WORDS = 250;
    ifstream fin;
    fin.open("Words.txt");
    int userLetters = userInput.size();
    int newWordLetters = 0;
    string newWord = "";
    string allWordsInFile[MAX_WORDS];
    int allWordMatches[MAX_WORDS];
    int numWords = 0;
    int capitalLetterIndexs[45];
    bool allLettersCapital = true;
    int numInArray = 0;
    string exactWordFound = "";
    for (int x = 0; x < userInput.size(); x++) {
        if (userInput[x] != toupper(userInput[x])) {
            allLettersCapital = false;
            break;
        }
    }
    while (getline(fin, newWord)) {
        int numMatches = 0;
        fin >> newWord;
        newWordLetters = newWord.size();
        if (allLettersCapital != false) {
            for (int c = 0; c < newWord.size(); c++) {
                newWord[c] = toupper(newWord[c]);
            }
        }
        else if (userInput[0] == toupper(userInput[0])) {
            newWord[0] = toupper(newWord[0]);
        }
        /*int rightCharacter = 0;
        for (int e = 0; (e < userInput.size()); e++) {
            if (userInput[e] == newWord[e]) {
                rightCharacter++;
            }
        }
        if (rightCharacter >= (newWord.size() - 1)) {
            exactWordFound = newWord;
        }*/
        if (userInput == newWord) {
            exactWordFound = newWord;
        }
        for (int i = 0; i < userLetters; i++) {
            int j = 0;
            while (j < newWordLetters && j < userLetters) {
                if (userInput[i] == newWord[j]) {
                    numMatches++;
                }
                j++;
            }
        }
        allWordsInFile[numWords] = newWord;
        allWordMatches[numWords] = numMatches;
        newWord = "";
        newWordLetters = 0;
        numWords++;
    }
    string bestWord = allWordsInFile[0];
    int maxMatches = allWordMatches[0];
    string equalWord = "";
    int wordToLookAt = 0;
    for (int i = 0; i <= numWords; i++) {
        for (int j = i + 1; j <= numWords; j++) {
            wordToLookAt = allWordMatches[j];
            if (maxMatches < wordToLookAt) {
                maxMatches = wordToLookAt;
                bestWord = allWordsInFile[j];
                equalWord = "";
            }
            else if (maxMatches == wordToLookAt) {
                equalWord = allWordsInFile[j];
                int bestWordMatches = 0;
                int equalWordMatches = 0;
                for (int m = 0; m < userInput.size(); m++) {
                    if (bestWord[m] == userInput[m]) {
                        bestWordMatches++;
                    }
                    if (equalWord[m] == userInput[m]) {
                        equalWordMatches++;
                    }
                }
                if (equalWordMatches > bestWordMatches) {
                    bestWord = equalWord;
                    equalWord = "";
                }
                else if (bestWordMatches > equalWordMatches) {
                    equalWord = "";
                }
                else if (bestWordMatches == equalWordMatches) {
                    if (equalWord.size() < bestWord.size()) {
                        bestWord = equalWord;
                        equalWord = "";
                    }
                    if (equalWord.size() > userInput.size()) {
                        equalWord = "";
                    }
                }
            }
        }
    }
    if (userInput == "j" || userInput == "u" || userInput == "o" || userInput == "k" || userInput == "l" || userInput == "I" || userInput == "i") {
        bestWord = "I";
    }
    if (userInput == "youre") {
        bestWord = "you're";
    }
    if (userInput == "dont") {
        bestWord = "don't";
    }
    for (int j = 0; j < MAX_WORDS; j++) {
        allWordMatches[j] = 0;
        allWordsInFile[j] = "";
    }
    if (exactWordFound == "") {
        userInput = bestWord;
    }
    else{
        userInput = exactWordFound;
    }
}