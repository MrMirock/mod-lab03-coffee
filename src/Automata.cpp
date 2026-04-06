// Copyright 2026 KashinGS
#include "Automata.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

Automata::Automata() : cash(0), state(STATES::OFF), selectedPrice(0) {
    menu.push_back("Water");
    menu.push_back("Tea");
    menu.push_back("Espresso");
    menu.push_back("Capuccino");
    menu.push_back("Latte");

    prices.push_back(10);
    prices.push_back(20);
    prices.push_back(30);
    prices.push_back(45);
    prices.push_back(55);
}

void Automata::on() {
    if (state == STATES::OFF) {
        state = STATES::WAIT;
        cash = 0;
        selectedPrice = 0;
        std::cout << "The vending machine is turned on. Status: WAIT.\n";
    } else {
        std::cout << "Can't turned on: the machine is ON.\n";
    }
}

void Automata::off() {
    if (state == STATES::WAIT) {
        if (cash > 0) {
            std::cout << "Refund of money:" << cash << " $.\n";
            cash = 0;
        }
        state = STATES::OFF;
        std::cout << "The machine is turned off.\n";
    } else {
        std::cout << "Shutdown is possible only from the WAIT state.\n";
    }
}

void Automata::coin(int amount) {
    if (state == STATES::WAIT) {
        if (amount > 0) {
            cash += amount;
            state = STATES::ACCEPT;
            std::cout << "Introduced " << amount << " $. Balance: " << cash
                      << " $. State: ACCEPT.\n";
        } else {
            std::cout << "The amount must be positive.\n";
        }
    } else if (state == STATES::ACCEPT) {
        if (amount > 0) {
            cash += amount;
            std::cout << "Introduced " << amount << " $. Balance: " << cash
                      << " $. State: ACCEPT.\n";
        } else {
            std::cout << "The amount must be positive.\n";
        }
    } else {
        std::cout << "It is not possible to deposit money now (condition "
                  << static_cast<int>(state) << ").\n";
    }
}

std::string Automata::getMenu() {
    if (state == STATES::OFF) {
        return "The machine is turned off. The menu is unavailable.\n";
    }
    std::string result = "Menu:\n";
    for (size_t i = 0; i < menu.size(); ++i) {
        result += std::to_string(i + 1) + ". " + menu[i] + " - "
                  + std::to_string(prices[i]) + " $.\n";
    }
    return result;
}

STATES Automata::getState() {
    return state;
}

bool Automata::choice(int index) {
    if (state != STATES::ACCEPT) {
        std::cout << "The choice drink is possible in the ACCEPT.\n";
        return false;
    }
    int idx = index - 1;
    if (idx < 0 || idx >= static_cast<int>(menu.size())) {
        std::cout << "Incorrect drink number.\n";
        return false;
    }
    selectedPrice = prices[idx];
    state = STATES::CHECK;
    std::cout << "Selected " << menu[idx] << " (price " << selectedPrice
              << " $.). Switching to the CHECK state.\n";
    return true;
}

bool Automata::check() {
    if (state != STATES::CHECK) {
        std::cout << "Verification is only possible in the CHECK state.\n";
        return false;
    }
    if (cash >= selectedPrice) {
        std::cout << "There's enough money (" << cash << " $. >= "
                  << selectedPrice << " $.).\n";
        return true;
    } else {
        std::cout << "There's not enough money: need " << selectedPrice
                  << " $., Inserted " << cash << " $.\n";
        return false;
    }
}

void Automata::cancel() {
    if (state == STATES::ACCEPT || state == STATES::CHECK) {
        if (cash > 0) {
            std::cout << "Refund of money: " << cash << " $.\n";
            cash = 0;
        } else {
            std::cout << "There is no money for a refund.\n";
        }
        state = STATES::WAIT;
        selectedPrice = 0;
        std::cout << "Switching to the WAIT state.\n";
    } else {
        std::cout << "Cancellation is not possible in the current state.\n";
    }
}

void Automata::cook() {
    if (state != STATES::CHECK) {
        std::cout << "Cooking is possible only from the CHECK state.\n";
        return;
    }
    if (!check()) {
        std::cout << "Insufficient funds. Deposit the money first or cancel "
                  << "the operation.\n";
        return;
    }
    cash -= selectedPrice;
    std::cout << "Written off " << selectedPrice << " $. Account balance: "
              << cash << " $.\n";
    state = STATES::COOK;
    std::cout << "We begin the preparation of the drink...\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "The drink is ready.\n";
}

void Automata::finish() {
    if (state != STATES::COOK) {
        std::cout << "Delivery is possible after cooking.\n";
        return;
    }
    std::cout << "Serving the drink. Take your drink.\n";
    state = STATES::WAIT;
    selectedPrice = 0;
    std::cout << "Switching to the WAIT state.\n";
}
