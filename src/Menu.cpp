
#include <iostream>
#include "Menu.h"

using namespace std;

void Menu::start(System system) {
    while (true) {
        cout << endl << "Menu:" << endl;
        cout << "1- Present the best flight option" << endl;
        cout << "Press a number to continue or press 0 to quit" << endl;
        int choice;  // Corrigindo o nome da variável para "choice".
        cin >> choice;

        if (choice == 0) {
            break;
        } else if (choice == 1) {
            cout << "Enter the Airport source code:" << endl;
            string source;
            cin >> source;
            cout << "Enter the Airport destination code:" << endl;
            string destination;  // Corrigindo o nome da variável para "destination".
            cin >> destination;
            system.FastConnection(source, destination);  // Corrigindo o nome da função para FastConnection.
        }
    }
}
