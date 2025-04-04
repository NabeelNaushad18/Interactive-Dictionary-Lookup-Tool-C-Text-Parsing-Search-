// This file contains the implementation of the `ImprovedDictionary` class's methods.
// It provides the logic for adding new words, playing a guessing game, and overriding the main menu functionality.
// Written By: Nabeel Naushad
// Student ID: 10664419

#include "improvedDictionary.h"
#include "dictionary.h"
#include "word.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <limits>

using namespace std;

ImprovedDictionary::ImprovedDictionary() : score(0), highScore(0) {
    loadHighScore();
}

void ImprovedDictionary::loadHighScore() {
    ifstream file("highscore.txt");
    if (file.is_open()) {
        file >> highScore;
        file.close();
    }
    else {
        highScore = 0; // Default high score is zero
    }
}

void ImprovedDictionary::saveHighScore() const {
    ofstream file("highscore.txt");
    if (file.is_open()) {
        file << highScore;
        file.close();
    }
}

void ImprovedDictionary::guessTheFourthWord() {
    srand(static_cast<unsigned>(time(0)));

    // Filter words with more than 4 words in their definition
    vector<Word> eligibleWords;
    for (const auto& word : words) {
        istringstream iss(word.getDefinition());
        int wordCount = 0;
        string w;
        while (iss >> w) {
            wordCount++;
        }
        if (wordCount > 4) {
            eligibleWords.push_back(word);
        }
    }

    if (eligibleWords.empty()) {
        cout << "No eligible words found!\n";
        return;
    }

    // The program chooses a random word from the dictionary
    Word randomWord = eligibleWords[rand() % eligibleWords.size()];
    string definition = randomWord.getDefinition();

    // Find and replace the fourth word with underscores for user to guess the word
    istringstream iss(definition);
    vector<string> wordsInDefinition;
    string w;
    while (iss >> w) {
        wordsInDefinition.push_back(w);
    }

    if (wordsInDefinition.size() < 4) {
        cout << "The selected word does not have a fourth word in its definition.\n";
        return;
    }

    string hiddenWord = wordsInDefinition[3];  // 4th word
    wordsInDefinition[3] = string(hiddenWord.size(), '_');

    // Show the modified definition
    cout << "Guess the missing word in the following definition:\n";
    for (const auto& w : wordsInDefinition) {
        cout << w << " ";
    }
    cout << "\n";

    // Get user's guess
    string guess;
    cin >> guess;

    if (guess == hiddenWord) {
        cout << "Congratulations! You guessed the word correctly.\n";
        score += 10; // Increment score
        cout << "Your current score: " << score << "\n";

        // Check for new high score
        if (score > highScore) {
            highScore = score;
            cout << "New high score: " << highScore << "!\n";
        }

        // Ask for another word
        guessTheFourthWord();
    }
    else {
        cout << "Incorrect. The correct word was: " << hiddenWord << "\n";
        cout << "Your final score: " << score << "\n";
        // Save high score if necessary
        saveHighScore();
    }
}

void ImprovedDictionary::addWord() {
    string name, type, definition;
    vector<string> validTypes = { "v", "n", "adv", "adj", "prep", "pn", "n_and-v", "misc" };

    cout << "Enter word name: ";
    cin >> name;

    // Check if the word already exists in the dictionary
    for (const auto& word : words) {
        if (word.getName() == name) {
            cout << "Error: word exists, elevated privileges required to edit existing words.\n";
            return;  // Exit early if the word exists
        }
    }

    // Input type and check validity
    bool validType = false;
    do {
        cout << "Enter word type (v, n, adv, adj, prep, pn, n_and-v, misc): ";
        cin >> type;
        for (const auto& validTypeEntry : validTypes) {
            if (type == validTypeEntry) {
                validType = true;
                break;
            }
        }
        if (!validType) {
            cout << "Invalid type! Please enter one of the valid types: v, n, adv, adj, prep, pn, n_and-v, misc.\n";
        }
    } while (!validType);

    cout << "Enter word definition: ";
    cin.ignore();
    getline(cin, definition);

    // Add the new word to the dictionary
    Word newWord(name, type, definition);
    words.push_back(newWord);

    string fileName;
    char overwriteChoice;
    cout << "Do you want to overwrite the existing dictionary file? (y/n): ";
    cin >> overwriteChoice;

    if (overwriteChoice == 'y' || overwriteChoice == 'Y') {
        fileName = "dictionary_2024S2.txt";
    }
    else {
        cout << "Enter a new file name to save the updated dictionary: ";
        cin >> fileName;
    }

    // Save the updated dictionary to the specified file
    ofstream file(fileName);
    if (file.is_open()) {
        for (const auto& word : words) {
            file << "Word: " << word.getName() << "\n";
            file << "Type: " << word.getType() << "\n";
            file << "Definition: " << word.getDefinition() << "\n\n";
        }
        file.close();
        cout << "Dictionary saved successfully to " << fileName << ".\n";
    }
    else {
        cout << "Failed to save dictionary to " << fileName << ".\n";
    }
}

void ImprovedDictionary::menu() {
    while (true) {
        int choice;
        cout << "1. Load dictionary\n2. Search for a word\n3. Guess the fourth word\n4. Add a word\n5. Exit\n";

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

            if (!loadDictionary(fileName)) {
                cout << "File not found. Loading default dictionary: dictionary_2024S2.txt\n";
                if (loadDictionary("dictionary_2024S2.txt")) {
                    cout << "Default dictionary loaded successfully.\n";
                }
                else {
                    cout << "Failed to load the default dictionary.\n";
                }
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
            guessTheFourthWord();
        }
        else if (choice == 4) {
            addWord();
        }
        else if (choice == 5) {
            saveHighScore(); // Save high score on exit
            break;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}
