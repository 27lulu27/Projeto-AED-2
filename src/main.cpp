#include <iostream>
#include "Menu.h"
int main() {
    Menu menu; // Crie uma instância de Menu
    System system; // Crie uma instância de System
    menu.start(system); // Inicie o menu passando a instância de System
    return 0;
}
