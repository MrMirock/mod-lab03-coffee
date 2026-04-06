// Copyright 2025 Student
#ifndef INCLUDE_AUTOMATA_H
#define INCLUDE_AUTOMATA_H

#include <string>
#include <vector>

enum class STATES {
    OFF,
    WAIT,
    ACCEPT,
    CHECK,
    COOK
};

class Automata {
 private:
    int cash;
    std::vector<std::string> menu;
    std::vector<int> prices;
    STATES state;
    int selectedPrice;

 public:
    Automata();

    void on();
    void off();
    void coin(int amount);
    std::string getMenu();
    STATES getState();
    bool choice(int index);
    bool check();
    void cancel();
    void cook();
    void finish();
};

#endif  // INCLUDE_AUTOMATA_H
