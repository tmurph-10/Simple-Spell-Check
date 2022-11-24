#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <vector>
using namespace std;

void SpellCheck(string &userInput) {
    const int MAX_WORDS = 300;
    ifstream fin;
    fin.open("Words.txt");
    string newWord = "";
    vector<string> allWordsInFile;
    vector<int> allWordMatches;
    int numWords = 0;
    int capitalLetterIndexs[45];

    bool allLettersCapital = true;
    for (int x = 0; x < userInput.size(); x++) {
        if (userInput[x] != toupper(userInput[x])) {
            allLettersCapital = false;
            break;
        }
    }
    while (getline(fin, newWord)) {
        int numMatches = 0;
        fin >> newWord;
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

        //exact word was found, nothing needs to be changed
        if (userInput == newWord) {
            userInput = newWord;
            return;
        }
        for (int i = 0; i < userInput.size(); i++) {
            int j = 0;
            while (j < newWord.size() && j < userInput.size()) {
                if (userInput[i] == newWord[j]) {
                    numMatches++;
                }
                j++;
            }
        }
        allWordsInFile.push_back(newWord);
        allWordMatches.push_back(numMatches);
        newWord = "";
        numWords++;
    }

    //initializing bestWord & maxMatches to first element in vectors
    string bestWord = allWordsInFile[0];
    int maxMatches = allWordMatches[0]; 
    string equalWord = "";
    int wordToLookAt = 0;

    for (int i = 0; i <= numWords; i++) {
        for (int j = i + 1; j <= numWords; j++) {
            wordToLookAt = allWordMatches[j];
            if (maxMatches < wordToLookAt) { //maxMatches will be updated if a word has more matches
                maxMatches = wordToLookAt;
                bestWord = allWordsInFile[j];
                equalWord = "";
            }
            else if (maxMatches == wordToLookAt) { //if a word is encountered with equal matches to maxMatches
                equalWord = allWordsInFile[j];
                int bestWordMatches = 0;
                int equalWordMatches = 0;
                //now instead of just looking at char matches, looking to see which is most similar
                //at each index of the strings
                for (int i = 0; i < userInput.size(); i++) {
                    if (bestWord[i] == userInput[i]) {
                        bestWordMatches++;
                    }
                    if (equalWord[i] == userInput[i]) {
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
                //if the words have the same amount of matches at each index the smaller of the two words is picked
                else if (bestWordMatches == equalWordMatches) {
                    if (equalWord.size() < bestWord.size()) {
                        bestWord = equalWord;
                        equalWord = "";
                    }
                    else  {
                        equalWord = "";
                    }
                }
            }
        }
    }
    //hard coding some very specific cases for userEntry
    if (userInput == "j" || userInput == "u" || userInput == "o" || userInput == "k" || userInput == "l" || userInput == "I" || userInput == "i") {
        bestWord = "I";
    }
    if (userInput == "Im") {
        bestWord = "I'm";
    }
    if (userInput == "youre") {
        bestWord = "you're";
    }
    if (userInput == "dont") {
        bestWord = "don't";
    }

    //clearing vectors
    allWordMatches.clear();
    allWordsInFile.clear();

    //setting userInput reference equal to bestWord
    userInput = bestWord;
}