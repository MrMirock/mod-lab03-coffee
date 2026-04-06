#include "Automata.h"
#include <iostream>

int main() {
    Automata machine;
    std::cout << machine.getMenu();
    machine.on();
    std::cout << machine.getMenu();
    machine.coin(30);
    machine.coin(20);
    if (machine.choice(2)) {
        std::cout << "Состояние после choice: " << static_cast<int>(machine.getState()) << "\n";
        if (machine.check()) {
            machine.cook();
            machine.finish();
        }
        else {
            machine.cancel();
        }
    }
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