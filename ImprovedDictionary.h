//This header file defines the `ImprovedDictionary` class, which extends the basic `Dictionary` class.
//It includes additional functionality like playing a word guessing game and adding new words to the dictionary.
// Written By: Nabeel Naushad
// Student ID: 10664419
#ifndef IMPROVEDDICTIONARY_H
#define IMPROVEDDICTIONARY_H

#include "Dictionary.h"

class ImprovedDictionary : public Dictionary {
private:
    int score;
    int highScore;

public:
    ImprovedDictionary();
    void loadHighScore();
    void saveHighScore() const;
    void guessTheFourthWord();
    void addWord();
    void menu();
};

#endif

