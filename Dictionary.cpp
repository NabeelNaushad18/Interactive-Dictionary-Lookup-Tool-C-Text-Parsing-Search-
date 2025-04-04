//This file contains the implementation of the `Dictionary` class's methods.
// It defines how the dictionary is loaded from a file and how to search for a word within the dictionary.
// Written By: Nabeel Naushad
// Student ID: 10664419

#include "dictionary.h"
#include "word.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

bool Dictionary::loadDictionary(const string& fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "File not found.\n";
        return false;
    }

    const string typeTag = "Type: ";
    const string nameTag = "Word: ";
    const string defTag = "Definition: ";
    string buffer;
    Word currentWord;

    while (getline(file, buffer)) {
        if (buffer.substr(0, typeTag.size()) == typeTag) {
            currentWord.setType(buffer.substr(typeTag.size()));
        }
        else if (buffer.substr(0, defTag.size()) == defTag) {
            currentWord.setDefinition(buffer.substr(defTag.size()));
        }
        else if (buffer.substr(0, nameTag.size()) == nameTag) {
            currentWord.setName(buffer.substr(nameTag.size()));
        }
        else if (buffer.empty()) {
            if (!currentWord.getName().empty()) {
                words.push_back(currentWord);
                currentWord = Word();  // Reset word
            }
        }
    }

    // Check if the last word was added
    if (!currentWord.getName().empty()) {
        words.push_back(currentWord);
    }

    file.close();
    return true;
}

Word Dictionary::search(const string& wordToFind) const {
    for (const auto& word : words) {
        if (word.getName() == wordToFind) {
            return word;
        }
    }
    return Word();  // Return an empty Word object if not found
}

void Dictionary::menu() {
    while (true) {
        int choice;
        cout << "1. Load dictionary\n2. Search for a word\n3. Exit\n";

        // Input validation
        while (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number: ";
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }

        if (choice == 1) {
            string fileName;
            cout << "Enter file name: ";
            cin >> fileName;
            if (loadDictionary(fileName)) {
                cout << "Dictionary loaded successfully.\n";
            }
            else {
                cout << "Failed to load dictionary.\n";
            }
        }
        else if (choice == 2) {
            string word;
            cout << "Enter word to search: ";
            cin >> word;
            Word foundWord = search(word);
            if (foundWord.getName().empty()) {
                cout << "Word not found.\n";
            }
            else {
                foundWord.printDefinition();
            }
        }
        else if (choice == 3) {
            break;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}
