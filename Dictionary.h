// This header file defines the `Dictionary` class.The class holds a collection of `Word` objects
//and provides methods to load a dictionary from a file and search for words.
// Written By: Nabeel Naushad
// Student ID: 10664419

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "Word.h"
#include <vector>
#include <string>

class Dictionary {
protected:
    std::vector<Word> words;

public:
    bool loadDictionary(const std::string& fileName);
    Word search(const std::string& wordToFind) const;
    void menu();
};

#endif
