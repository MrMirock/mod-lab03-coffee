// Copyright 2026 KashinGS
#include "Automata.h"
#include <iostream>

int main() {
    Automata machine;
    std::cout << machine.getMenu();
    machine.on();
    std::cout << machine.getMenu();
    machine.coin(30);
    machine.coin(20);
    machine.choice(2);
    machine.check();
    machine.cook();
    machine.finish();
    machine.coin(40);
    machine.choice(1);
    machine.check();
    machine.cook();
    machine.finish();
    machine.coin(20);
    machine.choice(3);
    machine.check();
    machine.cancel();
    machine.off();
    return 0;
}
