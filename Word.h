//This header file defines the structure `Word`, which represents a word in the dictionary.
//Each word contains three properties : its name, type(e.g., noun, verb), and definition.
// Written By: Nabeel Naushad
// Student ID: 10664419
#ifndef WORD_H
#define WORD_H

#include <string>
#include <iostream>

class Word {
private:
    std::string name;
    std::string type;
    std::string definition;

public:
    Word() = default;
    Word(std::string name, std::string type, std::string definition) : name(name), type(type), definition(definition) {}

    void setName(const std::string& name) { this->name = name; }
    void setType(const std::string& type) { this->type = type; }
    void setDefinition(const std::string& definition) { this->definition = definition; }

    std::string getName() const { return name; }
    std::string getType() const { return type; }
    std::string getDefinition() const { return definition; }

    void printDefinition() const {
        std::cout << "Word: " << name << "\nType: " << type << "\nDefinition: " << definition << "\n";
    }
};

#endif
